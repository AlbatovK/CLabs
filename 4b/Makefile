all: clean exec

clean:
	rm -rf main *.o *.dot *.png

main.o:
	$(CC) -o main.o -c main.c

utils.o:
	$(CC) -o utils.o -c utils.c

SplayTree.o:
	$(CC) -o SplayTree.o -c SplayTree.c

main: main.o utils.o SplayTree.o
	$(CC) -o main main.o utils.o SplayTree.o

exec: main
	valgrind -s --leak-check=full ./main

image:
	dot -Tpng $(DOT) -o $(PNG)
	catimg $(PNG)
