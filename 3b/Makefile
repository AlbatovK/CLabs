all: clean exec

clean:
	rm -rf main *.o

main.o:
	$(CC) -o main.o -c main.c

utils.o:
	$(CC) -o utils.o -c utils.c

table.o:
	$(CC) -o table.o -c table.c

main: main.o utils.o table.o
	$(CC) -o main main.o utils.o table.o

exec: main
	valgrind ./main
