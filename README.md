## UID: 123456789

## Pipe Up

This program runs all subsequent arguments as programs and as if there were a pipe in between adjacent ones.

## Building

If running on a Linux machine:
make

Otherwise:
gcc -o pipe pipe.c

## Running

Example:
./pipe ls cat wc
      7       7      63

This command outputs the equivalent of:
ls | cat | wc

## Cleaning up

Run the following command:
make clean
