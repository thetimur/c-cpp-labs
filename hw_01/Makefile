all: obj obj/bmp.o obj/main.o hw_01

obj:
	mkdir -p obj

obj/bmp.o: src/bmp.c include/bmp.h
	gcc -c src/bmp.c -o obj/bmp.o -I include

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -I include

hw_01: obj/main.o obj/bmp.o 
	gcc obj/main.o obj/bmp.o -o hw_01 -I include

clean: 
	rm -f obj/*.o hw_01 *.bmp
