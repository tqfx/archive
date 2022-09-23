#!/usr/bin/env node
var Module = require("./liba.js")
var NB = -3
var NM = -2
var NS = -1
var ZO = 0
var PS = +1
var PM = +2
var PB = +3
var mkp = [
    [NB, NB, NM, NM, NS, ZO, ZO],
    [NB, NB, NM, NS, NS, ZO, PS],
    [NM, NM, NM, NS, ZO, PS, PS],
    [NM, NM, NS, ZO, PS, PM, PM],
    [NS, NS, ZO, PS, PS, PM, PM],
    [NS, ZO, PS, PM, PM, PM, PB],
    [ZO, ZO, PM, PM, PM, PB, PB],
]
var mki = [
    [PB, PB, PM, PM, PS, ZO, ZO],
    [PB, PB, PM, PS, PS, ZO, ZO],
    [PB, PM, PS, PS, ZO, NS, NS],
    [PM, PM, PS, ZO, NS, NM, NM],
    [PM, PS, ZO, NS, NS, NM, NB],
    [ZO, ZO, NS, NS, NM, NB, NB],
    [ZO, ZO, NS, NM, NM, NB, NB],
]
var mkd = [
    [NS, PS, PB, PB, PB, PM, NS],
    [NS, PS, PB, PM, PM, PS, ZO],
    [ZO, PS, PM, PM, PS, PS, ZO],
    [ZO, PS, PS, PS, PS, PS, ZO],
    [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
    [NB, NS, NS, NS, NS, NS, NB],
    [NB, NM, NM, NM, NS, NS, NB],
]
var mma = [
    [Module.MF_TRI, -3, -3, -2],
    [Module.MF_TRI, -3, -2, -1],
    [Module.MF_TRI, -2, -1, +0],
    [Module.MF_TRI, -1, +0, +1],
    [Module.MF_TRI, +0, +1, +2],
    [Module.MF_TRI, +1, +2, +3],
    [Module.MF_TRI, +2, +3, +3],
    [Module.MF_NUL, +0, +0, +0],
]
var fpid = new Module.fpid(2, 1, mma, mkp, mki, mkd, -3, 3, -10, 10)
fpid.kpid(10, 0.1, 1)
fpid.pos(10)
console.log(fpid.proc(10, 0))
fpid.delete()
