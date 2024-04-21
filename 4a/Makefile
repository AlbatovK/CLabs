all: clean exec post

clean:
	rm -rf main *.o *.dot *.png

main.o:
	$(CC) -o main.o -c main.c

main: main.o
	$(CC) -o main main.o

exec: main
	./main

post: exec
	dot -Tpng tree.dot -o tree.png
