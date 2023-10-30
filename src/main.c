#include <stdio.h>

#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            printf("Assertion failed: %s, file %s, line %d\n", #condition, __FILE__, __LINE__); \
            return 1; \
        } \
    } while (0)

int dummy_test_1()
{
    ASSERT_TRUE(2 == 2);
    return 0;
}

int (*all_tests[])() =
{
    dummy_test_1,
    NULL
};

int run_all_tests()
{
    int rc = 0;
    for (int i=0; all_tests[i]; i++)
    {
        int tmp = all_tests[i]();
        printf("Test %i [%s]\n", i, tmp ? "FAIL" : "PASS");
        rc |= tmp;
    }
    return rc;
}

int main()
{
    if (run_all_tests())
    {
        printf("Some tests failed\n");
        return 1;
    }

    printf("All tests passed!\n");
    return 0;
}
