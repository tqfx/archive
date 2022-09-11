#!/usr/bin/env node
var Module = require("./liba.js")
console.log(Module.ccall("version", "string"))
console.log(Module._version_major())
console.log(Module._version_minor())
console.log(Module._version_patch())
