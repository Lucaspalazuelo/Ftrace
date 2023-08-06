# Ftrace

## About The Project

`Ftrace` is a Epitech second year project in C to list various inputs and outputs of a program’s functions. It offers insights into:

- System calls.
- Internal function calls of a program with their names and addresses.
- Signals received from other programs.
- Function calls contained in shared libraries (.so).

## Display Format

Information is displayed in the structured manner as shown:

1. Function entry and address: `Entering function main at 0x42ff231`
2. System calls: `Syscall write(0x1, 0xff3210123, 0x1) = 0x1`
3. Signal reception: `Received signal SIGWINCH`
4. Function exit: `Leaving function my_putstr`

## Prerequisites

- Developed and tested primarily on x86-64/Linux.
- libraries: `libc`, `libelf`.

## Compilation

The program is written in `C` and comes with a `Makefile` that includes the following rules:

- `make`: Compile the program.
- `make re`: Recompile the program.
- `make clean`: Clean object files.
- `make fclean`: Clean object files and the binary.

After compilation, the binary will be named `ftrace`.


## Usage
To test the program use the binaries inside the binary folder.

Exemple :
```bash
make all

./ftrace ./binary/test1
