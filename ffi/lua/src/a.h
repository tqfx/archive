#ifndef L_A_H
#define L_A_H

#include "api.h"

#define AMODULE(F) liba_##F
#define AMODULE1(F, a) liba_##F(a)
#define AMODULE2(F, a, b) liba_##F(a, b)
#define AMODULE_(F, L) luaopen_liba##F(L)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int AMODULE_(, lua_State *L);
A_PUBLIC int AMODULE_(_mf, lua_State *L);
A_PUBLIC int AMODULE_(_tf, lua_State *L);
A_PUBLIC int AMODULE_(_pid, lua_State *L);
A_PUBLIC int AMODULE_(_fpid, lua_State *L);
A_PUBLIC int AMODULE_(_complex, lua_State *L);
A_PUBLIC int AMODULE_(_polytrack3, lua_State *L);
A_PUBLIC int AMODULE_(_polytrack5, lua_State *L);
A_PUBLIC int AMODULE_(_polytrack7, lua_State *L);
A_PUBLIC int AMODULE_(_version, lua_State *L);
A_PUBLIC int AMODULE(setter)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* L_A_H */
