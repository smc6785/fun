import socket
import struct
import telnetlib

def interact():
  print("==== INTERACT ====")
  t = telnetlib.Telnet()
  t.sock = s
  t.interact()
  
s = socket.create_connection(("vortex.labs.overthewire.org", 5842))
acc = 0
for i in range(4):
  acc += struct.unpack("I", s.recv(4))[0]

s.send(struct.pack("I", acc))

interact()

# Username: vortex1 Password: Gq#qu3bF3
