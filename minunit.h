#ifndef MINUNIT_H
#define MINUNIT_H

#include <stdio.h>
#include <string.h>

// Accumulate test results
extern int tests_run;
extern int tests_failed;
extern char test_details[1024]; // Increase size as needed for detailed output

#define mu_assert(message, test) do { \
    if (!(test)) { \
        sprintf(test_details + strlen(test_details), "FAIL: %s - %s\n", __func__, message); \
        return "fail"; \
    } \
} while (0)

#define mu_run_test(test) do { \
    char *message = test(); \
    tests_run++; \
    if (message) tests_failed++; \
} while (0)

#endif