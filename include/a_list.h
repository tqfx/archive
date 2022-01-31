/*!
 @file a_list.h
 @brief Generic single-linked list and memory pool
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_LIST_H__
#define __A_LIST_H__

#include "liba.h"

#include <stdlib.h> /* alloc */

#ifndef a_mempool_s
#define a_mempool_s(_type)             \
    struct                             \
    {                                  \
        size_t m;  /* really memory */ \
        size_t n;  /* unused memory */ \
        size_t a;  /* memory alloc */  \
        _type **p; /* memory table */  \
    }
#endif /* a_mempool_s */

#ifndef a_mempool_t
#define a_mempool_t(_def) a_mempool_##_def##_s
#endif /* a_mempool_t */
#ifndef a_mempool_type
#define a_mempool_type(_def, _type)     \
    typedef struct a_mempool_##_def##_s \
    {                                   \
        size_t m;  /* really memory */  \
        size_t n;  /* unused memory */  \
        size_t a;  /* memory alloc */   \
        _type **p; /* memory table */   \
    } a_mempool_##_def##_s
#endif /* a_mempool_type */

#ifndef a_mempool_inits
#define a_mempool_inits() \
    {                     \
        0, 0, 0, 0,       \
    }
#endif /* a_mempool_inits */

#ifndef a_mempool_init
#define a_mempool_init(_ctx) ( \
    (_ctx).m = (_ctx).n = (_ctx).a = 0, (_ctx).p = 0)
#endif /* a_mempool_init */

#ifndef a_mempool_pinit
#define a_mempool_pinit(_def, _ctx) (                      \
    (_ctx) = (a_mempool_t(_def) *)malloc(sizeof(*(_ctx))), \
    (_ctx) ? (a_mempool_init(*(_ctx)), 0) : -1)
#endif /* a_mempool_pinit */

#ifndef a_mempool_initp
#define a_mempool_initp(_def) ( \
    (a_mempool_t(_def) *)calloc(1, sizeof(a_mempool_t(_def))))
#endif /* a_mempool_initp */

#ifndef a_mempool_done
#define a_mempool_done(_ctx, _func)    \
    do                                 \
    {                                  \
        while ((_ctx).n)               \
        {                              \
            --(_ctx).n;                \
            _func((_ctx).p[(_ctx).n]); \
            free((_ctx).p[(_ctx).n]);  \
            (_ctx).p[(_ctx).n] = 0;    \
        }                              \
        if ((_ctx).m)                  \
        {                              \
            free((_ctx).p);            \
            (_ctx).p = 0;              \
            (_ctx).m = 0;              \
        }                              \
    } while (0)
#endif /* a_mempool_done */
#ifndef a_mempool_pdone
#define a_mempool_pdone(_ctx, _func)        \
    do                                      \
    {                                       \
        if (_ctx)                           \
        {                                   \
            a_mempool_done(*(_ctx), _func); \
            free(_ctx);                     \
            (_ctx) = 0;                     \
        }                                   \
    } while (0)
#endif /* a_mempool_pdone */

/* a_mempool_alloc */
#ifndef a_mempool_alloc
#define a_mempool_alloc(_type, _ctx) (      \
    ++(_ctx).a,                             \
    (_ctx).n == 0                           \
        ? /*0 = n*/                         \
        (_type *)malloc(sizeof(**(_ctx).p)) \
        : /*n > 0*/                         \
        (_ctx).p[--(_ctx).n])
#endif /* a_mempool_alloc */
/* a_mempool_palloc */
#ifndef a_mempool_palloc
#define a_mempool_palloc(_type, _ctx) a_mempool_alloc(_type, *(_ctx))
#endif /* a_mempool_palloc */

#ifndef a_mempool_free
#define a_mempool_free(_type, _ctx, _pdat) (                                   \
    --(_ctx).a,                                                                \
    (_ctx).n == (_ctx).m                                                       \
        ? /*n == m*/                                                           \
        ((_ctx).m = (_ctx).m ? ((_ctx).m << 1) : 0x10,                         \
         (_ctx).p = (_type **)realloc((_ctx).p, sizeof(*(_ctx).p) * (_ctx).m)) \
        : 0 /*n < m*/,                                                         \
    (_ctx).p[(_ctx).n++] = (_pdat))
#endif /* a_mempool_free */
#ifndef a_mempool_pfree
#define a_mempool_pfree(_type, _ctx, _pdat) a_mempool_free(_type, *(_ctx), _pdat)
#endif /* a_mempool_pfree */

