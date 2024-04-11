#ifndef MATRIX_H
#define MATRIX_H

// An enum that allows us to specify the type of data our matrix will be filled with.
typedef enum {
    INT,
    DOUBLE,
    CHAR
} DataType;


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

// Function prototypes
// A create matrix prototype
Matrix createMatrix(int rows, int cols, DataType data_type);

// A print matrix prototype
void printMatrix(Matrix mat);

#endif /* MATRIX_H */