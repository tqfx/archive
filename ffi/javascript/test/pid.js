#!/usr/bin/env node
var Module = require("./liba.js")
pid = Module._pid_new(1, -10, 10)
Module._pid_kpid(pid, 10, 0.1, 1)
Module._pid_pos(pid, 10)
console.log(Module._pid(pid, 10, 0))
Module._pid_die(pid)
