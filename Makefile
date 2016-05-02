CFLAGS = -g

final_project: main.o vector.o
	gcc main.o vector.o -o bin/final_project
	
main.o: src/main.c
	gcc src/main.c -c

vector.o: src/vector.c
	gcc src/vector.c -c
	
clean:
	rm *.o bin/final_project