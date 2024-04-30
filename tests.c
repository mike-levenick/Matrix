#include "minunit.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;

// Test matrix creation
static char * test_create_matrix() {

    // Create a 2x2 matrix
    Matrix mat = createMatrix(2, 2, DOUBLE);

    // Make sure it has 2 rows and 2 columns. If it doesn't, return the message
    mu_assert("error, mat.rows != 2", mat.rows == 2);
    mu_assert("error, mat.cols != 2", mat.cols == 2);

    // If all tests pass, return 0
    printf("Matrix creation test passed!\n");
    return 0;
}

// Test multiple operations. Matrix creation, element creation, and element setting
static char * test_matrix_operations() {

    // Create a matrix
    Matrix mat = createMatrix(2, 2, INT);

    // Create an element with int value 5
    MatrixElement element = {.int_val = 5};

    // Set the item at 0,0 to our element of value 5
    setMatrixElement(&mat, 0, 0, element);

    // Ensure the element at 0,0 is valued 5 as expected, or return a message
    mu_assert("error, mat.data[0][0].int_val != 5", mat.data[0][0].int_val == 5);

    // Return 0 if everything is good
    printf("Element Setting test passed!\n");
    return 0;
}

static char * test_set_row() {
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
    return 0;
}

static char* test_set_column() {
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
    return 0;
}

static char * test_create_matrix_subset_complete() {
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

    freeMatrix(&original);
    freeMatrix(&subset);
    return 0;
}

static char * test_create_matrix_subset_single_element() {
    Matrix original = createMatrix(5, 5, DOUBLE);
    original.data[2][2].double_val = 1.234;

    Matrix subset = createMatrixSubset(original, 2, 2, 2, 2);
    mu_assert("error, subset.rows != 1", subset.rows == 1);
    mu_assert("error, subset.cols != 1", subset.cols == 1);
    mu_assert("error, subset element does not match original single value", subset.data[0][0].double_val == 1.234);

    freeMatrix(&original);
    freeMatrix(&subset);
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
