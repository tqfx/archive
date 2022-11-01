#include "slist.h"

int main(void)
{
#if defined(HAS_CXX)
    return slist_c() + slist_cpp();
#else /* !HAS_CXX */
    return slist_c();
#endif /* HAS_CXX */
}
