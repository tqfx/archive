#include "a/a.h"

#include <stdio.h>
#include <inttypes.h>
#include "a/version.h"

A_STATIC a_int_t version_c(void)
{
    printf("%s\n", __func__);
    printf("version %s\n", a_version());
    printf("major %u\n", a_version_major());
    printf("minor %u\n", a_version_minor());
    printf("patch %u\n", a_version_patch());
    printf("tweak %" PRIu64 "\n", A_VERSION_TWEAK);
    return A_SUCCESS;
}

#include <iostream>
#include "a/version.hpp"

A_STATIC a_int_t version_cpp(void)
{
    printf("%s\n", __func__);
    std::cout << "version " << a::version() << std::endl;
    std::cout << "major " << a::version_major() << std::endl;
    std::cout << "minor " << a::version_minor() << std::endl;
    std::cout << "patch " << a::version_patch() << std::endl;
    std::cout << "tweak " << A_VERSION_TWEAK << std::endl;
    return A_SUCCESS;
}

int main(void)
{
    return version_c() + version_cpp();
}
