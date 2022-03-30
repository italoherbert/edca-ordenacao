FILE = ordenacao
EXEC_EXT = .exe
CC = gcc

all: compila linka

compila:
	$(CC) -c $(FILE).c -o $(FILE).o

linka: compila
	$(CC) $(FILE).o -o $(FILE)$(EXEC_EXT)