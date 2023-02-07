#include "a/host/a.h"

static a_alloc_f a_alloc_ptr = a_alloc_;
a_alloc_f a_alloc_reg(a_alloc_f alloc)
{
    a_alloc_f ptr = a_alloc_ptr;
    if (alloc)
    {
        a_alloc_ptr = alloc;
    }
    return ptr;
}

a_vptr_t a_alloc(a_vptr_t vptr, a_size_t size)
{
    return a_alloc_ptr(vptr, size);
}

a_vptr_t a_alloc_(a_vptr_t vptr, a_size_t size)
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
