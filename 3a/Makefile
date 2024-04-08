all: clean gen_csv exec

clean:
	rm -rf main *.o *.csv

main.o:
	$(CC) -o main.o -c main.c

utils.o:
	$(CC) -o utils.o -c utils.c

table.o:
	$(CC) -o table.o -c table.c

main: main.o utils.o table.o
	$(CC) -o main main.o utils.o table.o

exec: main
	valgrind -s ./main

gen_csv:
	echo "key1;value1;value2;value3;" >> test.csv
	echo "key2;valueAnother;idkValue" >> test.csv
	echo "ahah;aahahahahahha;ahahah;ahaha" >> test.csv
	echo ":);:(;:(((;:|" >> test.csv
	echo "ihaveakeyboard;i;have;a;keyboard" >> test.csv
