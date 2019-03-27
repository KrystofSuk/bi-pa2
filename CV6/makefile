run: build
	./a.out

build: 
	g++ ./prog.cpp ./inventory.cpp -Wall -pedantic; 

mem: build
	valgrind ./a.out