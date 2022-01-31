/*!
 @file a_vec.h
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_VEC_H__
#define __A_VEC_H__

#include "liba.h"

#include <stdlib.h> /* alloc */
#include <string.h> /* memcpy */

#ifndef a_vec_s
#define a_vec_s(_type)         \
    struct                     \
    {                          \
        size_t m; /* memory */ \
        size_t n; /* length */ \
        _type *v; /* vector */ \
    }
#endif /* a_vec_s */

#ifndef a_vec_t
#define a_vec_t(_def) a_vec_##_def##_s
#endif /* a_vec_t */
#ifndef a_vec_type
#define a_vec_type(_def, _type)     \
    typedef struct a_vec_##_def##_s \
    {                               \
        size_t m; /* memory */      \
        size_t n; /* length */      \
        _type *v; /* vector */      \
    } a_vec_##_def##_s
#endif /* a_vec_type */

#ifndef a_vec_max
#define a_vec_max(_ctx) (_ctx).m
#endif /* a_vec_max */
#ifndef a_vec_pmax
#define a_vec_pmax(_ctx) a_vec_max(*(_ctx))
#endif /* a_vec_pmax */

#ifndef a_vec_siz
#define a_vec_siz(_ctx) (_ctx).n
#endif /* a_vec_siz */
#ifndef a_vec_psiz
#define a_vec_psiz(_ctx) a_vec_siz(*(_ctx))
#endif /* a_vec_psiz */

#ifndef a_vec_v
#define a_vec_v(_ctx, _idx) (_ctx).v[(_idx)]
#endif /* a_vec_v */
#ifndef a_vec_pv
#define a_vec_pv(_ctx, _idx) a_vec_v(*(_ctx), _idx)
#endif /* a_vec_pv */

#ifndef a_vec_vp
#define a_vec_vp(_ctx, _idx) ((_ctx).v + (_idx))
#endif /* a_vec_vp */
#ifndef a_vec_pvp
#define a_vec_pvp(_ctx, _idx) a_vec_vp(*(_ctx), _idx)
#endif /* a_vec_pvp */

#ifndef a_vec_inits
#define a_vec_inits() \
    {                 \
        0, 0, 0,      \
    }
#endif /* a_vec_inits */

#ifndef a_vec_init
#define a_vec_init(_ctx) ( \
    (_ctx).m = (_ctx).n = 0, (_ctx).v = 0)
#endif /* a_vec_init */
#ifndef a_vec_pinit
#define a_vec_pinit(_def, _ctx) (                      \
    (_ctx) = (a_vec_t(_def) *)malloc(sizeof(*(_ctx))), \
    (_ctx) ? (a_vec_init(*(_ctx)), 0) : -1)
#endif /* a_vec_pinit */

#ifndef a_vec_initp
#define a_vec_initp(_def) ( \
    (a_vec_t(_def) *)calloc(1, sizeof(a_vec_t(_def))))
#endif /* a_vec_initp */

#ifndef a_vec_done
#define a_vec_done(_ctx) ( \
    (_ctx).m = (_ctx).n = 0, (_ctx).v ? (free((_ctx).v), (_ctx).v = 0) : 0)
#endif /* a_vec_done */
#ifndef a_vec_pdone
#define a_vec_pdone(_ctx) ( \
    (_ctx) ? (a_vec_done(*(_ctx)), free(_ctx), (_ctx) = 0) : 0)
#endif /* a_vec_pdone */

#ifndef a_vec_resize
#define a_vec_resize(_type, _ctx, _m) ( \
    (_ctx).m = (_m), (_ctx).v = (_type *)realloc((_ctx).v, sizeof(*(_ctx).v) * (_ctx).m))
#endif /* a_vec_resize */
#ifndef a_vec_presize
#define a_vec_presize(_type, _ctx, _m) a_vec_resize(_type, *(_ctx), _m)
#endif /* a_vec_presize */

#ifndef a_vec_vi
#define a_vec_vi(_type, _ctx, _idx) (                                         \
    (_idx) < (_ctx).m                                                         \
        ? /*i < m*/                                                           \
        (_idx) < (_ctx).n ? 0 : ((_ctx).n = (_idx) + 1, 0)                    \
        : /*m < i + 1*/                                                       \
        ((_ctx).m = (_ctx).n = (_idx) + 1, aroundup32((_ctx).m),              \
         (_ctx).v = (_type *)realloc((_ctx).v, sizeof(*(_ctx).v) * (_ctx).m), \
         0),                                                                  \
    (_ctx).v[(_idx)])
