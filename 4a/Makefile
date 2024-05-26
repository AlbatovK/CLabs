all: clean exec post

clean:
	rm -rf main *.o *.dot *.png

main.o:
	$(CC) -o main.o -c main.c

utils.o:
	$(CC) -o utils.o -c utils.c

queue.o:
	$(CC) -o queue.o -c queue.c

tree.o:
	$(CC) -o tree.o -c tree.c

main: main.o utils.o queue.o tree.o
	$(CC) -o main main.o utils.o queue.o tree.o

exec: main
	valgrind -s --leak-check=full ./main

post: exec
	dot -Tpng tree.dot -o tree.png

image:
	catimg -c -w 200 -r 2 tree.png
