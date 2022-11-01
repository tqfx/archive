#include "complex.h"

int main(int argc, char *argv[])
{
#if defined(HAS_CXX)
    return complex_c(argc, argv) + complex_cpp(argc, argv);
#else /* !HAS_CXX */
    return complex_c(argc, argv);
#endif /* HAS_CXX */
}
