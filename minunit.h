#ifndef MINUNIT_H
#define MINUNIT_H

#include <stdio.h>
#include <string.h>

// Accumulate test results
// Total tests ran
extern int tests_run;

// Tests failed
extern int tests_failed;

// Details about the failures
extern char test_details[1024];

// Assertion
// If the test fails (test == false), add the test details for the test to the buffer
// And then return "fail"
#define mu_assert(message, test) do { \
    if (!(test)) { \
        sprintf(test_details + strlen(test_details), "FAIL: %s - %s\n", __func__, message); \
        return "fail"; \
    } \
} while (0)

// For each test that is run, increment the number of tests run
// If we get a message back (which indicates a failure), increment failed_tests
#define mu_run_test(test) do { \
    char *message = test(); \
    tests_run++; \
    if (message) tests_failed++; \
} while (0)

#endif