CFLAGS := -g -std=c99 -Wall -Wextra -Wpedantic

main2.elf: main.elf bytecode.VM
	cat main.elf bytecode.VM > main2.elf
	chmod +x main2.elf

main.elf: main.c VM.c VM.h
	gcc -o main.elf main.c VM.c $(CFLAGS)

###########################################################

bytecode.VM:
	echo -n > bytecode.VM
	printf "0: %.2x" 91 | xxd -r -g0 >> bytecode.VM # 1 byte
	printf "bytecode" >> bytecode.VM # 8 * 1 byte
	printf "0: %.8x" 1 \
	| sed -E 's/0: (..)(..)(..)(..)/0: \4\3\2\1/' \
	| xxd -r -g0 >> bytecode.VM # 1 * 4 bytes (little endian)

###########################################################

.DELETE_ON_ERROR:
