all: obj obj/clist.o obj/main.o lab_04

obj:
	mkdir -p obj

obj/clist.o: src/clist.c include/clist.h
	gcc -c src/clist.c -o obj/clist.o -I include

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -I include

lab_04: obj/main.o obj/clist.o 
	gcc obj/main.o obj/clist.o -o lab_04 -I include

clean: 
	rm -f obj/*.o lab_04
