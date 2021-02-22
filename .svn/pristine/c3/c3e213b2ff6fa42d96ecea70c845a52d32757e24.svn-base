all: obj obj/clist.o obj/point_list.o obj/main.o lab_05

obj:
	mkdir -p obj

obj/clist.o: src/clist.c include/clist.h
	gcc -c src/clist.c -o obj/clist.o -I include

obj/point_list.o: src/point_list.c include/point_list.h
	gcc -c src/point_list.c -o obj/point_list.o -I include

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -I include

lab_05: obj/main.o obj/point_list.o obj/clist.o 
	gcc obj/main.o obj/point_list.o obj/clist.o -o lab_05 -I include

clean: 
	rm -f obj/*.o lab_05 *.txt *.bin
