#include "pid.h"

int main(void)
{
#if defined(HAS_CXX)
    return pid_c() + pid_cpp();
#else /* !HAS_CXX */
    return pid_c();
#endif /* HAS_CXX */
}