#ifndef a_list1_t
#define a_list1_t(_def) a_list1_##_def##_s
#endif /* a_list1_t */
#ifndef a_list1_type
#define a_list1_type(_def, _type)        \
    typedef struct a_list1_##_def##_s    \
    {                                    \
        struct a_list1_##_def##_s *next; \
        _type data;                      \
    } a_list1_##_def##_s
#endif /* a_list1_type */

#ifndef a_list1_data
#define a_list1_data(_ctx) (_ctx)->data
#endif /* a_list1_data */

#ifndef a_list1_next
#define a_list1_next(_ctx) (_ctx)->next
#endif /* a_list1_next */

#ifndef a_list2_t
#define a_list2_t(_def) a_list2_##_def##_s
#endif /* a_list2_t */
#ifndef a_list2_type
#define a_list2_type(_def, _type)        \
    typedef struct a_list2_##_def##_s    \
    {                                    \
        struct a_list2_##_def##_s *last; \
        struct a_list2_##_def##_s *next; \
        _type data;                      \
    } a_list2_##_def##_s
#endif /* a_list2_type */

#ifndef a_list2_data
#define a_list2_data(_ctx) (_ctx)->data
#endif /* a_list2_data */

#ifndef a_list2_next
#define a_list2_next(_ctx) (_ctx)->next
#endif /* a_list2_next */

#ifndef a_list2_last
#define a_list2_last(_ctx) (_ctx)->last
#endif /* a_list2_last */

#ifndef a_list_t
#define a_list_t(_def) a_list_##_def##_s
#endif /* a_list_t */
#ifndef a_list_type
#define a_list_type(_def, _type)           \
    a_list1_type(_def, _type);             \
    a_mempool_type(_def, a_list1_t(_def)); \
    typedef struct a_list_##_def##_s       \
    {                                      \
        a_list1_t(_def) * head;            \
        a_list1_t(_def) * tail;            \
        a_mempool_t(_def) mem;             \
        size_t siz;                        \
    } a_list_##_def##_s
#endif /* a_list_type */

#ifndef a_list_head
#define a_list_head(_ctx) (_ctx).head
#endif /* a_list_head */
#ifndef a_list_phead
#define a_list_phead(_ctx) a_list_head(*(_ctx))
#endif /* a_list_phead */

#ifndef a_list_tail
#define a_list_tail(_ctx) (_ctx).tail
#endif /* a_list_tail */
#ifndef a_list_ptail
#define a_list_ptail(_ctx) a_list_tail(*(_ctx))
#endif /* a_list_ptail */

#ifndef a_list_mem
#define a_list_mem(_ctx) (_ctx).mem
#endif /* a_list_mem */
#ifndef a_list_pmem
#define a_list_pmem(_ctx) a_list_mem(*(_ctx))
#endif /* a_list_pmem */

#ifndef a_list_siz
#define a_list_siz(_ctx) (_ctx).siz
#endif /* a_list_siz */
#ifndef a_list_psiz
#define a_list_psiz(_ctx) a_list_siz(*(_ctx))
#endif /* a_list_psiz */

#ifndef a_list_init
#define a_list_init(_def, _ctx) (                                             \
    a_mempool_init((_ctx).mem),                                               \
    (_ctx).tail = (_ctx).head = a_mempool_alloc(a_list1_t(_def), (_ctx).mem), \
    (_ctx).tail->next = 0,                                                    \
    (_ctx).siz = 0)
#endif /* a_list_init */
#ifndef a_list_pinit
#define a_list_pinit(_def, _ctx) (                      \
    (_ctx) = (a_list_t(_def) *)malloc(sizeof(*(_ctx))), \
    (_ctx) ? (a_list_init(_def, *(_ctx)), 0) : -1)
#endif /* a_list_pinit */

#ifndef a_list_done
#define a_list_done(_def, _ctx, _func)                                \
    do                                                                \
    {                                                                 \
        while ((_ctx).head)                                           \
        {                                                             \
            a_mempool_free(a_list1_t(_def), (_ctx).mem, (_ctx).head); \
            (_ctx).head = (_ctx).head->next;                          \
        }                                                             \
        a_mempool_done((_ctx).mem, _func);                            \
        (_ctx).tail = 0;                                              \
        (_ctx).siz = 0;                                               \
    } while (0)
