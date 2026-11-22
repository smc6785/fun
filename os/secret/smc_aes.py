#!/usr/bin/python3
import pyaes

# 16 bytes
key = bytes(" ", "utf-8") + bytes(15)
iv = 0

plaintext = ""

aes = pyaes.AESModeOfOperationCTR(key, pyaes.Counter(iv))
encoded = aes.encrypt(plaintext)

print(f"encoded\n{encoded}")

encoded = ""

aes = pyaes.AESModeOfOperationCTR(key, pyaes.Counter(iv))
# Decrypt the encoded
decrypted = aes.decrypt(encoded)
print("Decrypted\n")
print("-----BEGIN OPENSSH PRIVATE KEY-----")
print(f"{decrypted.decode()}")
print("-----END OPENSSH PRIVATE KEY-----")
