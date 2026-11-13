#!/usr/bin/python3
import pyaes

# 16 bytes
key = bytes(" ", "utf-8") + bytes(1)
iv = 0

plaintext = ""

aes = pyaes.AESModeOfOperationCTR(key, pyaes.Counter(iv))
encoded = aes.encrypt(plaintext)

print(f"encoded\n{encoded}")

encoded = ""

aes = pyaes.AESModeOfOperationCTR(key, pyaes.Counter(iv))
# Decrypt the encoded
decrypted = aes.decrypt(encoded)
print(f"Decrypted\n{decrypted.decode()}")
