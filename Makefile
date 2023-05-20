FLAGS= -std=c++17
CC=g++

run: clean max_min_heap.o main.o
	$(CC) $(FLAGS) -v main.o max_min_heap.o -o run_file 
	chmod +x run_file
	./run_file

max_min_heap.o:
	$(CC) $(FLAGS) -g -c max_min_heap.cpp

main.o: max_min_heap.h
	$(CC) $(FLAGS) -g -c main.cpp

clean clear:
	rm *.o || :
