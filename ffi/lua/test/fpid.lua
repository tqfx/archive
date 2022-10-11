#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
local NB = -3;
local NM = -2;
local NS = -1;
local ZO = 0;
local PS = 1;
local PM = 2;
local PB = 3;
local mmp = {
    { a.mf.TRI, NB, NB, NM },
    { a.mf.TRI, NB, NM, NS },
    { a.mf.TRI, NM, NS, ZO },
    { a.mf.TRI, NS, ZO, PS },
    { a.mf.TRI, ZO, PS, PM },
    { a.mf.TRI, PS, PM, PB },
    { a.mf.TRI, PM, PB, PB },
    { a.mf.NUL },
}
local mkp = {
    { NB, NB, NM, NM, NS, ZO, ZO },
    { NB, NB, NM, NS, NS, ZO, PS },
    { NM, NM, NM, NS, ZO, PS, PS },
    { NM, NM, NS, ZO, PS, PM, PM },
    { NS, NS, ZO, PS, PS, PM, PM },
    { NS, ZO, PS, PM, PM, PM, PB },
    { ZO, ZO, PM, PM, PM, PB, PB },
}
local mki = {
    { PB, PB, PM, PM, PS, ZO, ZO },
    { PB, PB, PM, PS, PS, ZO, ZO },
    { PB, PM, PS, PS, ZO, NS, NS },
    { PM, PM, PS, ZO, NS, NM, NM },
    { PM, PS, ZO, NS, NS, NM, NB },
    { ZO, ZO, NS, NS, NM, NB, NB },
    { ZO, ZO, NS, NM, NM, NB, NB },
}
local mkd = {
    { NS, PS, PB, PB, PB, PM, NS },
    { NS, PS, PB, PM, PM, PS, ZO },
    { ZO, PS, PM, PM, PS, PS, ZO },
    { ZO, PS, PS, PS, PS, PS, ZO },
    { ZO, ZO, ZO, ZO, ZO, ZO, ZO },
    { NB, NS, NS, NS, NS, NS, NB },
    { NB, NM, NM, NM, NS, NS, NB },
}
test:r(getmetatable(a.fpid))
ctx = a.fpid.new(2, 1, mmp, mkp, mki, mkd, -3, 3, -10, 10)
assert(a.fpid.base(ctx, mmp, mkp, mki ,mkd))
assert(a.fpid.kpid(ctx, 3, 2, 1))
assert(a.fpid:kpid(ctx, 3, 2, 1))
assert(a.fpid.proc(ctx, 1, 0))
assert(a.fpid:proc(ctx, 1, 0))
assert(a.fpid.time(ctx, 0.1))
assert(a.fpid:time(ctx, 0.1))
assert(a.fpid.zero(ctx))
assert(a.fpid:zero(ctx))
assert(a.fpid.pos(ctx, 10))
assert(a.fpid:pos(ctx, 10))
assert(a.fpid.inc(ctx))
assert(a.fpid:inc(ctx))
assert(a.fpid.off(ctx))
assert(a.fpid:off(ctx))
tab = a.fpid.into(ctx)
ctx = a.fpid.from(ctx, tab)
tab = a.fpid:into(ctx)
ctx = a.fpid:from(ctx, tab)
test:r(getmetatable(ctx))
ctx = a:fpid(2, 1, mmp, mkp, mki, mkd, -3, 3, -10, 10)
ctx:kpid(3, 2, 1):time(0.1):off():inc():pos(10):buff(2)
assert(ctx:base(mmp, mkp, mki ,mkd))
assert(ctx:from(tab))
assert(ctx:into())
assert(ctx(1, 0))
