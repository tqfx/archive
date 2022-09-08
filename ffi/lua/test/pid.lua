#!/usr/bin/env lua

function print_r(t)
  local print_r_cache = {}
  local function sub_print_r(t, indent)
    if (print_r_cache[tostring(t)]) then
      print(indent .. "*" .. tostring(t))
    else
      print_r_cache[tostring(t)] = true
      if (type(t) == "table") then
        for pos, val in pairs(t) do
          if (type(val) == "table") then
            print(indent .. "[" .. pos .. "] => " .. tostring(t) .. " {")
            sub_print_r(val, indent .. string.rep(" ", string.len(pos) + 8))
            print(indent .. string.rep(" ", string.len(pos) + 6) .. "}")
          elseif (type(val) == "string") then
            print(indent .. "[" .. pos .. '] => "' .. val .. '"')
          else
            print(indent .. "[" .. pos .. "] => " .. tostring(val))
          end
        end
      else
        print(indent .. tostring(t))
      end
    end
  end
  if (type(t) == "table") then
    print(tostring(t) .. " {")
    sub_print_r(t, "  ")
    print("}")
  else
    sub_print_r(t, "  ")
  end
  print()
end

local a = require("liba")
print_r(getmetatable(a.pid))

pid = a.pid.init(1, 10, 0.1, 1, -10, 10, 10)
a.pid.kpid(pid, 3, 2, 1)
a.pid:kpid(pid, 3, 2, 1)
a.pid.proc(pid, 1, 0)
a.pid:proc(pid, 1, 0)
a.pid.time(pid, 0.1)
a.pid:time(pid, 0.1)
a.pid.done(pid)
a.pid:done(pid)
a.pid.pos(pid, 10)
a.pid:pos(pid, 10)
a.pid.inc(pid)
a.pid:inc(pid)
a.pid.off(pid)
a.pid:off(pid)
tab = a.pid.into(pid)
pid = a.pid.from(tab)
tab = a.pid:into(pid)
pid = a.pid:from(tab)

pid = a.pid(1, 10, 0.1, 1, -10, 10, 10)
pid:kpid(3, 2, 1):time(0.1):off(1, 2):inc():pos(10)
pid:from(tab)
pid:into()
pid(1, 0)
