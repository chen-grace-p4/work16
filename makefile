all: work16.o
	gcc -o work16 work16.o
work16.o: work16.c
	gcc -c work16.c
run:
	./work16
clean:
	rm *.o
	rm work16
