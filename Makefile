CFLAGS = -g

cs3050_hw1: main.o graph.o
	gcc main.o graph.o -o bin/cs3050_hw3
	
main.o: src/main.c
	gcc src/main.c -c

graph.o: src/graph.c
	gcc src/graph.c -c
	
clean:
	rm *.o bin/cs3050_hw3