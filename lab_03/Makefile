all: prepare obj/mergesort.o obj/main.o link

prepare:
	mkdir -p obj

obj/mergesort.o: src/mergesort.c include/mergesort.h
	gcc -c src/mergesort.c -o obj/mergesort.o -I include

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -I include

link: obj/main.o obj/mergesort.o 
	gcc obj/main.o obj/mergesort.o -o lab_03 -I include

clean: 
	rm -f obj/*.o lab_03
