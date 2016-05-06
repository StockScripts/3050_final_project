CFLAGS = -g

final_project: main.o
	gcc main.o -o bin/final_project
	
main.o: src/main.c
	gcc src/main.c -c
	
clean:
	rm *.o bin/final_project
