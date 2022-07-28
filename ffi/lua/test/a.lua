#!/usr/bin/env lua
local a = require("liba")
print("version", a:version())
print("major", a:version_major())
print("minor", a:version_minor())
print("patch", a:version_patch())
print(a.inv_sqrt(1, 2, 3, 4))
