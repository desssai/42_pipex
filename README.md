# pipex

## Overview

A program that is built on several UNIX mechanisms. Multiprocessing, working with pipes, 
redirecting input and output as well as executing binary files. All of it written in C, in 98 standard.
The program reads data from input file, executes a shell command, redirects the output to either a pipe
or to an output file. If there is another command and the data was redirected to the pipe, the program repeats the same process,
however, this time data is being read from pipe's another end and not from the input file.

So as to handle errors that may arise during the execution of commands, a child-process is created for the execution of each command
using `fork()`. Every command is executed inside of a child-process, while the only parent-process waits for the child to either complete its task, 
or finish with an error id. Data is redirected between processes using pipes.

## Usage

1. Clone the repository.
2. Compile the program using Makefile.
3. Launch the program. 

The Makefile rules are as follows:

| Rule | Despription |
| ---- | ----------- |
| ALL | Compiles the program using GCC. |
| BONUS | Compiles the program the same way 'ALL' does. |
| CLEAN | Removes object files leaving only the executable present. |
| FCLEAN | Removes both the executable and object files. |
| RE | Recompiles the program using **CLEAN** and **ALL** Makefile rules |

## Examples
The program should be executed as follows:
```
./pipex file1 cmd1 cmd2 ... cmdn file2
```
It must take at least 4 arguments:
- file1 and file2 are file names.
- cmd1, cmd2 and cmdn are shell commands with their parameters.

The program works with the following redirection modes.
| Mode | Despription |
| ---- | ----------- |
| << | Read from standard input until LIMITER. If here_doc keywoard is used for the input_file. |
| < | Read from an input file. |
| \> | Erase the file's content and write to a file. |

#### For example
```
./pipex infile "ls -l" "wc -l" outfile
./pipex here_doc LIMITER cmd cmd1 file
./pipex infile "grep a1" "wc -w" outfile
```
#### Is exactly the same as 
```
< infile ls -l | wc -l > outfile
cmd << LIMITER | cmd1 >> file
< infile grep a1 | wc -w > outfile
```
