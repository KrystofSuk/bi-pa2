run: build
	./a.out

build: 
	g++ ./test.cpp  -Wall -pedantic; 

mem: build
	valgrind ./a.out