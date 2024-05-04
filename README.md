# Matrix Library

### Overview
This is a matrix library written by Michael Levenick for CS252, Spring Semester 2024. It contains several necessary functions for creation, deletion, and modification of Matricies in C.

### Compiling and Testing
__Cleanup:__ Between subsequent attempts at testing or running, it is wise to run a `make clean` command to clean up leftover files. This can be linked with the compile or test command, such as `make clean && make test`. 

__Testing:__ The matrix library contains a makefile which allows for ease of compilation and testing. In order to run the test suite, run the command `make test`. The tests will compile as an executable and then run, dumping test results to stdout. There will be a report at the end with a list of total tests run, failed tests, and a passing percentage.

__Compilation:__ The matrix library itself does not contain a `main` function, and thus will not be compiled as an executable. The `make` command will compile the file as `libmatrix.a` instead.

### Row Major vs Column Major Storage
The matrix library supports both row major and column major storage. This selection is made at compile time, and is selected 