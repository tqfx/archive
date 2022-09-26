#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test:r(getmetatable(a.tf))

local num = {6.59492796e-05, 6.54019884e-05}
local den = {-1.97530991, 0.97530991}

tf = a.tf.new(num, den)
assert(a.tf.proc(tf, 1))
assert(a.tf:proc(tf, 1))
assert(a.tf.zero(tf))
assert(a.tf:zero(tf))
tab = a.tf.into(tf)
tf = a.tf.from(tab)
tab = a.tf:into(tf)
tf = a.tf:from(tab)
test:r(getmetatable(tf))
tf = a:tf(num, den)
assert(tf.proc(tf, 1))
assert(tf.zero(tf))
assert(tf:proc(1))
assert(tf:zero())
