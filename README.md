# JV-Compiler

Small Java-like language made for learning purposes.

## Installation

You need to have C++ compiler with c++20 support and CMAKE version 3.16.\
Use install script to install flex, bison and submodules. After that use build script build project.

```Shell
$ git clone https://github.com/baranov-V-V/JV-Compiler.git
$ cd JV-Compiler
$ ./install.sh
$ ./build.sh
$
```

## Usage

Use `./jvc` to compile and execute programs

List of basic flags:

* `-o <filename>` creates text dump of program.
* `--emit-llvm` shows llvm ir representation of program.
* `--debug-level <debug_level>` enables debug messages of sertan level, critical level is default.
* `--dump-txt <filename>` creates text dump of program abstract syntax tree
* `--version` shows version of the compiler

For more flags info use `./jvc --help`

Example:

```Shell
$ ./jvc test/jv_programs/test_while.jv -o buzz.out
$
```
