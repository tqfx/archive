#include "polytrack.h"

int main(void)
{
#if defined(HAS_CXX)
    return polytrack_c() + polytrack_cpp();
#else /* !HAS_CXX */
    return polytrack_c();
#endif /* HAS_CXX */
}
