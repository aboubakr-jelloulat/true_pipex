# Pipex

[![1337 Badge](https://img.shields.io/badge/1337-Project-blue)](https://www.42network.org/)

## Table of Contents
- [Introduction](#introduction)
- [How Pipex Works](#how-pipex-works)
- [Mandatory Part](#mandatory-part)
- [Bonus Part](#bonus-part)
- [Installation](#installation)
- [Usage](#usage)
- [Process Explanation](#process-explanation)
- [Example](#example)
- [Resources](#resources)

---

## Introduction
Pipex is a 42 project that aims to deepen your understanding of process management and pipes in Unix-like systems by mimicking the behavior of shell piping (`|`). You will learn how to use system calls like `fork()`, `execve()`, `pipe()`, and `dup2()` to handle inter-process communication.

---

## How Pipex Works
Pipex replicates the behavior of the following shell command:

```sh
< file1 cmd1 | cmd2 > file2
```

Where:
- `file1` is the input file.
- `cmd1` processes the input.
- `cmd2` processes the output of `cmd1`.
- `file2` is the output file.

---

## Mandatory Part
### Requirements
- Your program must execute as follows:
  ```sh
  ./pipex file1 cmd1 cmd2 file2
  ```
- You must use the following system calls: `open()`, `close()`, `read()`, `write()`, `malloc()`, `free()`, `perror()`, `strerror()`, `access()`, `dup()`, `dup2()`, `execve()`, `exit()`, `fork()`, `pipe()`, `unlink()`, `wait()`, `waitpid()`.
- No memory leaks allowed.
- Your program must behave exactly like the shell.

---

## Bonus Part
To earn extra points, you must implement:
- **Multiple pipes**: Handling commands like:
  ```sh
  ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
  ```
- **Here_doc mode**: Supporting `<< LIMITER` and `>> file` redirections:
  ```sh
  ./pipex here_doc LIMITER cmd cmd1 file
  ```

---

## Installation
Clone the repository and compile the project:
```sh
git clone <your_repo_link>
cd pipex
make
```

---

## Usage
Run Pipex with two commands and two files:
```sh
./pipex input.txt "cat -e" "grep hello" output.txt
```

For bonus (multiple commands):
```sh
./pipex input.txt "ls -l" "grep .c" "wc -l" output.txt
```

For here_doc:
```sh
./pipex here_doc EOF "cat" "wc -l" output.txt
```

---

## Process Explanation
| Step | Action |
|------|--------|
| 1.   | Open `file1` for reading. |
| 2.   | Create a pipe for inter-process communication. |
| 3.   | Fork the first child process to execute `cmd1`. |
| 4.   | Redirect input from `file1` and output to the pipe. |
| 5.   | Fork the second child process to execute `cmd2`. |
| 6.   | Redirect input from the pipe and output to `file2`. |
| 7.   | Wait for both processes to finish and close file descriptors. |

---

## Example
### Input:
```sh
$ echo "hello world" > infile
$ ./pipex infile "cat -e" "grep hello" outfile
```
### Equivalent Shell Command:
```sh
$ < infile cat -e | grep hello > outfile
```
### Output (`outfile`):
```sh
hello world$
```

---

## Resources
- [Pipe and Fork in Unix](https://www.geeksforgeeks.org/pipe-system-call/)
- [Exec Family Functions](https://linux.die.net/man/3/exec)
- [42 Pipex Subject](https://cdn.intra.42.fr/pdf/pdf/34483/en.subject.pdf)

---

Enjoy coding! 🚀

