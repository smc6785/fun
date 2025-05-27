# riscv64-unknown-elf-as hello.s -o hello.o
# riscv64-unknown-elf-gcc -o hello hello.o -nostdlib -static

.global _start

_start:
  # Linux syscall write number is 64.
  addi a7, zero, 64
  # STDOUT DF = 1
  addi a0, zero, 1
  la a1, helloworld
  addi a2, zero, 13
  ecall


  # Linux syscall exit number is 93.
  addi a7, zero, 93
  # Argument that goes into exit in a0.
  # Exit will return a0.
  addi a0, zero, 12
  # Invoke syscall.
  ecall

helloworld:
  .ascii "Hello world\n"
