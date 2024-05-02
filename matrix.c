#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

// I wanted a way to detect for INVALID conditions in my testing, such as
// attempting to add matricies of incompatible data types or similar.
// In these error states, I will return a specific "invalid" matrix, and this function
// is intended to detect these invalid matricies.
int isValid(const Matrix *mat) {
    // Verify our matrix isn't null, data isn't null, and our rows and columns are greater than 0.
    if (mat != NULL && mat->data != NULL && mat->rows > 0 && mat->cols > 0) {
        return 1;
    } else {
        return 0;
    }
}

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
                    mat.data[r][c].char_val = '\0';
                    break;
                default:
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
// Accepts a matrix pointer, a column int, a row int, and a matrix element
// Returns void
void setMatrixElement(Matrix *mat, int row, int col, MatrixElement data) {

    // Check if the row and column indices are within the bounds of the matrix
    #ifdef ENABLE_BOUNDS_CHECK
    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        printf("Error: Index out of bounds\n");
        return; 
    }
    #endif

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
            printf("Error: Unknown data type\n");
            break;
    }
}

// Function to set all the elements in a given row or column.
// Accepts a matrix pointer, an index for the row or column, ROC as row or column, an array of elements, and a number of elements
// Returns void
void setRowOrColumn(Matrix *mat, int index, RowOrCol roc, MatrixElement *elements, int numElements) {
    // Bounds checks which can be disabled
    #ifdef ENABLE_BOUNDS_CHECK
    if ((roc == ROW && (index < 0 || index >= mat->rows)) || 
        (roc == COL && (index < 0 || index >= mat->cols))) {
        printf("Error: Index out of bounds\n");
        return;
    }
    #endif

    // Check if we provided enough elements
    int count = (roc == ROW) ? mat->cols : mat->rows;
    if (numElements < count) {
        printf("Error: Not enough elements provided\n");
        return;
    }

    // Add the elements if everything is good
    if (roc == ROW) {
        for (int col = 0; col < mat->cols; col++) {
            setMatrixElement(mat, index, col, elements[col]);
        }
    } else {
        for (int row = 0; row < mat->rows; row++) {
            setMatrixElement(mat, row, index, elements[row]);
        }
    }
}

// Create a matrix from a subset of a larger matrix
// Accepts a matrix, a starting row, ending row, starting col, ending col
// Returns a new matrix
Matrix createMatrixSubset(Matrix original, int startRow, int endRow, int startCol, int endCol) {
    // Check bounds if we have bounds checking enabled
    #ifdef ENABLE_BOUNDS_CHECK
    if (startRow < 0 || endRow >= original.rows || startRow > endRow ||
        startCol < 0 || endCol >= original.cols || startCol > endCol) {
        printf("Error: Index out of bounds or invalid range.\n");
        exit(EXIT_FAILURE);
    }
    #endif

    // Calculate new matrix dimensions
    int rows = endRow - startRow + 1;
    int cols = endCol - startCol + 1;

    // Create new matrix
    Matrix newMatrix = createMatrix(rows, cols, original.data_type);

    // Copy data from original matrix to new matrix
    for (int r = startRow; r <= endRow; r++) {
        for (int c = startCol; c <= endCol; c++) {
            newMatrix.data[r - startRow][c - startCol] = original.data[r][c];
        }
    }

    return newMatrix;
}

