#!/usr/bin/env python3

import os, binascii, hashlib, base58, ecdsa
import random
import socket
import struct
import time
from hexdump import hexdump
'''
import qrcode
img = qrcode.make(publ_addr)
img.save("coin.jpg")
'''

def shex(x):
  return binascii.hexlify(x).decode()

def checksum(x):
  return hashlib.sha256(hashlib.sha256(x).digest()).digest()[:4]

def b58wchecksum(x):
  return base58.b58encode(x+checksum(x))

def ripemd160(x):
  d = hashlib.new('ripemd160')
  d.update(x)
  return d

def get_key_w_seed(seed=1337):
  # generate private key
  random.seed(1337)
  priv_key = bytes([random.randint(0,255) for x in range(32)])
  #print(shex(priv_key))

  # priv_key -> WIF
  WIF = b58wchecksum(b"\x80" + priv_key)
  #print(WIF)

  # get public key
  sk = ecdsa.SigningKey.from_string(priv_key, curve=ecdsa.SECP256k1)
  vk = sk.get_verifying_key()
  publ_key = b"\x04" + vk.to_string()
  #print(shex(publ_key))

  # get public address
  hash160 = ripemd160(hashlib.sha256(publ_key).digest()).digest()
  publ_addr =b58wchecksum(b"\x00" + hash160)
  #print(publ_addr)

  return priv_key,WIF, publ_addr

#magic = 0xd9b4bef9
# bit coin cash magic
MAGIC_CASH = 0xe8f3e1e3

def makeMessage(magic, command, payload):
  return struct.pack('<L12sL4s', MAGIC_CASH, command, len(payload), checksum(payload)) + payload

def getVersionMsg():
  version = 240002
  services = 1
  timestamp = int(time.time())
  addr_me = b"\x00"*26
  addr_you = b"\x00"*26
  nonce = random.getrandbits(64)
  sub_version_num = b"\00" 
  start_height = 0
  payload = struct.pack('<LQQ26s26sQsL', version, services, timestamp, addr_me,
  addr_you, nonce, sub_version_num, start_height)
  return makeMessage(MAGIC_CASH, b'version', payload)

#def getTxMsg():


def sock_read(sock, count):
  ret = b''
  while len(ret) < count:
    ret += sock.recv(count-len(ret))
  return ret

def recvMessgae(sock):
  magic, command, plen, cksum = struct.unpack('<L12sL4s', sock_read(sock,24))
  assert magic == MAGIC_CASH
  payload = sock_read(sock,plen)
  assert checksum(payload) == cksum
  print(command)
  hexdump(payload)
  return command, payload
    
if __name__ == "__main__":
  peers= socket.gethostbyname_ex('seed.bitcoinabc.org')[2]
  peer = random.choice(peers)

  vermsg =  getVersionMsg()
  hexdump(vermsg)

  sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  sock.connect((peer,8333))
  sock.send(vermsg)
  cmd, payload = recvMessgae(sock)
  cmd, payload = recvMessgae(sock)
  #hexdump(sock.recv(1024))


  priv_key,WIF, publ_addr = get_key_w_seed()
  _,_, publ_addr2 = get_key_w_seed(1338)
  print("%s -> %s" %(publ_addr, publ_addr2))


'''
- private key, sk
  a private key is essentially a randomly generated, 32-byte number
- public key, pk
  a pulbic key can be derived from the private key using Elliptic curve cryptohraphy
  Bitcoin uses a specific elliptic curve called secp256k1
- public address
  public key -> 8 step process involving concatenation, has functions(SHA-256 and RIPEMD-160) and Base58Check -> public address

different messages
completely different signatures

sign(Message, sk) = signature
verify(Message, signature, pk) =T/F

256 bit signature

Hash fucntion
SHA256(meesage/file)= hash, or digest
inverse is infeasible

Wallet import format(WIF)
WIF is a standardized method for displaying Bitcoin private keys using Base58Check encoding scheme
WIF format was standardized in order to allow all Bitcoin wallets to import and export private keys

the process of encoding a private key into WIF format is:
- raw private ekys are simply lare numbers, which are represented as bytes
- WIF format adds a prefix byte (0x80 for mainnet and 0xef for testnet)
- a ‘0x01’ byte is added to the end of the private key if its corresponding public key should use compressed SEC format. 
- a four byte double SHA-256 checksum is appended to the byte-encoded private key, in order to prevent typos or tampering.

SEC format, Efficient Crptography
SEC is the standard method for encoding a Bitcoin pblic key
A Bitcoin public key is a point on the elliptic curve, called secp256k1, thus has an x and y coordinate

str = '...'
bytes = b'...'

#!/usr/local/bin.python
will only run if python is installed in /usr/local/bin

#!/usr/bin/env python
/usr/bin/env can interpret your $PATH, which makes scripts mreo portable

this is shebang line
a shebang line defines where the interpreter is located
in this case python3 interpreter is located in /usr/bin/python3
A shebang line could also be a bash, ruby, perl and so on
eg. #!/bin/bash

chmod +x script.py
./script.py

You can use #!/usr/bin/env python3 for portability across different systems 

# Base58
Base58 is an encoding scheme with an alphabet of 58 characters
Base58 excludes zero, uppercase'O', uppercase'I', lowcase'i'
26*2 +10 -4 =58

A variant of Base58 called Base58Check is used to represent legacy Bitcoin addresses and private keys in WIF format.
Wallet Import Format (WIF) is a standardized method for displaying Bitcoin private keys using the Base58Check encoding scheme.

Base58Check is identical to Base58, with the addition of a 4-bute checksum and a version prefix
the version prefix indicates what data is represented:
  Pay-to-Public-Key-Hash (P2PKH) addresses have the prefix ‘1’, 
  P2SH addresses have a prefix of ‘3’
  private keys in WIF format carry a ‘5’ prefix.

# hashlib
this module implements a common interface to many different sucure hash and message digest algorithms
included are the FIPS secure hash algorithms SHA1, SHA224, SHA256, SHA384, and SHA512 (defined in FIPS 180-2) as well as RSA’s MD5 algorithm (defined in internet RFC 1321).

# binascii
convert between binary and ASCII

nslookup
from name server lookup
is a network admninistration command-line tool for querying the Domian Name System
to obtain the mapong between domain name and IP address or other DNS records

tuple, immutable
are used to store multiple items in a single variable
tuple = ("orange","apple","banana")

list, mutable
list can store more than one data type
list = ["mango", "strawberry", "orange","apple", "banana"]

array, mutable
array can store ony similar data type
import array as arr
a = arr.array('i', [1, 2, 3])

256-bit private key, 32 bytes
512-bit public key, the elliptic curve DSA algorithm 
  - the bitcoin protocol adds a prefix of 04 to the public key
  - and then it gets hashed down to 160 bits using SHA-256 and RIPEMD hash algorithms
  - and then the key is encoded in ASCII using Base58Check encoding

keys are represented externally in ASCII using Base58Check

assert keyword
is used when debugging code
the assert keyword lets you test if a condition in your code returns True
if not, the program will raise an AssertionError
x = "hello"

#if condition returns True, then nothing happens:
assert x == "hello"

#if condition returns False, AssertionError is raised:
assert x == "goodbye"

'''



