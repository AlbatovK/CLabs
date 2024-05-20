all: build exec show

build: main.c
	gcc -o main main.c utils.c queue.c

exec: main
	./main

show: graph.dot
	dot graph.dot -Tpng -o graph.png
	