// Resize a matrix
// Accepts a matrix, an int for new number of rows, and an int for new number of columns
// Returns void
void resizeMatrix(Matrix *mat, int newRows, int newCols) {

    // Perform a bounds check if enabled
    #ifdef ENABLE_BOUNDS_CHECK
    if (newRows < 0 || newCols < 0) {
        printf("Error: Invalid matrix dimensions.\n");
        return;
    }
    #endif

    // Allocate new data array
    MatrixElement **newData = malloc(newRows * sizeof(MatrixElement *));
    if (!newData) {
        printf("Memory allocation failed for new data rows.\n");
        return;
    }

    for (int i = 0; i < newRows; i++) {
        newData[i] = malloc(newCols * sizeof(MatrixElement));
        if (!newData[i]) {
            printf("Memory allocation failed for new data columns at row %d.\n", i);
            // Free already allocated rows
            for (int j = 0; j < i; j++) {
                free(newData[j]);
            }
            free(newData);
            return;
        }
    }

    // Copy data from old matrix to new matrix
    int minRows = (newRows > mat->rows) ? mat->rows : newRows;
    int minCols = (newCols > mat->cols) ? mat->cols : newCols;
    for (int r = 0; r < minRows; r++) {
        for (int c = 0; c < minCols; c++) {
            newData[r][c] = mat->data[r][c];
        }
    }

    // Free old data
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);

    // Update matrix properties
    mat->data = newData;
    mat->rows = newRows;
    mat->cols = newCols;
}

// Set matrix subset
// Accepts a source matrix, a destination matrix, and a starting row and column to put the data into.
void setMatrixSubset(Matrix *sourceMat, Matrix *destMat, int startRow, int startCol) {

    // Check if the start indices are within the bounds of the destination matrix
    #ifdef ENABLE_BOUNDS_CHECK
    if (startRow < 0 || startRow + sourceMat->rows > destMat->rows ||
        startCol < 0 || startCol + sourceMat->cols > destMat->cols) {
        fprintf(stderr, "Error: Source matrix does not fit within the destination matrix at the specified start indices.\n");
        return;
    }
    #endif

    // Copy data from source matrix to destination matrix
    for (int r = 0; r < sourceMat->rows; r++) {
        for (int c = 0; c < sourceMat->cols; c++) {
            destMat->data[startRow + r][startCol + c] = sourceMat->data[r][c];
        }
    }
}

// Set a specific element in the matrix
// Accepts a matrix, a column int, a row int, and a matrix element
// Returns void
MatrixElement getMatrixElement(Matrix mat, int row, int col) {

    // Check if the row and column indices are within the bounds of the matrix
    #ifdef ENABLE_BOUNDS_CHECK

    // A default element to return if we're out of bounds
    MatrixElement defaultElement = {0};

    if (row < 0 || row >= mat.rows || col < 0 || col >= mat.cols) {
        printf("Error: Index out of bounds\n");
        return defaultElement;
    }
    #endif

    return mat.data[row][col];
}

// Get a row or column in the matrix
// Accepts a matrix pointer, and a Row Or Column enum, along with an index
// Returns a MatrixElement pointer
MatrixElement* getRowOrColumn(Matrix *mat, RowOrCol roc, int index) {

    // Check if the index is out of bounds
    #ifdef ENABLE_BOUNDS_CHECK
    if ((roc == ROW && (index < 0 || index >= mat->rows)) || 
        (roc == COL && (index < 0 || index >= mat->cols))) {
        printf("Error: Index out of bounds\n");
        return NULL;
    }
    #endif

    // Allocate memory for the row or column 
    MatrixElement *result = NULL;

    // Get a row
    if (roc == ROW) {
        // Get a row
        // Allocate memory for the row based on the number of columns
        result = (MatrixElement *)malloc(mat->cols * sizeof(MatrixElement));

        // Catch errors with memory allocation
        if (!result) {
            printf("Memory allocation failed\n");
            return NULL;
        }

        // Put the data into the memory location
        for (int i = 0; i < mat->cols; i++) {
            result[i] = mat->data[index][i];
        }
    
    // Get a column
    } else {
        // Allocate memory for the column based on the number of rows
        result = (MatrixElement *)malloc(mat->rows * sizeof(MatrixElement));

        // Catch errors with memory allocation
        if (!result) {
            printf("Memory allocation failed\n");
            return NULL;
        }

        // Put the data into the memory location
        for (int i = 0; i < mat->rows; i++) {
            result[i] = mat->data[i][index];
        }
    }
    return result;
}

