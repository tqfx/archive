#!/usr/bin/env node
var Module = require("./liba.js")
var pid = new Module.pid(1, -10, 10)
pid.kpid(10, 0.1, 1)
pid.pos(10)
console.log(pid.proc(10, 0))
pid.delete()