#endif /* a_vec_vi */
#ifndef a_vec_pvi
#define a_vec_pvi(_type, _ctx, _idx) a_vec_vi(_type, *(_ctx), _idx)
#endif /* a_vec_pvi */

#ifndef a_vec_vip
#define a_vec_vip(_type, _ctx, _idx) (                                        \
    (_idx) < (_ctx).m                                                         \
        ? /*i < m*/                                                           \
        (_idx) < (_ctx).n ? 0 : ((_ctx).n = (_idx) + 1, 0)                    \
        : /*m < i + 1*/                                                       \
        ((_ctx).m = (_ctx).n = (_idx) + 1, aroundup32((_ctx).m),              \
         (_ctx).v = (_type *)realloc((_ctx).v, sizeof(*(_ctx).v) * (_ctx).m), \
         0),                                                                  \
    (_ctx).v + (_idx))
#endif /* a_vec_vip */
#ifndef a_vec_pvip
#define a_vec_pvip(_type, _ctx, _idx) a_vec_vip(_type, *(_ctx), _idx)
#endif /* a_vec_pvip */

#ifndef a_vec_copy
#define a_vec_copy(_type, _dst, _src) (       \
    (_dst).m < (_src).n                       \
        ? a_vec_resize(_type, _dst, (_src).n) \
        : 0 /*_dst.m >= _src.n*/,             \
    (_dst).n = (_src).n,                      \
    memcpy((_dst).v, (_src).v, sizeof(*(_src).v) * (_src).n))
#endif /* a_vec_copy */
#ifndef a_vec_pcopy
#define a_vec_pcopy(_def, _type, _pdst, _psrc) ( \
    (_pdst) == 0                                 \
        ? a_vec_pinit(_def, _pdst)               \
        : 0 /*_pdst != 0*/,                      \
    a_vec_copy(_type, *(_pdst), *(_psrc)))
#endif /* a_vec_pcopy */

#ifndef a_vec_pop
#define a_vec_pop(_ctx) (_ctx).v[(_ctx).n ? --(_ctx).n : 0]
#endif /* a_vec_pop */
#ifndef a_vec_ppop
#define a_vec_ppop(_ctx) a_vec_pop(*(_ctx))
#endif /* a_vec_ppop */

#ifndef a_vec_popp
#define a_vec_popp(_ctx) ((_ctx).v + ((_ctx).n ? --(_ctx).n : 0))
#endif /* a_vec_popp */
#ifndef a_vec_ppopp
#define a_vec_ppopp(_ctx) a_vec_popp(*(_ctx))
#endif /* a_vec_ppopp */

#ifndef a_vec_push
#define a_vec_push(_type, _ctx, _x) (                                         \
    (_ctx).n == (_ctx).m                                                      \
        ? /*n == m*/                                                          \
        ((_ctx).m = (_ctx).m ? ((_ctx).m << 1) : 2,                           \
         (_ctx).v = (_type *)realloc((_ctx).v, sizeof(*(_ctx).v) * (_ctx).m)) \
        : 0 /*n < m*/,                                                        \
    (_ctx).v[(_ctx).n++] = (_x))
#endif /* a_vec_push */
#ifndef a_vec_ppush
#define a_vec_ppush(_type, _ctx, _x) a_vec_push(_type, *(_ctx), _x)
#endif /* a_vec_ppush */

#ifndef a_vec_pushp
#define a_vec_pushp(_type, _ctx) (                                            \
    (_ctx).n == (_ctx).m                                                      \
        ? /*n == m*/                                                          \
        ((_ctx).m = (_ctx).m ? ((_ctx).m << 1) : 2,                           \
         (_ctx).v = (_type *)realloc((_ctx).v, sizeof(*(_ctx).v) * (_ctx).m)) \
        : 0 /*n < m*/,                                                        \
    (_ctx).v + (_ctx).n++)
#endif /* a_vec_pushp */
#ifndef a_vec_ppushp
#define a_vec_ppushp(_type, _ctx) a_vec_pushp(_type, *(_ctx))
#endif /* a_vec_ppushp */

/* Enddef to prevent recursive inclusion */
#endif /* __A_VEC_H__ */
