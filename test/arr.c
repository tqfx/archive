#include "arr.h"

int main(void)
{
#if defined(HAS_CXX)
    return arr_c() + arr_cpp();
#else /* !HAS_CXX */
    return arr_c();
#endif /* HAS_CXX */
}
