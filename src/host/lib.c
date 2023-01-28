#include "a/host/a.h"

a_vptr_t a_alloc(a_vptr_t vptr, a_size_t size)
{
    if (size)
    {
        if (vptr)
        {
            return realloc(vptr, size);
        }
        return malloc(size);
    }
    free(vptr);
    return A_NULL;
}
