# JV-Compiler

Small Java-like language made for learning purposes.

## Installation

Use install script to install flex, bison and submodules.

```Shell
$ git clone https://github.com/baranov-V-V/JV-Compiler.git
$ cd JV-Compiler
$ ./install.sh
$ ./build.sh
$
```

## Usage

Use run script to compile and execute programs

The list of possible flags:

* `-d (--dump)` creates text dump of program.
* `-s (--scan)` enables flex scanner debug messages.
* `-p (--parse)` enables bison parser debug messages.

Example:

```Shell
$ ./run.sh -d test/examples/test_while.jv
$
```