// Function to add 2 matricies together
// Accepts two different matrix pointers
// Returns a matrix
Matrix addMatrices(const Matrix *mat1, const Matrix *mat2) {
    // Confirm our matricies are the same size, or it won't work.
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        printf("Error: Matrices dimensions do not match.\n");
        exit(EXIT_FAILURE); 
    }

    // Confirm we hav ethe same data type in each matrix or it won't work
    if (mat1->data_type != mat2->data_type) {
        printf("Error: Matrices data types do not match.\n");
        exit(EXIT_FAILURE);
    }

    // Create the new matrix to store the result in
    Matrix result = createMatrix(mat1->rows, mat1->cols, mat1->data_type);

    // Perform the actual addition
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            switch (mat1->data_type) {
                case INT:
                    result.data[i][j].int_val = mat1->data[i][j].int_val + mat2->data[i][j].int_val;
                    break;
                case DOUBLE:
                    result.data[i][j].double_val = mat1->data[i][j].double_val + mat2->data[i][j].double_val;
                    break;
                case CHAR:
                    printf("Error: Addition not supported for CHAR type matrices.\n");
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }

    return result;
}

// Function to subtract 2 matricies
// Accepts two different matrix pointers
// Returns a matrix
Matrix subtractMatrices(const Matrix *mat1, const Matrix *mat2) {
    // Confirm our matricies are the same size, or it won't work.
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        printf("Error: Matrices dimensions do not match.\n");
        exit(EXIT_FAILURE); 
    }

    // Confirm we hav ethe same data type in each matrix or it won't work
    if (mat1->data_type != mat2->data_type) {
        printf("Error: Matrices data types do not match.\n");
        exit(EXIT_FAILURE);
    }

    // Create the new matrix to store the result in
    Matrix result = createMatrix(mat1->rows, mat1->cols, mat1->data_type);

    // Perform the actual addition
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            switch (mat1->data_type) {
                case INT:
                    result.data[i][j].int_val = mat1->data[i][j].int_val - mat2->data[i][j].int_val;
                    break;
                case DOUBLE:
                    result.data[i][j].double_val = mat1->data[i][j].double_val - mat2->data[i][j].double_val;
                    break;
                case CHAR:
                    printf("Error: Subtraction not supported for CHAR type matrices.\n");
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }

    return result;
}

// Function to multiply two matricies
// Accepts two different matrix pointers
// Returns a matrix
Matrix multiplyMatrices(const Matrix *mat1, const Matrix *mat2) {
    // Confirm that matrix 1 columns == matrix 2 rows otherwise it won't work.
    if (mat1->cols != mat2->rows) {
        printf("Error: Matrix dimensions do not allow multiplication (cols of mat1 must equal rows of mat2).\n");
        printf("Returning empty matrix to indicate error state.\n");
        return createMatrix(0,0,INT);
    }

    // Confirm matching data types, or it won't work.
    if (mat1->data_type != mat2->data_type) {
        printf("Error: Data types of matrices do not match.\n");
        printf("Returning empty matrix to indicate error state.\n");
        return createMatrix(0,0,INT);
    }

    // Create the result matrix with the data type from mat1 (which is also the data type of mat2)
    Matrix result = createMatrix(mat1->rows, mat2->cols, mat1->data_type);

    // Begin multiplication
    // Iterate over the rows of matrix 1
    for (int i = 0; i < mat1->rows; i++) {

        // Iterate over the columns in matrix 2
        for (int j = 0; j < mat2->cols; j++) {

            // Iterate over the columns in matrix 1
            for (int k = 0; k < mat1->cols; k++) {

                // Add the product of the row/column matches to the result matrix cells
                if (mat1->data_type == INT) {
                    result.data[i][j].int_val += mat1->data[i][k].int_val * mat2->data[k][j].int_val;
                } else if (mat1->data_type == DOUBLE) {
                    result.data[i][j].double_val += mat1->data[i][k].double_val * mat2->data[k][j].double_val;
                }
            }
        }
    }
    return result;
}

// Free the memory allocated to a matrix
void freeMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
}
