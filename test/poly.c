#include "poly.h"

int main(void)
{
#if defined(HAS_CXX)
    return poly_c() + poly_cpp();
#else /* !HAS_CXX */
    return poly_c();
#endif /* HAS_CXX */
}
