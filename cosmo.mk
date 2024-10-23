
main2.exe: main.exe bytecode.VM
	cat main.exe bytecode.VM > main2.exe
	chmod +x main2.exe

main.exe: main.c VM.c VM.h
	./cosmocc -o main2.exe main.c VM.c

include Makefile
