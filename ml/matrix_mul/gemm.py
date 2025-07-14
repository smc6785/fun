#!/usr/bin/env python3.10

# gemm, general matrix multiplications
# dgemm, double-precision general matrix multiply(64 bit)
# sgemm, single-precision general matrix multiply(32 bit)

# A * B = C
# A: m x n
# B: n x p
# C: m x p
# Each cell in C is the output of dot product of two vectors.

import os
os.environ['OMP_NUM_THREAD'] = '1'
import numpy as np
import time

N = 1024
if __name__ == "__main__":
  A = np.random.randn(N,N).astype(np.float32)
  B = np.random.randn(N,N).astype(np.float32)
  
  # N^2 output cells with 2N compute each (add and multiply)
  # FLOPS, floating point operation per second
  flop = N*N*2*N
  # si prefixes
  # p, peta
  # t, tera
  # g, giga
  # m, mega
  # k, kilo
  # m, milli
  # u, micro
  # n, nano

  print(f"{flop / 1e9:.2f} GFLOP")
  st = time.monotonic()
  C = A @ B
  et = time.monotonic()
  s = et-st

  print(f"{flop/s * 1e-9} GFLOPS")

  with open("./matmul", "wb") as f:
    f.write(A.data)
    f.write(B.data)
    f.write(C.data)

