#!/usr/bin/env node
var Module = require("./liba.js")
var source = [0, 0, 0, 0, 0];
var target = [1, 1, 1, 1, 1];

var ctx = new Module.polytrack3(source, target)
console.log(ctx.all(0.5))
console.log(ctx.pos(0.5))
console.log(ctx.vec(0.5))
console.log(ctx.acc(0.5))
ctx.delete()

var ctx = new Module.polytrack5(source, target)
console.log(ctx.all(0.5))
console.log(ctx.pos(0.5))
console.log(ctx.vec(0.5))
console.log(ctx.acc(0.5))
ctx.delete()

var ctx = new Module.polytrack7(source, target)
console.log(ctx.all(0.5))
console.log(ctx.pos(0.5))
console.log(ctx.vec(0.5))
console.log(ctx.acc(0.5))
console.log(ctx.jer(0.5))
ctx.delete()
