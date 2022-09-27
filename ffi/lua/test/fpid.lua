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
local mkp = {
    { NB, NB, NM, NM, NS, ZO, ZO },
    { NB, NB, NM, NS, NS, ZO, PS },
    { NM, NM, NM, NS, ZO, PS, PS },
    { NM, NM, NS, ZO, PS, PM, PM },
    { NS, NS, ZO, PS, PS, PM, PM },
    { NS, ZO, PS, PM, PM, PM, PB },
    { ZO, ZO, PM, PM, PM, PB, PB },
};
local mki = {
    { PB, PB, PM, PM, PS, ZO, ZO },
    { PB, PB, PM, PS, PS, ZO, ZO },
    { PB, PM, PS, PS, ZO, NS, NS },
    { PM, PM, PS, ZO, NS, NM, NM },
    { PM, PS, ZO, NS, NS, NM, NB },
    { ZO, ZO, NS, NS, NM, NB, NB },
    { ZO, ZO, NS, NM, NM, NB, NB },
};
local mkd = {
    { NS, PS, PB, PB, PB, PM, NS },
    { NS, PS, PB, PM, PM, PS, ZO },
    { ZO, PS, PM, PM, PS, PS, ZO },
    { ZO, PS, PS, PS, PS, PS, ZO },
    { ZO, ZO, ZO, ZO, ZO, ZO, ZO },
    { NB, NS, NS, NS, NS, NS, NB },
    { NB, NM, NM, NM, NS, NS, NB },
};
local mma = {
    { a.mf.TRI, -3, -3, -2 },
    { a.mf.TRI, -3, -2, -1 },
    { a.mf.TRI, -2, -1, 0 },
    { a.mf.TRI, -1, 0, 1 },
    { a.mf.TRI, 0, 1, 2 },
    { a.mf.TRI, 1, 2, 3 },
    { a.mf.TRI, 2, 3, 3 },
    { a.mf.NUL },
};
test:r(getmetatable(a.fpid))
fpid = a.fpid.new(2, 1, mma, mkp, mki, mkd, -3, 3, -10, 10)
assert(a.fpid.base(fpid, mma, mkp, mki ,mkd))
assert(a.fpid.kpid(fpid, 3, 2, 1))
assert(a.fpid:kpid(fpid, 3, 2, 1))
assert(a.fpid.proc(fpid, 1, 0))
assert(a.fpid:proc(fpid, 1, 0))
assert(a.fpid.time(fpid, 0.1))
assert(a.fpid:time(fpid, 0.1))
assert(a.fpid.zero(fpid))
assert(a.fpid:zero(fpid))
assert(a.fpid.pos(fpid, 10))
assert(a.fpid:pos(fpid, 10))
assert(a.fpid.inc(fpid))
assert(a.fpid:inc(fpid))
assert(a.fpid.off(fpid))
assert(a.fpid:off(fpid))
tab = a.fpid.into(fpid)
fpid = a.fpid.from(tab)
tab = a.fpid:into(fpid)
fpid = a.fpid:from(tab)
test:r(getmetatable(fpid))
fpid = a:fpid(2, 1, mma, mkp, mki, mkd, -3, 3, -10, 10)
fpid:kpid(3, 2, 1):time(0.1):off():inc():pos(10):buff(2)
assert(fpid:base(mma, mkp, mki ,mkd))
assert(fpid:from(tab))
assert(fpid:into())
assert(fpid(1, 0))
