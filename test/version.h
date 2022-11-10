#ifndef TEST_VERSION_H
#define TEST_VERSION_H
#define MAIN_(s, argc, argv) version##s(argc, argv)
#include "test.h"
#if defined(__cplusplus)
#include "a/version.hpp"
#else /* !__cplusplus */
#include "a/version.h"
#endif /* __cplusplus */

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
#if defined(__cplusplus)
    printf("version %s\n", a::version());
    printf("major %u\n", a::version_major());
    printf("minor %u\n", a::version_minor());
    printf("patch %u\n", a::version_patch());
    printf("tweak %" PRIu64 "\n", A_VERSION_TWEAK);
#else /* !__cplusplus */
    printf("version %s\n", a_version());
    printf("major %u\n", a_version_major());
    printf("minor %u\n", a_version_minor());
    printf("patch %u\n", a_version_patch());
    printf("tweak %" PRIu64 "\n", A_VERSION_TWEAK);
#endif /* __cplusplus */
    return 0;
}

#endif /* TEST_VERSION_H */
