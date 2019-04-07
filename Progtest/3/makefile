run: build
	./a.out

build: 
	g++ ./test.cpp ./tests.cpp -Wall -pedantic; 

mem: build
	valgrind ./a.out