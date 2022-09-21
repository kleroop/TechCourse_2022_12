#include <cstdio>
#include <cstring>
#include "CUnit/CUnit.h"

/* Pointer to the file used by the tests. */
static FILE *temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
    if ((temp_file = fopen("temp.txt", "w+")) == NULL) {
        return -1;
    } else {
        return 0;
    }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    if (fclose(temp_file) != 0) {
        return -1;
    } else {
        temp_file = NULL;
        return 0;
    }
}

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void testFPRINTF(void)
{
    int i1 = 10;

    if (temp_file != NULL) {
        CU_ASSERT(fprintf(temp_file, "") == 0);
        CU_ASSERT(fprintf(temp_file, "Q\n") == 2);
        CU_ASSERT(fprintf(temp_file, "i1 = %d", i1) == 7);
    }
}

/* Simple test of fread().
 * Reads the data previously written by testFPRINTF()
 * and checks whether the expected characters are present.
 * Must be run after testFPRINTF().
 */
void testFREAD(void)
{
    char buffer[20];

    if (temp_file != NULL) {
        rewind(temp_file);
        CU_ASSERT(fread(buffer, sizeof(unsigned char), 20, temp_file) == 9);
        CU_ASSERT(strncmp(buffer, "Q\ni1 = 10", 9) == 0);
    }
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
    /* initialize the CUnit test registry */
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    static CU_TestInfo tests[] = { { "test of fprintf()", testFPRINTF },
                                   { "test of fread()", testFREAD },
                                   CU_TEST_INFO_NULL };

    static CU_SuiteInfo suites[] = { { "Suite_1", init_suite1, clean_suite1, NULL, NULL, tests },
                                     CU_SUITE_INFO_NULL };

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if (CU_register_suites(suites) != CUE_SUCCESS) {
        goto end;
    }

    CU_run_all_tests();
end:
    CU_cleanup_registry();
    return CU_get_error();
}
