TARGET_LIST = list
TARGET_VECTOR = vector

all: clean install list_dev vector_dev list_dyn vector_dyn list_static vec_static

clean:
	rm -rf $(TARGET_VECTOR) $(TARGET_LIST) list_dyn vector_dyn *.o *.so *.a list_static vec_static

install:
	export LD_LIBRARY_PATH=.:LD_LIBRARY_PATH

main.o: main.c
	$(CC) -o main.o -c main.c

queue_list_impl.o: queue_list_impl.c
	$(CC) -o queue_list_impl.o -c queue_list_impl.c -fPIC

queue_vector_impl.o: queue_vector_impl.c
	$(CC) -o queue_vector_impl.o -c queue_vector_impl.c -fPIC


list_dev: main.o queue_list_impl.o
	$(CC) -o $(TARGET_LIST) main.o queue_list_impl.o

vector_dev: main.o queue_vector_impl.o
	$(CC) -o $(TARGET_VECTOR) main.o queue_vector_impl.o
	

libqueue_list.so: queue_list_impl.o
	$(CC) -shared -o libqueue_list.so queue_list_impl.o -lm

libqueue_vec.so: queue_vector_impl.o
	$(CC) -shared -o libqueue_vec.so queue_vector_impl.o -lm


list_dyn: main.o libqueue_list.so
	$(CC) main.o -o list_dyn -L . -lqueue_list -lm

vector_dyn: main.o libqueue_vec.so
	$(CC) main.o -ldl -o vector_dyn -L . -lqueue_vec -lm

run_list_dyn: list_dyn libqueue_list.so
	valgrind ./list_dyn -s

run_vector_dyn: vector_dyn libqueue_vec.so
	valgrind ./vector_dyn -s
	

libqueue_list.a: queue_list_impl.o
	ar -rcs libqueue_list.a queue_list_impl.o

libqueue_vec.a: queue_vector_impl.o
	ar -rcs libqueue_vec.a queue_vector_impl.o
	

list_static: libqueue_list.a
	$(CC) main.c -L . -lqueue_list -o list_static

vec_static: libqueue_vec.a
	$(CC) main.c -L . -lqueue_vec -o vec_static

run_list_static: list_static
	valgrind ./list_static -s

run_vec_static: vec_static
	valgrind ./vec_static -s
