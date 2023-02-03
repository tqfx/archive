#include "a/host/a.h"

#undef A_ALLOC_
static a_alloc_f A_ALLOC_ = a_alloc_;
a_vptr_t a_alloc(a_vptr_t vptr, a_size_t size)
{
    return A_ALLOC_(vptr, size);
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

a_void_t a_alloc_set(a_alloc_f alloc)
{
    A_ALLOC_ = alloc ? alloc : a_alloc_;
}

a_alloc_f a_alloc_get(a_void_t)
{
    if (A_ALLOC_)
    {
        return A_ALLOC_;
    }
    return a_alloc_;
}
