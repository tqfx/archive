#include "lib.h"
#include "a/math.h"

EM_PORT_API(float)
inv_sqrt(float x) { return a_inv_sqrt(x); }
