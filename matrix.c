#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// Create Matrix Function
// Accepts an int of rows, an int of columns, and then a data type enum from the header
// Returns a matrix
Matrix createMatrix(int rows, int cols, DataType data_type) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data_type = data_type;

    // Memory Allocation
    // Allocate memory for the rows.
    mat.data = (MatrixElement **)malloc(rows * sizeof(MatrixElement *));

    // Allocate memory for each set of columns within the rows.
    for (int i = 0; i < rows; i++) {
        mat.data[i] = (MatrixElement *)malloc(cols * sizeof(MatrixElement));
    }

    // Initialize matrix with zeros for doubles and integers, and null characters for chars
    // Iterate over rows
    for (int r = 0; r < rows; r++) {

        // Iterate over columns
        for (int c = 0; c < cols; c++) {

            // Switch case based on the specified data type enum
            switch (data_type) {
                // Initialize with 0s if it's an INT
                case INT:
                    mat.data[r][c].int_val = 0;
                    break;

                // Initialize with 0.0s if it's a DOUBLE
                case DOUBLE:
                    mat.data[r][c].double_val = 0.0;
                    break;

                // Initialize with NULL values if it's full of CHARs
                case CHAR:
                    mat.data[r][c].char_val = 'A';
                    break;
                default:
                    // TODO Add error handling for unknown data types
                    break;
            }
        }
    }
    // Return the initialized matrix
    return mat;
}

// Print Matrix Function
// Accepts a matrix
// Does not return
void printMatrix(Matrix mat) {

    // Iterate over rows
    for (int r = 0; r < mat.rows; r++) {

        // Iterate over columns
        for (int c = 0; c < mat.cols; c++) {

            // Switch based on the data type of the matrix
            switch (mat.data_type) {
                // Print the data in the appropriate way
                case INT:
                    printf("%d\t", mat.data[r][c].int_val);
                    break;
                case DOUBLE:
                    printf("%f\t", mat.data[r][c].double_val);
                    break;
                case CHAR:
                    printf("%c\t", mat.data[r][c].char_val);
                    break;
                default:
                    // TODO - Better error handling?
                    printf("Unknown data type\t");
            }
        }
        // Add a line break at the end of each row
        printf("\n");
    }
}

// Get matrix dimensions
// Accepts a matrix, and uses output parameters rows and cols.
// Returns void, but puts the data into the rows and columns pointers
void getMatrixDimensions(Matrix mat, int *rows, int *cols) {
    *rows = mat.rows;
    *cols = mat.cols;
}

// Set a specific element in the matrix
// Accepts a matrix, a column int, a row int, and a matrix element
// Returns void
void setMatrixElement(Matrix *mat, int row, int col, MatrixElement data) {
    // Check if the row and column indices are within the bounds of the matrix
    // TODO - Make this switchable
    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        printf("Error: Index out of bounds\n");
        return; // Exit the function if indices are out of bounds
    }

    // Assign the provided data to the specified location in the matrix
    switch (mat->data_type) {
        case INT:
            mat->data[row][col].int_val = data.int_val;
            break;
        case DOUBLE:
            mat->data[row][col].double_val = data.double_val;
            break;
        case CHAR:
            mat->data[row][col].char_val = data.char_val;
            break;
        default:
            // TODO - Better error handling?
            printf("Error: Unknown data type\n");
            break;
    }
}

// Set a specific element in the matrix
// Accepts a matrix, a column int, a row int, and a matrix element
// Returns void
MatrixElement getMatrixElement(Matrix mat, int row, int col) {
    // A default element to return if we're out of bounds
    MatrixElement defaultElement = {0};

    // Check if the row and column indices are within the bounds of the matrix
    // TODO - Make this switchable
    if (row < 0 || row >= mat.rows || col < 0 || col >= mat.cols) {
        printf("Error: Index out of bounds\n");
        return defaultElement;
    }

    return mat.data[row][col];
}

// Free the memory allocated to a matrix
void freeMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
}


int main() {
    // Example usage
    Matrix doubleMatrix = createMatrix(4, 2, DOUBLE);

    // Get matrix dimensions
    int rows, cols;
    getMatrixDimensions(doubleMatrix, &rows, &cols);
    printf("Matrix dimensions: %d rows x %d columns\n", rows, cols);

    // Set and get an element
    MatrixElement element;
    element.double_val = 3.1415;
    setMatrixElement(&doubleMatrix, 0, 0, element);

    printMatrix(doubleMatrix);

    MatrixElement retrievedElement = getMatrixElement(doubleMatrix, 0, 0);
    printf("%f\n", retrievedElement.double_val);

    // Free the matrix
    freeMatrix(&doubleMatrix);

    return 0;
}