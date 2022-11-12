/*!
 @file a.config.h
 @brief algorithm library configuration
 @details it is autogenerated by xmake ${XMAKE_VERSION}
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef LIBA_CONFIG_H
#define LIBA_CONFIG_H

/* clang-format off */

${define A_BYTE_ORDER}
#if !defined A_REAL_BYTE
${define A_REAL_BYTE}
#endif /* A_REAL_BYTE */
${define A_SIZE_PTR}
#define A_VERSION "${VERSION}"
#define A_VERSION_MAJOR ${VERSION_MAJOR}
#define A_VERSION_MINOR ${VERSION_MINOR}
#define A_VERSION_PATCH ${VERSION_ALTER}
#define A_VERSION_TWEAK A_U64_C(${VERSION_BUILD})

${define A_HAVE_COMPLEX_H}
${define A_HAVE_STDINT_H}
${define A_HAVE_HYPOT}
${define A_HAVE_LOG1P}
${define A_HAVE_ATAN2}
${define A_HAVE_CSQRT}
${define A_HAVE_CPOW}
${define A_HAVE_CEXP}
${define A_HAVE_CLOG}
${define A_HAVE_CSIN}
${define A_HAVE_CCOS}
${define A_HAVE_CTAN}
${define A_HAVE_CSINH}
${define A_HAVE_CCOSH}
${define A_HAVE_CTANH}
${define A_HAVE_CASIN}
${define A_HAVE_CACOS}
${define A_HAVE_CATAN}
${define A_HAVE_CASINH}
${define A_HAVE_CACOSH}
${define A_HAVE_CATANH}

/* clang-format on */

#endif /* LIBA_CONFIG_H */
