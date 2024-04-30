#include "minunit.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;

// Test matrix creation
static char * test_create_matrix() {
    // Intro output
    const char *functionName = "Create Matrix";
    printf("*** TEST START: %s ***\n", functionName);

    // Create a 2x2 matrix
    Matrix mat = createMatrix(2, 2, DOUBLE);
    printf("Created matrix:\n");
    printMatrix(mat);

    // Make sure it has 2 rows and 2 columns. If it doesn't, return the message
    mu_assert("error, mat.rows != 2", mat.rows == 2);
    mu_assert("error, mat.cols != 2", mat.cols == 2);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);

    // cleanup
    freeMatrix(&mat);

    // If all tests pass, return 0
    return 0;
}

// Test multiple operations. Matrix creation, element creation, and element setting
static char * test_matrix_operations() {
    // Intro output
    const char *functionName = "Multiple Matrix Operations";
    printf("*** TEST START: %s ***\n", functionName);

    // Create a matrix
    Matrix mat = createMatrix(2, 2, INT);
    printf("Initial matrix:\n");
    printMatrix(mat);

    // Create an element with int value 5
    MatrixElement element = {.int_val = 5};

    // Set the item at 0,0 to our element of value 5
    setMatrixElement(&mat, 0, 0, element);
    printf("Matrix after setting element at 0,0:\n");
    printMatrix(mat);

    // Ensure the element at 0,0 is valued 5 as expected, or return a message
    mu_assert("error, mat.data[0][0].int_val != 5", mat.data[0][0].int_val == 5);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);

    // cleanup
    freeMatrix(&mat);

    // If all tests pass, return 0
    return 0;
}

static char * test_set_row() {
    // Intro output
    const char *functionName = "Set Row";
    printf("*** TEST START: %s ***\n", functionName);

    Matrix mat = createMatrix(3, 3, INT);
    MatrixElement vals[3] = {{.int_val = 5}, {.int_val = 5}, {.int_val = 5}};

    // Set the first row with an array of values
    setRowOrColumn(&mat, 0, ROW, vals, 3);

    // Check if all elements in the first row are set correctly
    for (int i = 0; i < mat.cols; i++) {
        mu_assert("Error: Element not set correctly in row", mat.data[0][i].int_val == 5);
    }

    // Clean up
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return 0;
}

static char* test_set_column() {
    // Intro output
    const char *functionName = "Set Column";
    printf("*** TEST START: %s ***\n", functionName);

    Matrix mat = createMatrix(3, 3, INT);
    MatrixElement vals[3] = {{.int_val = 10}, {.int_val = 10}, {.int_val = 10}};

    // Set the second column with an array of values
    setRowOrColumn(&mat, 1, COL, vals, 3);

    // Check if all elements in the second column are set correctly
    for (int i = 0; i < mat.rows; i++) {
        mu_assert("Error: Element not set correctly in column", mat.data[i][1].int_val == 10);
    }

    // Clean up
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return 0;
}

static char * test_create_matrix_subset_complete() {
    // Intro output
    const char *functionName = "Create Subset - Complete";
    printf("*** TEST START: %s ***\n", functionName);

    Matrix original = createMatrix(3, 3, INT);
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            original.data[r][c].int_val = r * 3 + c;
        }
    }

    Matrix subset = createMatrixSubset(original, 0, 2, 0, 2);
    mu_assert("error, subset.rows != 3", subset.rows == 3);
    mu_assert("error, subset.cols != 3", subset.cols == 3);
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
    return 0;
}

static char * test_create_matrix_subset_single_element() {
    // Intro output
    const char *functionName = "Create Subset - Single Element";
    printf("*** TEST START: %s ***\n", functionName);

    Matrix original = createMatrix(5, 5, DOUBLE);
    original.data[2][2].double_val = 1.234;

    Matrix subset = createMatrixSubset(original, 2, 2, 2, 2);
    mu_assert("error, subset.rows != 1", subset.rows == 1);
    mu_assert("error, subset.cols != 1", subset.cols == 1);
    mu_assert("error, subset element does not match original single value", subset.data[0][0].double_val == 1.234);

    // Cleanup
    freeMatrix(&original);
    freeMatrix(&subset);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return 0;
}

