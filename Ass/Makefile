EXE = csapp
CFLAGS += -g
src = ./src
CODE = ./src/memory/instruction.c ./src/disk/code.c ./src/memory/dram.c ./src/cpu/mmu.c  ./src/main.c

.PHONY:csapp
csapp:
	$(CC) -I $(src) $(CODE) $(CFLAGS) -o $(EXE)

run:
	./$(EXE)