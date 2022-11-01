#include "vector.h"

int main(void)
{
#if defined(HAS_CXX)
    return vector_c() + vector_cpp();
#else /* !HAS_CXX */
    return vector_c();
#endif /* HAS_CXX */
}
