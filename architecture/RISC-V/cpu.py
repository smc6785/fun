#!/usr/bin/env python3
# The above is a shebang for python.
# It makes the system to find pyton3 to make it more portable.
import struct
import glob
from elftools.elf.elffile import ELFFile

regfile = [0]*33
PC = 32

# riscv64-elf-objdump tests/hello -D
# 4k at 0x10000
memory = b'\x00'*0x1000

def ws(dat, addr):
  global memory
  print(hex(addr), len(dat))
  addr -= 0x10000
  assert addr >= 0 and addr < len(memory)
  memory = memory[:addr] + dat + memory[addr+len(dat):]

def r32(addr):
  addr -= 0x10000
  assert addr >= 0 and addr < len(memory)
  return struct.unpack("I", memory[addr:addr+4])[0]

def dump():
  pp =[]
  for i in range(32):
    if i != 0 and i % 8 ==0:
      pp += "\n"
    pp += " %3s: %08x" %("x%d" % i, regfile[i])
  pp += "\n PC: %08x" % regfile[PC]
  print(''.join(pp))

def step():
  # Instruction Fetch
  ins = r32(regfile[PC])
  # Instruction Decode
  print(hex(ins))
  dump()
  # Execute
  # Access
  # Write-Back
  return False
  
# xdd hello
# hexdump -C hello

# Debug:
#   1. exit(0), to terminate a script with exit status code 0 (successuly)
#   2. python3 -i ./cpu.py
#      -i starts puthon interpreter in interactive mode after executing 
if __name__  == "__main__":
  for x in glob.glob("tests/*"):
    if x.endswith('.o'):
      continue
    if x.endswith('.s'):
      continue
    with open(x, 'rb') as f:
      # with keyword makes sure handle will be closed after this block.
      e = ELFFile(f)
      # In ELf file, sections are for linking.
      # Segments are for execution, loadable data, loadable code.
      # for s in e.iter_sections():
        # print(s.name)
      for s in e.iter_segments():
        # print(dir(s))
        # print(s.header)
        ws(s.data(), s.header.p_paddr)
      regfile[PC] = 0x10078
      while step():
        pass
      #text = e.get_section_by_name(".text").data()
      # print(x,e,text.data())
      # print(dir(text))
      # dir(), is a python build-in functions that returns a list of vaild
      # attributes and methods of an object
      # exit(0)
