#ifndef MINUNIT_H
#define MINUNIT_H

// If we fail our test, return a message
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)

// Run a test, and return the messgae if the test fails
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

// Keep track of the number of tests run
extern int tests_run;

#endif