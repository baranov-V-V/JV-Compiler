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

* `-o <filename>` specify output file name.
* `--emit-llvm` shows llvm ir representation of program.
* `--dump-ast-txt <filename>` creates text dump of program abstract syntax tree
* `--dump-ast <filename>` creates graphviz dump of program abstract syntax tree
* `--dump-table=<filename>`  - specify symbol table output filename
* `--version` shows version of the compiler
* `--debug-level <level>` enables debug messages of sertan level, critical level is default.

For more flags info use `./jvc --help`

Example:

```Shell
$ ./jvc --debug-level=TRACE --dump-table=pic/table.png --dump-ast-txt=pic/ast.txt --dump-ast=pic/ast.png test/jv_programs/classes/many_classes.jv
$
```
