#include "list.h"

int main(void)
{
#if defined(HAS_CXX)
    return list_c() + list_cpp();
#else /* !HAS_CXX */
    return list_c();
#endif /* HAS_CXX */
}
