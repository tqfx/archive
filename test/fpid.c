#include "fpid.h"

int main(void)
{
#if defined(HAS_CXX)
    return fpid_c() + fpid_cpp();
#else /* !HAS_CXX */
    return fpid_c();
#endif /* HAS_CXX */
}