static char * test_resize_matrix_increase() {
    // Intro output
    const char *functionName = "Resize Matrix - Increase";
    printf("*** TEST START: %s ***\n", functionName);

    Matrix mat = createMatrix(2, 2, INT);
    mat.data[0][0].int_val = 1;
    mat.data[0][1].int_val = 2;
    mat.data[1][0].int_val = 3;
    mat.data[1][1].int_val = 4;

    resizeMatrix(&mat, 3, 3);

    mu_assert("error, mat.rows != 3", mat.rows == 3);
    mu_assert("error, mat.cols != 3", mat.cols == 3);
    mu_assert("error, mat.data[0][0].int_val != 1", mat.data[0][0].int_val == 1);
    mu_assert("error, mat.data[1][1].int_val != 4", mat.data[1][1].int_val == 4);
    mu_assert("error, uninitialized cell should be 0 for int", mat.data[2][2].int_val == 0);

    // Cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return 0;
}

static char * test_resize_matrix_decrease() {
    // Intro output
    const char *functionName = "Resize Matrix - Decrease";
    printf("*** TEST START: %s ***\n", functionName);

    Matrix mat = createMatrix(3, 3, INT);
    mat.data[2][2].int_val = 9;

    resizeMatrix(&mat, 2, 2);

    mu_assert("error, mat.rows != 2", mat.rows == 2);
    mu_assert("error, mat.cols != 2", mat.cols == 2);
    mu_assert("error, data beyond new dimensions should not be accessible", mat.data[1][1].int_val == 0);

    // Cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return 0;
}

static char * test_resize_matrix_to_zero() {
    // Intro output
    const char *functionName = "Resize Matrix - To Zero";
    printf("*** TEST START: %s ***\n", functionName);

    Matrix mat = createMatrix(3, 3, INT);

    resizeMatrix(&mat, 0, 0);

    mu_assert("error, mat.rows should be 0", mat.rows == 0);
    mu_assert("error, mat.cols should be 0", mat.cols == 0);

    // Here, we assume mat.data should be NULL or handled gracefully
    mu_assert("error, mat.data should be NULL or invalid", mat.data == NULL || mat.cols == 0);

    // Cleanup
    freeMatrix(&mat);

    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return 0;
}

static char * test_set_matrix_subset() {
    // Intro output
    const char *functionName = "Set Matrix Subset";
    printf("*** TEST START: %s ***\n", functionName);

    // Create a larger destination matrix (4x4) and fill with 10
    Matrix destMat = createMatrix(4, 4, INT);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            destMat.data[r][c].int_val = 10;
        }
    }

    // Create a smaller source matrix (2x2) and fill with 5
    Matrix sourceMat = createMatrix(2, 2, INT);
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 2; c++) {
            sourceMat.data[r][c].int_val = 5;
        }
    }

    // Set the subset of destMat starting at (1, 1)
    setMatrixSubset(&sourceMat, &destMat, 1, 1);

    // Check that the subset was copied correctly
    mu_assert("error, destMat.data[1][1].int_val != 5", destMat.data[1][1].int_val == 5);
    mu_assert("error, destMat.data[2][2].int_val != 5", destMat.data[2][2].int_val == 5);

    // Check that other parts of destMat are unchanged
    mu_assert("error, destMat.data[0][0].int_val != 10", destMat.data[0][0].int_val == 10);
    mu_assert("error, destMat.data[3][3].int_val != 10", destMat.data[3][3].int_val == 10);

    printMatrix(destMat);

    // Clean up
    freeMatrix(&destMat);
    freeMatrix(&sourceMat);
    
    // Success output
    printf("*** TEST PASSED: %s ***\n", functionName);
    return 0;
}

// Run the tests
static char * all_tests() {

    // List of tests
    mu_run_test(test_create_matrix);
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
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
