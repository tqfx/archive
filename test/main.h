#ifndef TEST_MAIN_H
#define TEST_MAIN_H
#define MAIN_(s, argc, argv) main##s(argc, argv)
#include "test.h"

static int test(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    return 0;
}

int MAIN(int argc, char *argv[])
{
    printf(__func__);
#if defined(MAIN_OUTPUT)
    printf(" ok");
#endif /* MAIN_OUTPUT */
    putchar('\n');
    test(argc, argv);
    return 0;
}

#endif /* TEST_MAIN_H */
