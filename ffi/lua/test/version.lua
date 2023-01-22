#!/usr/bin/env lua
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test:r(getmetatable(a.version))
ctx = a.version:new()
test:r(getmetatable(ctx))
v000 = a.version.new(0, 0, 0)
v100 = a.version.new(1, 0, 0)
v010 = a.version.new(0, 1, 0)
v001 = a.version.new(0, 0, 1)
assert(a.version.eq(v000, v000))
assert(a.version.ne(v000, v010))
assert(a.version.lt(v000, v010))
assert(not a.version.lt(v000, v000))
assert(a.version.gt(v010, v000))
assert(not a.version.gt(v000, v000))
assert(a.version.le(v000, v010))
assert(not a.version.le(v010, v000))
assert(a.version.ge(v010, v000))
assert(not a.version.ge(v000, v010))
assert(a.version.cmp(v000, v100) < 0)
assert(a.version.cmp(v000, v010) < 0)
assert(a.version.cmp(v000, v001) < 0)
assert(a.version.cmp(v100, v000) > 0)
assert(a.version.cmp(v010, v000) > 0)
assert(a.version.cmp(v001, v000) > 0)
assert(a.version.cmp(v000, v000) == 0)
assert(v000 == v000)
assert(v000 ~= v010)
assert(v000 < v010)
assert(not (v000 < v000))
assert(v010 > v000)
assert(not (v000 > v000))
assert(v000 <= v010)
assert(not (v010 <= v000))
assert(v010 >= v010)
assert(not (v000 >= v010))
print("major", a.version.major)
print("minor", a.version.minor)
print("patch", a.version.patch)
print("version", a.VERSION)
