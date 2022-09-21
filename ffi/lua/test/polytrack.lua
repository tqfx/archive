#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")

print("polytrack3")
test:r(getmetatable(a.polytrack3))
ctx = a.polytrack3.new({0, 0, 0}, {1, 1, 1})
assert(a.polytrack3.all(ctx, 0.5))
assert(a.polytrack3:all(ctx, 0.5))
assert(a.polytrack3.pos(ctx, 0.5))
assert(a.polytrack3:pos(ctx, 0.5))
assert(a.polytrack3.vec(ctx, 0.5))
assert(a.polytrack3:vec(ctx, 0.5))
assert(a.polytrack3.acc(ctx, 0.5))
assert(a.polytrack3:acc(ctx, 0.5))
tab = a.polytrack3.into(ctx)
ctx = a.polytrack3.from(tab)
tab = a.polytrack3:into(ctx)
ctx = a.polytrack3:from(tab)
ctx = a:polytrack3({0, 0, 0}, {1, 1, 1})
test:r(getmetatable(ctx))
assert(ctx.pos(ctx, 0.5))
assert(ctx.vec(ctx, 0.5))
assert(ctx.acc(ctx, 0.5))
assert(ctx.all(ctx, 0.5))
assert(ctx:pos(0.5))
assert(ctx:vec(0.5))
assert(ctx:acc(0.5))
assert(ctx(0.5))

print("polytrack5")
test:r(getmetatable(a.polytrack5))
ctx = a.polytrack5.new({0, 0, 0, 0}, {1, 1, 1, 1})
assert(a.polytrack5.all(ctx, 0.5))
assert(a.polytrack5:all(ctx, 0.5))
assert(a.polytrack5.pos(ctx, 0.5))
assert(a.polytrack5:pos(ctx, 0.5))
assert(a.polytrack5.vec(ctx, 0.5))
assert(a.polytrack5:vec(ctx, 0.5))
assert(a.polytrack5.acc(ctx, 0.5))
assert(a.polytrack5:acc(ctx, 0.5))
tab = a.polytrack5.into(ctx)
ctx = a.polytrack5.from(tab)
tab = a.polytrack5:into(ctx)
ctx = a.polytrack5:from(tab)
ctx = a:polytrack5({0, 0, 0, 0}, {1, 1, 1, 1})
test:r(getmetatable(ctx))
assert(ctx.pos(ctx, 0.5))
assert(ctx.vec(ctx, 0.5))
assert(ctx.acc(ctx, 0.5))
assert(ctx.all(ctx, 0.5))
assert(ctx:pos(0.5))
assert(ctx:vec(0.5))
assert(ctx:acc(0.5))
assert(ctx(0.5))

print("polytrack7")
test:r(getmetatable(a.polytrack7))
ctx = a.polytrack7.new({0, 0, 0, 0, 0}, {1, 1, 1, 1, 1})
assert(a.polytrack7.all(ctx, 0.5))
assert(a.polytrack7:all(ctx, 0.5))
assert(a.polytrack7.pos(ctx, 0.5))
assert(a.polytrack7:pos(ctx, 0.5))
assert(a.polytrack7.vec(ctx, 0.5))
assert(a.polytrack7:vec(ctx, 0.5))
assert(a.polytrack7.acc(ctx, 0.5))
assert(a.polytrack7:acc(ctx, 0.5))
assert(a.polytrack7.jer(ctx, 0.5))
assert(a.polytrack7:jer(ctx, 0.5))
tab = a.polytrack7.into(ctx)
ctx = a.polytrack7.from(tab)
tab = a.polytrack7:into(ctx)
ctx = a.polytrack7:from(tab)
ctx = a:polytrack7({0, 0, 0, 0, 0}, {1, 1, 1, 1, 1})
test:r(getmetatable(ctx))
assert(ctx.pos(ctx, 0.5))
assert(ctx.vec(ctx, 0.5))
assert(ctx.acc(ctx, 0.5))
assert(ctx.jer(ctx, 0.5))
assert(ctx.all(ctx, 0.5))
assert(ctx:pos(0.5))
assert(ctx:vec(0.5))
assert(ctx:acc(0.5))
assert(ctx:jer(0.5))
assert(ctx(0.5))
