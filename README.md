# Pipex

[Spanish version 🇪🇸](README_es.md)

<p align="center">
    <img src="https://github.com/rpaparoni/imgs/blob/main/Captura%20desde%202025-03-04%2014-55-25.png" alt="Image description" />
</p>

## Description

Pipex is a project from 42 school that aims to replicate the behavior of the pipeline in Unix, allowing communication between processes through `pipe()`, `dup2()`, and `execve()`.

The goal is to execute commands in a chain like:

```bash
< infile cmd1 | cmd2 > outfile
```

This means that the output of `cmd1` becomes the input of `cmd2`, and the final result is saved in `outfile`.

## Installation and Usage

### Compilation

To compile the project, simply run:

```bash
make
```

This will generate the `pipex` executable.

To compile the bonus (support for `here_doc` and multiple pipes):

```bash
make bonus
```

### Usage

To run the program:

```bash
./pipex infile "command1" "command2" outfile
```

Example:

```bash
./pipex input.txt "cat -e" "wc -l" output.txt
```

This will take `input.txt`, execute `cat -e`, then pass its output to `wc -l`, and finally save the result in `output.txt`.

#### Bonus (Support for here\_doc)

If you want to use `here_doc` to simulate an interactive standard input:

```bash
./pipex here_doc LIMITER "command1" "command2" output.txt
```

Example:

```bash
./pipex here_doc END "cat" "wc -l" output.txt
```

Here, the program will read the standard input until it finds the word `END`, then process the commands and save the output in `output.txt`.

## Functions Used

The program uses key Unix functions such as:

- `pipe()` - Creates a communication channel between processes.
- `fork()` - Creates child processes to execute commands.
- `dup2()` - Redirects standard input/output.
- `execve()` - Executes commands in a new environment.
- `waitpid()` - Waits for child processes to terminate.

## Errors and Exception Handling

The program handles common errors such as:

- Non-existent input file.
- Command not found or incorrect.
- Insufficient permissions to open files.
- Failures in `pipe()`, `fork()`, or `execve()`.

If something fails, an error message will be printed with a specific function.

##

