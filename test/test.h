#ifndef TEST_TEST_H
#define TEST_TEST_H

#include "a/a.h"
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

#define TEST_IS_TRUE(expression, message)                   \
    do                                                      \
    {                                                       \
        if (!(expression))                                  \
        {                                                   \
            (void)fprintf(stderr, "%s: file %s, line %i\n", \
                          message, __FILE__, __LINE__);     \
        }                                                   \
    } while (0)

#define TEST_IS_FASLE(expression, message)                  \
    do                                                      \
    {                                                       \
        if (expression)                                     \
        {                                                   \
            (void)fprintf(stderr, "%s: file %s, line %i\n", \
                          message, __FILE__, __LINE__);     \
        }                                                   \
    } while (0)

#define TEST_BUG(expression) TEST_IS_TRUE(expression, "bug")

#if defined(MAIN_)
#define MAIN_C(argc, argv) MAIN_(_c, argc, argv)
#define MAIN_CPP(argc, argv) MAIN_(_cpp, argc, argv)
#if defined(__cplusplus) == defined(HAS_CXX)
#define MAIN_ONCE 1
#endif /* __cplusplus */
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
int MAIN_C(int argc, char *argv[]);
int MAIN_CPP(int argc, char *argv[]);
#if defined(__cplusplus)
} /* extern "C" */
#define MAIN(argc, argv) MAIN_CPP(argc, argv)
#else /* !__cplusplus */
#define MAIN(argc, argv) MAIN_C(argc, argv)
#endif /* __cplusplus */
#if !defined __cplusplus
int main(int argc, char *argv[])
{
#if defined(HAS_CXX)
    return MAIN_CPP(argc, argv) + MAIN_C(argc, argv);
#else /* !HAS_CXX */
    return MAIN_C(argc, argv);
#endif /* HAS_CXX */
}
#endif /* __cplusplus */
#endif /* MAIN_ */

#endif /* TEST_TEST_H */
