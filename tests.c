#include "minunit.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;
int tests_failed = 0;
char test_details[1024] = {0}; // Buffer to store test results

// Test matrix creation
// Doubles
static char * test_create_double_matrix() {
    // Intro output
    const char *functionName = "Create Matrix - Double";
    printf("*** TEST START: %s ***\n", functionName);

    // Given (nothing)

    // When
    // Create a 2x2 matrix
    Matrix mat = createMatrix(2, 2, DOUBLE);
    printf("Created matrix:\n");
    printMatrix(mat);

    // Then
    // Make sure it has 2 rows and 2 columns. If it doesn't, return the message
    mu_assert("error, mat.rows != 2", mat.rows == 2);
    mu_assert("error, mat.cols != 2", mat.cols == 2);

    // cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

// Integers
static char * test_create_int_matrix() {
    // Intro output
    const char *functionName = "Create Matrix - Int";
    printf("*** TEST START: %s ***\n", functionName);

    // Given (nothing)

    // When
    // Create a 2x2 matrix
    Matrix mat = createMatrix(2, 2, INT);
    printf("Created matrix:\n");
    printMatrix(mat);

    // Then
    // Make sure it has 2 rows and 2 columns. If it doesn't, return the message
    mu_assert("error, mat.rows != 2", mat.rows == 2);
    mu_assert("error, mat.cols != 2", mat.cols == 2);

    // cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

// Doubles
static char * test_create_char_matrix() {
    // Intro output
    const char *functionName = "Create Matrix - Char";
    printf("*** TEST START: %s ***\n", functionName);

    // Given (nothing)

    // When
    // Create a 2x2 matrix
    Matrix mat = createMatrix(2, 2, CHAR);
    printf("Created matrix:\n");
    printMatrix(mat);

    // Then
    // Make sure it has 2 rows and 2 columns. If it doesn't, return the message
    mu_assert("error, mat.rows != 2", mat.rows == 2);
    mu_assert("error, mat.cols != 2", mat.cols == 2);

    // cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

// Test multiple operations. Matrix creation, element creation, and element setting
static char * test_matrix_operations() {
    // Intro output
    const char *functionName = "Multiple Matrix Operations";
    printf("*** TEST START: %s ***\n", functionName);

    // Given
    // Create a matrix
    Matrix mat = createMatrix(2, 2, INT);
    printf("Initial matrix:\n");
    printMatrix(mat);

    // Create an element with int value 5
    MatrixElement element = {.int_val = 5};

    // When
    // Set the item at 0,0 to our element of value 5
    setMatrixElement(&mat, 0, 0, element);
    printf("Matrix after setting element at 0,0:\n");
    printMatrix(mat);

    // Then
    // Ensure the element at 0,0 is valued 5 as expected, or return a message
    mu_assert("error, mat.data[0][0].int_val != 5", mat.data[0][0].int_val == 5);

    // cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

static char * test_set_row() {
    // Intro output
    const char *functionName = "Set Row";
    printf("*** TEST START: %s ***\n", functionName);

    // Given
    // Create integer matrix
    Matrix mat = createMatrix(3, 3, INT);
    printf("Initial matrix:\n");
    printMatrix(mat);

    // Values to set into matrix
    MatrixElement vals[3] = {{.int_val = 5}, {.int_val = 5}, {.int_val = 5}};

    // When
    // Set the first row with an array of values
    setRowOrColumn(&mat, 0, ROW, vals, 3);

    printf("Matrix after setting row 0 with values of 5:\n");
    printMatrix(mat);

    // Then
    // Check if all elements in the first row are set correctly
    for (int i = 0; i < mat.cols; i++) {
        mu_assert("Error: Element not set correctly in row", mat.data[0][i].int_val == 5);
    }

    // Clean up
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

static char* test_set_column() {
    // Intro output
    const char *functionName = "Set Column";
    printf("*** TEST START: %s ***\n", functionName);

    // Given
    // Create an int matrix and an element of ints
    Matrix mat = createMatrix(3, 3, INT);
    MatrixElement vals[3] = {{.int_val = 10}, {.int_val = 10}, {.int_val = 10}};

    printf("Initial matrix:\n");
    printMatrix(mat);

    // When
    // Set the second column with an array of values
    setRowOrColumn(&mat, 1, COL, vals, 3);

    printf("Matrix after setting Column:\n");
    printMatrix(mat);

    // Then
    // Check if all elements in the second column are set correctly
    for (int i = 0; i < mat.rows; i++) {
        mu_assert("Error: Element not set correctly in column", mat.data[i][1].int_val == 10);
    }

    // Clean up
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

static char * test_create_matrix_subset_complete() {
    // Intro output
    const char *functionName = "Create Subset - Complete";
    printf("*** TEST START: %s ***\n", functionName);

    // Given
    // Create a matrix
    Matrix original = createMatrix(4, 4, INT);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            original.data[r][c].int_val = r * 4 + c;
        }
    }

    printf("Initial matrix:\n");
    printMatrix(original);

    // When
    // Attempt to create a smaller matrix as a subset of the original
    Matrix subset = createMatrixSubset(original, 0, 2, 0, 2);
    printf("Subset matrix:\n");
    printMatrix(subset);

    // Then
    // Subset should have 3 rows and 3 columns
    mu_assert("error, subset.rows != 3", subset.rows == 3);
    mu_assert("error, subset.cols != 3", subset.cols == 3);

    // The data in subset should match the originals
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            mu_assert("error, subset element does not match original", subset.data[r][c].int_val == original.data[r][c].int_val);
        }
    }

    // Cleanup
    freeMatrix(&original);
    freeMatrix(&subset);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

static char * test_create_matrix_subset_single_element() {
    // Intro output
    const char *functionName = "Create Subset - Single Element";
    printf("*** TEST START: %s ***\n", functionName);

    // Given
    // Create an original matrix, and put a value in the middle of it
    Matrix original = createMatrix(5, 5, DOUBLE);
    original.data[2][2].double_val = 1.234;

    printf("Initial matrix:\n");
    printMatrix(original);

    // When
    // Create matrix from just the middle element
    Matrix subset = createMatrixSubset(original, 2, 2, 2, 2);

    printf("Single-element subset matrix:\n");
    printMatrix(subset);

    // Then
    mu_assert("error, subset.rows != 1", subset.rows == 1);
    mu_assert("error, subset.cols != 1", subset.cols == 1);
    mu_assert("error, subset element does not match original single value", subset.data[0][0].double_val == 1.234);

    // Cleanup
    freeMatrix(&original);
    freeMatrix(&subset);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

static char * test_resize_matrix_increase() {
    // Intro output
    const char *functionName = "Resize Matrix - Increase";
    printf("*** TEST START: %s ***\n", functionName);

    // Given
    // Create a 2x2 matrix and fill it with data
    Matrix mat = createMatrix(2, 2, INT);
    mat.data[0][0].int_val = 1;
    mat.data[0][1].int_val = 2;
    mat.data[1][0].int_val = 3;
    mat.data[1][1].int_val = 4;

    printf("Initial matrix:\n");
    printMatrix(mat);

    // When
    // Rresize the matrix to 3x3
    resizeMatrix(&mat, 3, 3);

    printf("Matrix after resizing:\n");
    printMatrix(mat);

    // Then
    mu_assert("error, mat.rows != 3", mat.rows == 3);
    mu_assert("error, mat.cols != 3", mat.cols == 3);
    mu_assert("error, mat.data[0][0].int_val != 1", mat.data[0][0].int_val == 1);
    mu_assert("error, mat.data[1][1].int_val != 4", mat.data[1][1].int_val == 4);
    mu_assert("error, uninitialized cell should be 0 for int", mat.data[2][2].int_val == 0);

    // Cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

static char * test_resize_matrix_decrease() {
    // Intro output
    const char *functionName = "Resize Matrix - Decrease";
    printf("*** TEST START: %s ***\n", functionName);

    // Given
    // Create a 3x3 matrix and stick a 9 in it
    Matrix mat = createMatrix(3, 3, INT);
    mat.data[2][2].int_val = 9;
    
    printf("Initial matrix:\n");
    printMatrix(mat);

    // When
    // Resize the matrix to 2x2
    resizeMatrix(&mat, 2, 2);

    printf("Resized matrix:\n");
    printMatrix(mat);

    // Then
    mu_assert("error, mat.rows != 2", mat.rows == 2);
    mu_assert("error, mat.cols != 2", mat.cols == 2);
    mu_assert("error, data beyond new dimensions should not be accessible", mat.data[1][1].int_val == 0);

    // Cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

static char * test_resize_matrix_to_zero() {
    // Intro output
    const char *functionName = "Resize Matrix - To Zero";
    printf("*** TEST START: %s ***\n", functionName);

    // Given
    // Create a 3x3 matrix
    Matrix mat = createMatrix(3, 3, INT);

    printf("Initial matrix:\n");
    printMatrix(mat);

    // Resize it down to 0x0
    resizeMatrix(&mat, 0, 0);

    printf("Resized matrix:\n");
    printMatrix(mat);

    mu_assert("error, mat.rows should be 0", mat.rows == 0);
    mu_assert("error, mat.cols should be 0", mat.cols == 0);

    // Here, we assume mat.data should be NULL or handled gracefully
    mu_assert("error, mat.data should be NULL or invalid", mat.data == NULL || mat.cols == 0);

    // Cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

static char * test_set_matrix_subset() {
    // Intro output
    const char *functionName = "Set Matrix Subset";
    printf("*** TEST START: %s ***\n", functionName);

    // Given
    // Create a larger destination matrix (4x4) and fill with 10
    Matrix destMat = createMatrix(4, 4, INT);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            destMat.data[r][c].int_val = 10;
        }
    }

    printf("Initial matrix creation:\n");
    printMatrix(destMat);

    // Create a smaller source matrix (2x2) and fill with 5
    Matrix sourceMat = createMatrix(2, 2, INT);
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 2; c++) {
            sourceMat.data[r][c].int_val = 5;
        }
    }

    printf("Smaller, destination matrix creation:\n");
    printMatrix(destMat);

    // When
    // Set the subset of destMat starting at (1, 1)
    setMatrixSubset(&sourceMat, &destMat, 1, 1);

    // Then
    // Check that the subset was copied correctly
    mu_assert("error, destMat.data[1][1].int_val != 5", destMat.data[1][1].int_val == 5);
    mu_assert("error, destMat.data[2][2].int_val != 5", destMat.data[2][2].int_val == 5);

    // Check that other parts of destMat are unchanged
    mu_assert("error, destMat.data[0][0].int_val != 10", destMat.data[0][0].int_val == 10);
    mu_assert("error, destMat.data[3][3].int_val != 10", destMat.data[3][3].int_val == 10);

    // Clean up
    freeMatrix(&destMat);
    freeMatrix(&sourceMat);
    
    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return NULL;
}

// Run the tests
static char * all_tests() {
    test_details[0] = '\0'; // Reset the details buffer

    // List of tests
    mu_run_test(test_create_double_matrix);
    mu_run_test(test_create_int_matrix);
    mu_run_test(test_create_char_matrix);
    mu_run_test(test_matrix_operations);
    mu_run_test(test_set_row);
    mu_run_test(test_set_column);
    mu_run_test(test_create_matrix_subset_complete);
    mu_run_test(test_create_matrix_subset_single_element);
    mu_run_test(test_resize_matrix_increase);
    mu_run_test(test_resize_matrix_decrease);
    mu_run_test(test_resize_matrix_to_zero);
    mu_run_test(test_set_matrix_subset);
    return 0;
}

int main() {
    all_tests();
    if (tests_failed) {
        printf("Some tests FAILED:\n%s", test_details);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return tests_failed != 0;
}
