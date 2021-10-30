/*!
 @file a_mean.c
 @brief mean calculation
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_mean.h"

#include <math.h>

#undef A_SQ
#define A_SQ(_x) ((_x) * (_x))

#undef __A_MEAN_INIT
#define __A_MEAN_INIT(_def, _func)                  \
    void _func(_def##_t *_ctx, a_mean_mode_t _mode) \
    {                                               \
        aassert(_ctx);                              \
        aassert(A_MEAN_ALL <= _mode);               \
                                                    \
        _ctx->num = 0;                              \
        _ctx->mode = _mode;                         \
                                                    \
        switch (_ctx->mode)                         \
        {                                           \
        case A_MEAN_GEOMETRIC:                      \
        {                                           \
            _ctx->out = 1;                          \
        }                                           \
        break;                                      \
                                                    \
        case A_MEAN_ARITHMETIC:                     \
        case A_MEAN_HARMONIC:                       \
        case A_MEAN_SQUARE:                         \
        case A_MEAN_ALL:                            \
        default:                                    \
        {                                           \
            _ctx->out = 0;                          \
        }                                           \
        break;                                      \
        }                                           \
    }
__A_MEAN_INIT(a_mean, a_mean_init)
__A_MEAN_INIT(a_meanf, a_meanf_init)
#undef __A_MEAN_INIT

#undef __A_MEAN_PROCESS
#define __A_MEAN_PROCESS(_def, _type, _func)               \
    void _func(_def##_t *_ctx, const _type *_p, size_t _n) \
    {                                                      \
        aassert(_ctx);                                     \
        aassert(!_n || _p);                                \
                                                           \
        const _type *p = _p + _n;                          \
                                                           \
        switch (_ctx->mode)                                \
        {                                                  \
        case A_MEAN_ARITHMETIC:                            \
        {                                                  \
            for (; _p != p; ++_p)                          \
            {                                              \
                _ctx->out += *_p;                          \
            }                                              \
        }                                                  \
        break;                                             \
                                                           \
        case A_MEAN_GEOMETRIC:                             \
        {                                                  \
            for (; _p != p; ++_p)                          \
            {                                              \
                _ctx->out *= *_p;                          \
            }                                              \
        }                                                  \
        break;                                             \
                                                           \
        case A_MEAN_HARMONIC:                              \
        {                                                  \
            for (; _p != p; ++_p)                          \
            {                                              \
                _ctx->out += 1 / *_p;                      \
            }                                              \
        }                                                  \
        break;                                             \
                                                           \
        case A_MEAN_SQUARE:                                \
        {                                                  \
            for (; _p != p; ++_p)                          \
            {                                              \
                _ctx->out += A_SQ(*_p);                    \
            }                                              \
        }                                                  \
        break;                                             \
                                                           \
        case A_MEAN_ALL:                                   \
        default:                                           \
            break;                                         \
        }                                                  \
                                                           \
        _ctx->num += _n;                                   \
    }
__A_MEAN_PROCESS(a_mean, double, a_mean_process)
__A_MEAN_PROCESS(a_meanf, float, a_meanf_process)
#undef __A_MEAN_PROCESS

#undef __A_MEAN_DONE
#define __A_MEAN_DONE(_def, _type, _func, _sqrt, _pow)         \
    _type _func(_def##_t *_ctx)                                \
    {                                                          \
        aassert(_ctx);                                         \
                                                               \
        switch (_ctx->mode)                                    \
        {                                                      \
        case A_MEAN_ARITHMETIC:                                \
        {                                                      \
            _ctx->out /= (_type)_ctx->num;                     \
        }                                                      \
        break;                                                 \
                                                               \
        case A_MEAN_GEOMETRIC:                                 \
        {                                                      \
            _ctx->out = _pow(_ctx->out, 1 / (_type)_ctx->num); \
        }                                                      \
        break;                                                 \
                                                               \
        case A_MEAN_HARMONIC:                                  \
        {                                                      \
            _ctx->out = (_type)_ctx->num / _ctx->out;          \
        }                                                      \
        break;                                                 \
                                                               \
        case A_MEAN_SQUARE:                                    \
        {                                                      \
            _ctx->out /= (_type)_ctx->num;                     \
            _ctx->out = _sqrt(_ctx->out);                      \
        }                                                      \
        break;                                                 \
                                                               \
        case A_MEAN_ALL:                                       \
        default:                                               \
            break;                                             \
        }                                                      \
                                                               \
        return _ctx->out;                                      \
    }
__A_MEAN_DONE(a_mean, double, a_mean_done, sqrt, pow)
__A_MEAN_DONE(a_meanf, float, a_meanf_done, sqrtf, powf)
#undef __A_MEAN_DONE

/* END OF FILE */
