#!/usr/bin/env lua

package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test:r(getmetatable(a.version))
print("major", a.version.major)
print("minor", a.version.minor)
print("patch", a.version.patch)
print("version", a.version())
