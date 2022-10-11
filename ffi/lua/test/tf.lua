#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test:r(getmetatable(a.tf))

local num = {6.59492796e-05, 6.54019884e-05}
local den = {-1.97530991, 0.97530991}

ctx = a.tf.new(num, den)
assert(a.tf.proc(ctx, 1))
assert(a.tf:proc(ctx, 1))
assert(a.tf.zero(ctx))
assert(a.tf:zero(ctx))
tab = a.tf.into(ctx)
ctx = a.tf.from(tab)
tab = a.tf:into(ctx)
ctx = a.tf:from(tab)
test:r(getmetatable(ctx))
ctx = a:tf(num, den)
assert(ctx.proc(ctx, 1))
assert(ctx.zero(ctx))
assert(ctx:proc(1))
assert(ctx:zero())
