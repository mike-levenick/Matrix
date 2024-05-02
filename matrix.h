#ifndef MATRIX_H
#define MATRIX_H

// An enum that allows us to specify the type of data our matrix will be filled with.
typedef enum {
    INT,
    DOUBLE,
    CHAR
} DataType;

// Enum that we can use to select if we're getting a row or a column
typedef enum {
    ROW,
    COL
} RowOrCol;

// A union to use for our actual elements that will go into the matrix
typedef union {
    int int_val;
    double double_val;
    char char_val;
} MatrixElement;

// Struct for matrix, with rows, columns, data type, and elements
typedef struct {
    int rows;
    int cols;
    DataType data_type;
    MatrixElement **data;
} Matrix;

// MARK - Function prototypes

// Detect invalid return matricies
int isValid(const Matrix *mat);

// A create matrix prototype
Matrix createMatrix(int rows, int cols, DataType data_type);

// A print matrix prototype
void printMatrix(Matrix mat);

// Get matrix dimensions
void getMatrixDimensions(Matrix mat, int *rows, int *cols);

// Set matrix element
void setMatrixElement(Matrix *mat, int row, int col, MatrixElement data);

// Set row or column
void setRowOrColumn(Matrix *mat, int index, RowOrCol roc, MatrixElement *elements, int numElements);

// Create a matrix from a subset of a larger matrix
Matrix createMatrixSubset(Matrix original, int startRow, int endRow, int startCol, int endCol);

// Resize a matrix
void resizeMatrix(Matrix *mat, int newRows, int newCols);

// Replace a subset of a matrix
void setMatrixSubset(Matrix *sourceMat, Matrix *destMat, int startRow, int startCol);

// Get matrix element
MatrixElement getMatrixElement(Matrix mat, int row, int col);

// Get row or column
MatrixElement* getRowOrColumn(Matrix *mat, RowOrCol roc, int index);

// Add matricies
Matrix addMatrices(const Matrix *mat1, const Matrix *mat2);

// Subtract matricies
Matrix subtractMatrices(const Matrix *mat1, const Matrix *mat2);

// Multiply Matricies
Matrix multiplyMatrices(const Matrix *mat1, const Matrix *mat2);

// Free the memory from a matrix
void freeMatrix(Matrix *mat);

#endif