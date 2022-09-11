#include "lib.h"
#include "a/version.h"

EM_PORT_API(a_cstr_t)
version(void) { return a_version(); }

EM_PORT_API(a_uint_t)
version_major(void) { return a_version_major(); }

EM_PORT_API(a_uint_t)
version_minor(void) { return a_version_minor(); }

EM_PORT_API(a_uint_t)
version_patch(void) { return a_version_patch(); }
