#ifndef __LIB_H__
#define __LIB_H__

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* diagnostic */
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#endif /* __clang__ */
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */

#include "liba_ac.h"
#include "liba_ac_pid.h"
#include "liba_ac_polytrack3.h"
#include "liba_ac_polytrack5.h"
#include "liba_ac_polytrack7.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */

#define CLASSPATH "liba/ac$"

#endif /* __LIB_H__ */
