#include "lib.h"
#include "a/pid.h"

EM_PORT_API(a_pid_s *)
pid_new(a_real_t ts, a_real_t min, a_real_t max)
{
    a_pid_s *ctx = (a_pid_s *)malloc(sizeof(a_pid_s));
    if (ctx)
    {
        a_pid_init(ctx, ts, min, max);
    }
    return ctx;
}

EM_PORT_API(a_pid_s *)
pid_die(a_pid_s *ctx)
{
    if (ctx)
    {
        free(ctx);
    }
    return 0;
}

EM_PORT_API(a_pid_s *)
pid_off(a_pid_s *ctx)
{
    return a_pid_off(ctx);
}

EM_PORT_API(a_pid_s *)
pid_inc(a_pid_s *ctx)
{
    return a_pid_inc(ctx);
}

EM_PORT_API(a_pid_s *)
pid_pos(a_pid_s *ctx, a_real_t max)
{
    return a_pid_pos(ctx, max);
}

EM_PORT_API(a_pid_s *)
pid_time(a_pid_s *ctx, a_real_t ts)
{
    return a_pid_time(ctx, ts);
}

EM_PORT_API(a_pid_s *)
pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
{
    return a_pid_kpid(ctx, kp, ki, kd);
}

EM_PORT_API(a_pid_s *)
pid_init(a_pid_s *ctx, a_real_t ts, a_real_t min, a_real_t max)
{
    return a_pid_init(ctx, ts, min, max);
}

EM_PORT_API(a_real_t)
pid(a_pid_s *ctx, a_real_t set, a_real_t ref)
{
    return a_pid_proc(ctx, set, ref);
}

EM_PORT_API(a_pid_s *)
pid_done(a_pid_s *ctx)
{
    return a_pid_done(ctx);
}
