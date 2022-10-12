#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
print(a:sqrt_inv(1, 2, 4))
test:r(a)
test:p(a:hashs("gen", "q0", "v0", "a0", "j0"))
test:p(a:hashs("t1", "q1", "v1", "a1", "j1"))
