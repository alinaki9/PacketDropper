cmd_/work/packet_drop.ko := ld -r -m elf_x86_64 --build-id=sha1  -T scripts/module.lds -o /work/packet_drop.ko /work/packet_drop.o /work/packet_drop.mod.o;  true
