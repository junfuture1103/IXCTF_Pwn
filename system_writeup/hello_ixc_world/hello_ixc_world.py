from pwn import *

context.log_level = 'debug'
p = remote("pwn.isangxcaution.xyz", 10001)


def slog(symbol, addr): return success(symbol + ": " + hex(addr))


p.recvuntil("If you enter 1, you can get flag : ")

payload = str("1")
p.sendline(payload)

p.interactive()
