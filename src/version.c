#define LIBA_VERSION_C
#include "a/version.h"

a_cstr_t a_version(void)
{
    return A_VERSION;
}

a_uint_t a_version_major(void)
{
    return A_VERSION_MAJOR;
}

a_uint_t a_version_minor(void)
{
    return A_VERSION_MINOR;
}

a_uint_t a_version_patch(void)
{
    return A_VERSION_PATCH;
}

a_int_t a_version_cmp(const a_version_s *lhs, const a_version_s *rhs)
{
    if (lhs->major < rhs->major)
    {
        return -3;
    }
    if (lhs->major > rhs->major)
    {
        return +3;
    }
    if (lhs->minor < rhs->minor)
    {
        return -2;
    }
    if (lhs->minor > rhs->minor)
    {
        return +2;
    }
    if (lhs->patch < rhs->patch)
    {
        return -1;
    }
    if (lhs->patch > rhs->patch)
    {
        return +1;
    }
    return 0;
}
