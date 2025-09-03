# Minishell

A simple shell implementation in C, similar to Bash.

## Description

Minishell is a command interpreter that reproduces the basic behavior of a Unix shell. This project provides extensive knowledge about processes and file descriptors, allowing to understand how shells work internally.

## Features

### Core Functionality
- **Interactive prompt**: Displays a prompt when waiting for new commands
- **Command history**: Working history navigation with arrow keys
- **Program execution**: Search and launch executables based on PATH variable or using relative/absolute paths

### Signal Handling
- **Ctrl-C**: Displays a new prompt on a new line
- **Ctrl-D**: Exits the shell
- **Ctrl-\\**: Does nothing (like in bash)

### Quote Handling
- **Single quotes (`'`)**: Prevent shell from interpreting metacharacters in the quoted sequence
- **Double quotes (`"`)**: Prevent shell from interpreting metacharacters except for `$` (dollar sign)

### Redirections
- **`<`**: Redirect input
- **`>`**: Redirect output
- **`<<`**: Here document (read input until delimiter is found)
- **`>>`**: Redirect output in append mode

### Pipes
- **`|`**: Connect output of each command to the input of the next command via pipe

### Environment Variables
- **`$VARIABLE`**: Expand to their values
- **`$?`**: Expand to exit status of the most recently executed foreground pipeline

### Built-in Commands
- **`echo`** with option `-n`
- **`cd`** with only relative or absolute path
- **`pwd`** with no options
- **`export`** with no options
- **`unset`** with no options
- **`env`** with no options or arguments
- **`exit`** with no options

## Usage

```bash
./minishell
```

### Usage Examples

```bash
# Simple commands
ls -la
pwd
echo "Hello World"

# Pipes
ls | grep .c | wc -l

# Redirections
echo "test" > file.txt
cat < file.txt
echo "append" >> file.txt

# Environment variables
echo $HOME
echo $?

# Here document
cat << EOF
Line 1
Line 2
EOF

# Built-in commands
cd /tmp
pwd
export TEST_VAR=value
env | grep TEST
unset TEST_VAR
exit
```

## Technical Constraints

- **Language**: C
- **Norm**: Compliance with 42 norm
- **Memory management**: No memory leaks (except those from readline)
- **Global variable**: At most one global variable to indicate received signals
- **Allowed functions**: readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

## Error Handling

The shell handles errors similarly to bash:
- Appropriate error messages
- Correct return codes
- No crashes on user errors

## Limitations

- Does not interpret unclosed quotes or special characters not required by the subject (`\`, `;`)
- No wildcard expansion (`*`)
- No logical operators (`&&`, `||`)

## Testing

To test the shell, compare its behavior with bash:

```bash
# In bash
bash$ echo "test" | cat | wc -l

# In minishell  
minishell$ echo "test" | cat | wc -l
```