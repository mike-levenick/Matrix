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

### Structures and their Enums

`DataType`: an enum for tracking what type of data is stored in a given matrix.

* `INT` (the matrix contains integers)
* `DOUBLE` (the matrix contains doubles)
* `CHAR` (the matrix contains characters)

`RowOrCol`: an enum for tracking whether a row/column-wise function will operate on the row or on the column.

* `ROW` (the function should operate on the row)
* `COL` (the function should operate on the column)

`Sameness`: an enum used for a return type in a matrix-comparison function to determine the type of sameness the matricies exhibit.

* `NEITHER` (indicating the two matricies are completely different)
* `INSTANCE` (indicating instance-wise sameness)
* `ELEMENT` (indicating the matricies are different instances, but are identical on an element-by-element basis)

`RotationStatus`: an enum used as a return type in a matrix-rotating function to alert as to the success or failure of the matrix rotation

* `SUCCESS` (Value = 0. This indicates the matrix rotation was successful)
* `ERROR_NULL_POINTER` (Value = -1. This indicates the matrix rotation failed due to null values or a lack of rows/columns in a matrix)
* `ERROR_NOT_SQUARE` (Value = -2. Because rotating a matrix in-place requires that matrix to be square, this returns if it is not)

`MatrixElement`: A `union` used for the elements within the matricies to hold their values, depending on the data types

* `int_val`: The `integer` value of the element in the matrix
* `double_val`: The `double` value of the element in the matrix
* `char_val`: The `char` value of the element in the matrix

`Matrix`: The `struct` that holds the actual matricies that the library will operate on

* `rows`: An `integer` that holds the number of rows in the matrix
* `cols`: An `integer` that hold sthe number of columns in the matrix
* `data_type`: A `DataType` enum that tells what data type is stored in the matrix
* `**data`: A `MatrixElement` that holds the actual data stored in the matrix cells

### Functions List


| Function Name       | Return           | Parameters | Usage Notes |
|---------------------|------------------|------------| ---------|
| createMatrix        | `Matrix`         | `int rows, int cols, DataType data_type` | Create and return a matrix of given dimensions 
| printMatrix         | `void`           | `Matrix mat` | Print the contents of a given matrix to stdout
| getMatrixDimensions | `void`           | `Matrix mat, int *rows, int *cols` | Get the dimensions of a matrix. Does not return, but instead stores the values in return parameters `*rows` and `*cols`
| setMatrixElement    | `void`           | `Matrix *mat, int row, int col, MatrixElement data` | Set a specified element of a matrix to the provided MatrixElement
| setRowOrColumn      | `void`           | `Matrix *mat, int index, RowOrCol roc, MatrixElement *elements, int numElements` | Set an entire row or column at once
| createMatrixSubset  | `Matrix`         | `Matrix original, int startRow, int endRow, int startCol, int endCol` | Create a new, smaller matrix from a specified subset of another larger matrix
| resizeMatrix        | `void`           | `Matrix *mat, int newRows, int newCols` | Resize a given matrix to the provided dimensions
| setMatrixSubset     | `void`           | `Matrix *sourceMat, Matrix *destMat, int startRow, int startCol` | Set a subset within a matrix to that of another matrix
| getMatrixElement    | `MatrixElement`  | `Matrix mat, int row, int col` | Get a specific element from a matrix and return it
| getRowOrColumn      | `MatrixElement*` | `Matrix *mat, RowOrCol roc, int index` | Get the entire contents of a row or column of a matrix
| addMatrices         | `Matrix`         | `const Matrix *mat1, const Matrix *mat2` | Add two matricies together and return a 3rd matrix with the results
| subtractMatrices    | `Matrix`         | `const Matrix *mat1, const Matrix *mat2` | Subtract two matricies and return a 3rd matrix with the results
| multiplyMatrices    | `Matrix`         | `const Matrix *mat1, const Matrix *mat2` | Multiply two matricies and return a 3rd matrix with the results
| deepCopyMatrix      | `Matrix`         | `const Matrix *source` | Create a "deep copy" (element-by-element copy) of a given matrix, and return it
| checkMatrixSameness | `Sameness`       | `const Matrix *mat1, const Matrix *mat2` | Check if two matricies are identical instances, element-by-element identical, or not the same at all
| rotateMatrix        | `RotationStatus` | `Matrix *mat` | Rotate a matrix in place. Requires the provided matrix to be square and non-empty
| freeMatrix          | `void`           | `Matrix *mat` | Free a given matrix. 🙋 I will always free memory that I allocate
| isValid             | `int`            | `const Matrix *mat` | Returns whether or not a matrix is valid. This is primarily used in the tests
| invalidMatrix       | `Matrix`         | None | Create an invalid matrix, also primarily used in the tests. The resulting matrix will have no rows or columns
