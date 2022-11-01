#include "for.h"

int main(void)
{
#if defined(HAS_CXX)
    return for_c() + for_cpp();
#else /* !HAS_CXX */
    return for_c();
#endif /* HAS_CXX */
}
