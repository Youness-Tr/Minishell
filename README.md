# 🐚 Minishell (Neoshell)

A custom Unix shell implementation written in C, inspired by Bash. This project recreates the behavior of a command-line interpreter with support for pipes, redirections, environment variables, built-in commands, and advanced features like logical operators and wildcards.

![Language](https://img.shields.io/badge/language-C-blue.svg)
![School](https://img.shields.io/badge/school-42-success.svg)

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Architecture](#project-architecture)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Advanced Features](#advanced-features)
- [Examples](#examples)
- [Technical Details](#technical-details)
- [Memory Management](#memory-management)
- [Contributors](#contributors)

## 🎯 Overview

Minishell (branded as "neoshell") is a minimalist yet feature-rich shell implementation that mimics the behavior of Bash. It provides an interactive command-line interface where users can execute commands, manage processes, handle I/O redirections, and much more.

The project demonstrates deep understanding of:
- Process creation and management (`fork`, `execve`, `wait`)
- File descriptors and I/O redirections
- Signal handling
- Parsing and lexical analysis
- Abstract Syntax Trees (AST)
- Memory management in C

## ✨ Features

### Core Functionality
- **Interactive Prompt**: Custom prompt display (`neoshell->$ `)
- **Command Execution**: Execute system commands with proper PATH resolution
- **Command History**: Navigate through previous commands using readline
- **Quote Handling**: Support for single (`'`) and double (`"`) quotes
- **Environment Variables**: Expand variables with `$` syntax
- **Exit Status**: Track and expand last command exit status with `$?`

### Input/Output Redirections
- `<` : Input redirection
- `>` : Output redirection (overwrite)
- `>>` : Output redirection (append)
- `<<` : Here-document with delimiter

### Pipes and Operators
- `|` : Pipeline execution
- `&&` : Logical AND (execute second command only if first succeeds)
- `||` : Logical OR (execute second command only if first fails)
- `()` : Command grouping with subshells

### Built-in Commands
- `echo` with `-n` option
- `cd` with relative or absolute path
- `pwd` (no options)
- `export` for environment variable management
- `unset` to remove environment variables
- `env` to display environment
- `exit` with numeric argument

### Advanced Features
- **Wildcards**: Filename expansion with `*` (asterisk)
- **Here-documents**: Multi-line input with variable expansion
- **Signal Handling**: Proper handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`
- **Shell Level Tracking**: Automatic `SHLVL` increment

## 🏗️ Project Architecture

The project is organized into modular components:

```
Minishell/
├── Builtins/       # Built-in command implementations
│   ├── cd.c        # Change directory
│   ├── echo.c      # Echo command
│   ├── env.c       # Environment display
│   ├── exit.c      # Exit shell
│   ├── export.c    # Export variables
│   ├── pwd.c       # Print working directory
│   └── unset.c     # Unset variables
│
├── Lexer/          # Tokenization and lexical analysis
│   ├── lexical.c   # Main lexer logic
│   ├── token.c     # Token creation and management
│   └── lex_utils.c # Lexer utilities
│
├── Parser/         # Syntax analysis and AST construction
│   ├── ft_parser.c # Main parser (Recursive Descent)
│   ├── left_hand.c # Left-hand side parsing
│   └── putils.c    # Parser utilities
│
├── Executer/       # Command execution engine
│   ├── ft_execute.c    # Main execution logic
│   ├── ex_pipeline.c   # Pipeline execution
│   ├── ex_heredoc.c    # Here-document handling
│   ├── ex_io.c         # I/O redirection
│   ├── ex_and.c        # AND operator
│   ├── ex_or.c         # OR operator
│   └── ex_builtins.c   # Built-in execution
│
├── Expand/         # Variable expansion
│   ├── expander.c      # Main expansion logic
│   ├── exp_heredoc.c   # Here-doc expansion
│   └── exputils.c      # Expansion utilities
│
├── signals/        # Signal handling (Ctrl-C, etc.)
│   └── signal.c
│
├── wildcard/       # Wildcard expansion (*)
│   ├── asterisk.c
│   └── astirisk_tool.c
│
├── Leaks/          # Memory management
│   ├── garbedge.c  # Garbage collector
│   └── free_all.c  # Memory cleanup
│
├── Libft/          # Custom C library
│   └── [various utility functions]
│
├── Header/
│   └── headers.h   # Main header file
│
└── Main/
    └── main.c      # Entry point
```

## 🚀 Installation

### Prerequisites

- GCC or Clang compiler
- GNU Make
- readline library

#### Installing readline on Linux:
```bash
# Debian/Ubuntu
sudo apt-get install libreadline-dev

# Fedora/RHEL
sudo dnf install readline-devel

# Arch Linux
sudo pacman -S readline
```

#### Installing readline on macOS:
```bash
brew install readline
```

### Build Instructions

1. **Clone the repository**:
```bash
git clone https://github.com/Youness-Tr/Minishell.git
cd Minishell
```

2. **Compile the project**:
```bash
make
```

This will:
- Build the custom libft library
- Compile all source files
- Link with readline library
- Generate the `minishell` executable

3. **Clean object files** (optional):
```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile everything from scratch
```

## 💻 Usage

### Starting the Shell

```bash
./minishell
```

You will see the prompt:
```
neoshell->$
```

### Basic Usage

```bash
# Execute a simple command
neoshell->$ ls -la

# Use pipes
neoshell->$ ls -l | grep .c | wc -l

# Input/Output redirections
neoshell->$ cat < input.txt > output.txt
neoshell->$ echo "Hello World" >> file.txt

# Here-document
neoshell->$ cat << EOF
> Line 1
> Line 2
> EOF

# Environment variables
neoshell->$ echo $HOME
neoshell->$ echo $?

# Logical operators
neoshell->$ mkdir test && cd test
neoshell->$ cd nonexistent || echo "Directory not found"

# Command grouping
neoshell->$ (cd /tmp && ls) && pwd
```

### Exiting the Shell

```bash
neoshell->$ exit
# or
neoshell->$ exit 42  # Exit with specific status code
# or press Ctrl-D
```

## 🔨 Built-in Commands

### `echo`
Prints arguments to standard output.
```bash
neoshell->$ echo Hello World
Hello World

neoshell->$ echo -n "No newline"
No newline neoshell->$

neoshell->$ echo "$HOME is my home"
/home/user is my home
```

### `cd`
Changes the current directory.
```bash
neoshell->$ cd /tmp
neoshell->$ cd ..
neoshell->$ cd ~
neoshell->$ cd -  # Go to previous directory
```

### `pwd`
Prints the current working directory.
```bash
neoshell->$ pwd
/home/user/Minishell
```

### `export`
Sets or displays environment variables.
```bash
neoshell->$ export VAR=value
neoshell->$ export VAR="value with spaces"
neoshell->$ export  # Display all exported variables
```

### `unset`
Removes environment variables.
```bash
neoshell->$ unset VAR
neoshell->$ unset VAR1 VAR2 VAR3
```

### `env`
Displays all environment variables.
```bash
neoshell->$ env
HOME=/home/user
PATH=/usr/bin:/bin
...
```

### `exit`
Exits the shell with an optional status code.
```bash
neoshell->$ exit
neoshell->$ exit 0
neoshell->$ exit 42
```

## 🎓 Advanced Features

### Wildcards (Globbing)

The shell supports `*` for filename expansion:

```bash
neoshell->$ echo *.c        # All .c files
neoshell->$ ls *.txt        # All .txt files
neoshell->$ cat file*       # All files starting with "file"
```

### Here-documents

Multi-line input with delimiter:

```bash
neoshell->$ cat << DELIMITER
> This is line 1
> This is line 2
> Variables like $USER are expanded
> DELIMITER
```

### Logical Operators

**AND operator (`&&`)**: Execute second command only if first succeeds
```bash
neoshell->$ make && ./minishell
neoshell->$ mkdir newdir && cd newdir && touch file.txt
```

**OR operator (`||`)**: Execute second command only if first fails
```bash
neoshell->$ cat nonexistent.txt || echo "File not found"
neoshell->$ ./program || echo "Program failed with status $?"
```

### Command Grouping with Parentheses

```bash
neoshell->$ (cd /tmp && ls -la) && pwd
# Changes directory in subshell, lists files, then returns to original directory
```

### Quote Handling

**Single quotes** (`'`): Preserve literal value of all characters
```bash
neoshell->$ echo '$HOME is not expanded'
$HOME is not expanded
```

**Double quotes** (`"`): Preserve literal value except for `$`, `` ` ``, and `\`
```bash
neoshell->$ echo "My home is $HOME"
My home is /home/user
```

### Signal Handling

- **Ctrl-C**: Interrupts current command and displays new prompt
- **Ctrl-D**: Exits the shell (when no input)
- **Ctrl-\\**: Ignored (no quit signal)

## 📝 Examples

### Complex Pipeline
```bash
neoshell->$ cat file.txt | grep "error" | sort | uniq -c | sort -nr > errors.txt
```

### Multiple Redirections
```bash
neoshell->$ < input.txt grep "pattern" > output.txt 2> errors.txt
```

### Variable Expansion
```bash
neoshell->$ export NAME="John"
neoshell->$ echo "Hello, $NAME! Your home is $HOME"
Hello, John! Your home is /home/user
```

### Exit Status
```bash
neoshell->$ ls
neoshell->$ echo $?
0

neoshell->$ ls nonexistent
ls: cannot access 'nonexistent': No such file or directory
neoshell->$ echo $?
2
```

### Combining Features
```bash
neoshell->$ (export VAR=test && echo $VAR) || echo "Failed"
test

neoshell->$ cat << EOF | grep "important"
> This is important
> This is not
> Another important line
> EOF
This is important
Another important line
```

## 🔧 Technical Details

### Parsing Strategy

The shell uses a **Recursive Descent Parser** with precedence climbing to build an Abstract Syntax Tree (AST):

1. **Lexical Analysis**: Input is tokenized into meaningful units (words, operators, redirections)
2. **Syntax Analysis**: Tokens are parsed into an AST respecting operator precedence
3. **Execution**: AST is traversed and executed recursively

**Operator Precedence** (lowest to highest):
- OR (`||`)
- AND (`&&`)
- PIPE (`|`)
- Commands and redirections

### Execution Flow

```
Input → Lexer → Tokens → Parser → AST → Executor → Output
```

1. **Lexer**: Breaks input into tokens, handling quotes and special characters
2. **Parser**: Validates syntax and builds AST
3. **Expander**: Resolves variables, wildcards, and here-documents
4. **Executor**: Executes commands, handling pipes, redirections, and built-ins

### Process Management

- **Fork**: Creates child processes for external commands
- **Execve**: Replaces process image with command executable
- **Wait**: Parent process waits for children to complete
- **Pipes**: Inter-process communication for pipelines

### File Descriptor Management

The shell carefully manages file descriptors to handle:
- Standard input/output redirection
- Pipe creation and connection
- Here-document temporary files
- Saving and restoring original stdin/stdout

## 🧹 Memory Management

The project implements a **custom garbage collector** to prevent memory leaks:

- All dynamic allocations go through `ft_malloc()`
- Each allocation is tracked in a linked list
- `ft_free_all()` cleans up all allocations at exit
- Proper cleanup on error conditions

Memory safety features:
- No leaks during normal operation
- Clean exit on signals
- Proper cleanup of child processes
- File descriptor cleanup

## 👥 Contributors

- **Youness Tarhoua** ([@ytarhoua](https://github.com/Youness-Tr))
- **Abdelali Jabri** ([@ajabri](https://github.com/ajabrii))

---

## 📚 Learning Resources

This project covers important Unix/Linux concepts:

- Process management and IPC
- File I/O and descriptors
- Signal handling
- Lexical analysis and parsing
- Tree data structures
- Memory management in C

## 📄 License

This project is part of the 1337 School curriculum. Feel free to study and learn from it, but please don't copy it for your own 1337 projects.

---

**Note**: This is a learning project created as part of 1337/42Network School's curriculum. While it implements many shell features, it's not intended to replace production shells like Bash or Zsh.

For questions or issues, please open an issue on GitHub or contact the contributors.

**Made with ❤️ and lots of ☕ at 1337 School**
