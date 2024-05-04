# Matrix Library

### Overview
This is a matrix library written by Michael Levenick for CS252, Spring Semester 2024. It contains several necessary functions for creation, deletion, and modification of Matricies in C.

### Compiling and Testing
__Cleanup:__ Between subsequent attempts at testing or running, it is wise to run a `make clean` command to clean up leftover files. This can be linked with the compile or test command, such as `make clean && make test`. 

__Testing:__ The matrix library contains a makefile which allows for ease of compilation and testing. In order to run the test suite, run the command `make test`. The tests will compile as an executable and then run, dumping test results to stdout. There will be a report at the end with a list of total tests run, failed tests, and a passing percentage.

__Compilation:__ The matrix library itself does not contain a `main` function, and thus will not be compiled as an executable. The `make` command will compile the file as `libmatrix.a` instead.

### Compile Flags
There are two majors options that can be modified at compile time by changing CFLAGS in the makefile.

__Optional Bounds Checking:__ Bounds checking is good. By default, this library will always protect you with bounds checking. If, however, you like to live dangerously, you may disable bounds checks by commenting out the appropriate CFLAG in the makefile.

```
CFLAGS += -DENABLE_BOUNDS_CHECK
```

__Row Major vs Column Major Storage:__ The matrix library supports both row major and column major storage. In order to swap between them, uncomment one of the CFLAGS near the top of the makefile. One of these options must be uncommented. By default, the matrix library uses row major storage.

```
#CFLAGS += -DROW_MAJOR_ORDER
CFLAGS += -DCOLUMN_MAJOR_ORDER
```

### Example Usage
Below this section is another section that will actually tell you all the functions available to you here, as well as their usage. That said, no one ever RTFMs, so here's a block of code to get you started.

```
// Create and add two matricies of type INT and view all their contents

// Create the first matrix
Matrix mat1 = createMatrix(4, 4, INT);

// Fill it with ints from 0 to 15
for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
        mat1.data[r][c].int_val = r * 4 + c;
    }
}

// See what's inside:
printf("Initial matrix 1:\n");
printMatrix(mat1);

// Create the second matrix
Matrix mat2 = createMatrix(4, 4, INT);

// Fill it with ints from 10 to 25
for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
        mat2.data[r][c].int_val = r * 4 + c + 10;
    }
}

// See what's inside:
printf("Initial matrix 2:\n");
printMatrix(mat2);

// Add the two matricies together
Matrix matResult = addMatrices(&mat1, &mat2);

// View the resulting matrix:
printf("Resulting matrix after addition:\n");
printMatrix(matResult);

// 🙋 I will always free memory that I allocate
freeMatrix(&mat1);
freeMatrix(&mat2);
freeMatrix(&matResult);
```

### Functions List
| Function Name       | Parameters | Return | Special Notes |
|---------------------|----------|----------| ---------|
| createMatrix        | `int`: rows `int`: cols | Row1Col3 | 
| printMatrix         | Row2Col2 | Row2Col3 |
| getMatrixDimensions | Row3Col2 | Row3Col3 |
| setMatrixElement    | Row3Col2 | Row3Col3 |
| setRowOrColumn      | Row3Col2 | Row3Col3 |
| createMatrixSubset  | Row3Col2 | Row3Col3 |
| resizeMatrix        | Row3Col2 | Row3Col3 |
| setMatrixSubset     | Row3Col2 | Row3Col3 |
| getMatrixElement    | Row3Col2 | Row3Col3 |
| getRowOrColumn      | Row3Col2 | Row3Col3 |
| addMatrices         | Row3Col2 | Row3Col3 |
| subtractMatrices    | Row3Col2 | Row3Col3 |
| multiplyMatrices    | Row3Col2 | Row3Col3 |
| checkMatrixSameness | Row3Col2 | Row3Col3 |
| rotateMatrix        | Row3Col2 | Row3Col3 |
| freeMatrix          | Row3Col2 | Row3Col3 |


