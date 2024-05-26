all: clean exec

clean:
	rm -rf main *.o *.dot *.png

main.o:
	$(CC) -o main.o -c main.c

utils.o:
	$(CC) -o utils.o -c utils.c

queue.o:
	$(CC) -o queue.o -c queue.c

main: main.o utils.o queue.o
	$(CC) -o main main.o utils.o queue.o

exec: main
	valgrind -s --leak-check=full ./main

show:
	dot -Tpng $(DOT) -o $(PNG)
	catimg $(PNG)
