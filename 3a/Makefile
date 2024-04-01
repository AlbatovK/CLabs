all: clean gen_csv iter exec

clean:
	rm -rf main iter *.o *.csv

main.o:
	$(CC) -o main.o -c main.c

utils.o:
	$(CC) -o utils.o -c utils.c

table.o:
	$(CC) -o table.o -c table.c

iter.o:
	$(CC) -o iter.o -c iter.c

main: main.o utils.o table.o
	$(CC) -o main main.o utils.o table.o

iter:
	$(CC) -o iter main.c table_iter.c utils.c iter.c

exec: main
	valgrind ./main

gen_csv:
	echo "key1;value1;value2;value3;" >> test.csv
	echo "key2;valueAnother;idkValue" >> test.csv
	echo "ahah;aahahahahahha;ahahah;ahaha" >> test.csv
	echo ":);:(;:(((;:|" >> test.csv
	echo "ihaveakeyboard;i;have;a;keyboard" >> test.csv
	