#endif /* a_list_done */
#ifndef a_list_pdone
#define a_list_pdone(_def, _ctx, _func)        \
    do                                         \
    {                                          \
        if (_ctx)                              \
        {                                      \
            a_list_done(_def, *(_ctx), _func); \
            free(_ctx);                        \
            (_ctx) = 0;                        \
        }                                      \
    } while (0)
#endif /* a_list_pdone */

#ifndef a_list_push
#define a_list_push(_def, _ctx, _x) (                                 \
    ++(_ctx).siz,                                                     \
    (_ctx).tail->next = a_mempool_alloc(a_list1_t(_def), (_ctx).mem), \
    (_ctx).tail = (_ctx).tail->next,                                  \
    (_ctx).tail->data = (_x),                                         \
    (_ctx).tail->next = 0)
#endif /* a_list_push */
#ifndef a_list_ppush
#define a_list_ppush(_def, _ctx, _x) a_list_push(_def, *(_ctx), _x)
#endif /* a_list_ppush */

#ifndef a_list_pushp
#define a_list_pushp(_def, _ctx) (                                    \
    ++(_ctx).siz,                                                     \
    (_ctx).tail->next = a_mempool_alloc(a_list1_t(_def), (_ctx).mem), \
    (_ctx).tail = (_ctx).tail->next,                                  \
    (_ctx).tail->next = 0,                                            \
    &(_ctx).tail->data)
#endif /* a_list_pushp */
#ifndef a_list_ppushp
#define a_list_ppushp(_def, _ctx) a_list_pushp(_def, *(_ctx))
#endif /* a_list_ppushp */

#ifndef a_list_ins
#define a_list_ins(_def, _ctx, _x)                                          \
    do                                                                      \
    {                                                                       \
        ++(_ctx).siz;                                                       \
        a_list1_t(_def) *_p = a_mempool_alloc(a_list1_t(_def), (_ctx).mem); \
        _p->next = (_ctx).head->next;                                       \
        (_ctx).head->next = _p;                                             \
        _p->data = (_x);                                                    \
    } while (0)
#endif /* a_list_ins */
#ifndef a_list_pins
#define a_list_pins(_def, _ctx, _x) a_list_ins(_def, *(_ctx), _x)
#endif /* a_list_pins */

#ifndef a_list_insp
#define a_list_insp(_def, _ctx, _px)                                        \
    do                                                                      \
    {                                                                       \
        ++(_ctx).siz;                                                       \
        a_list1_t(_def) *_p = a_mempool_alloc(a_list1_t(_def), (_ctx).mem); \
        _p->next = (_ctx).head->next;                                       \
        (_ctx).head->next = _p;                                             \
        (_px) = &_p->data;                                                  \
    } while (0)
#endif /* a_list_insp */
#ifndef a_list_pinsp
#define a_list_pinsp(_def, _ctx, _px) a_list_insp(_def, *(_ctx), _px)
#endif /* a_list_pinsp */

#ifndef a_list_pop
#define a_list_pop(_def, _ctx, _x) (                                     \
    (_ctx).head->next                                                    \
        ? /*head->next != 0*/                                            \
        (--(_ctx).siz,                                                   \
         (_x) = (_ctx).head->next->data,                                 \
         a_mempool_free(a_list1_t(_def), (_ctx).mem, (_ctx).head->next), \
         (_ctx).head->next = (_ctx).head->next->next,                    \
         0)                                                              \
        : /*head->next == 0*/                                            \
        -1)
#endif /* a_list_pop */
#ifndef a_list_ppop
#define a_list_ppop(_def, _ctx, _x) a_list_pop(_def, *(_ctx), _x)
#endif /* a_list_ppop */

#ifndef a_list_popp
#define a_list_popp(_def, _ctx, _px) (                                   \
    (_ctx).head->next                                                    \
        ? /*head->next != 0*/                                            \
        (--(_ctx).siz,                                                   \
         (_px) = &(_ctx).head->next->data,                               \
         a_mempool_free(a_list1_t(_def), (_ctx).mem, (_ctx).head->next), \
         (_ctx).head->next = (_ctx).head->next->next,                    \
         0)                                                              \
        : /*head->next == 0*/                                            \
        -1)
#endif /* a_list_popp */
#ifndef a_list_ppopp
#define a_list_ppopp(_def, _ctx, _px) a_list_popp(_def, *(_ctx), _px)
#endif /* a_list_ppop */

/* Enddef to prevent recursive inclusion */
#endif /* __A_LIST_H__ */
