CFLAGS = -g

cs3050_hw3: main.o vector.o
	gcc main.o vector.o -o bin/cs3050_hw3
	
main.o: src/main.c
	gcc src/main.c -c

vector.o: src/vector.c
	gcc src/vector.c -c
	
clean:
	rm *.o bin/cs3050_hw3