CC = gcc
CFLAGS = -Wall -pedantic -ansi
BIN = freq.exe
OBJ = graph.o matrix.o stack.o transmitter.o main.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@

# vycisti vsechny .o soubory a .exe
clean: 
	rm -f $(OBJ) $(BIN)

