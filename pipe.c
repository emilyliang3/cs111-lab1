#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		exit(EINVAL);
	}
	int fd[2];
	for (int i = 1; i < argc; i++) {
		const char *program = argv[i];
		if (pipe(fd) == -1)
			exit(errno);
		pid_t pid = fork();
		if (pid < 0) {
			exit(errno);
		}
		if (pid == 0) {
			// if more programs after this one:
			if (i < argc - 1) {
				if (close(fd[0]) == -1)
					exit(errno);
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					exit(errno);
			}
			execlp(program, program, (char*) NULL);
			exit(errno);
		}
		int st;
		if (waitpid(pid, &st, 0) < 0) {
			exit(errno);
		}
		if (!WIFEXITED(st))
			exit(errno);
		if (WEXITSTATUS(st) != 0)
			exit(WEXITSTATUS(st));
		// not first program
		if (close(fd[1]) == -1)
			exit(errno);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit(errno);
	}
	return 0;
}
