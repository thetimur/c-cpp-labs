all: prepare obj/str.o obj/test_str.o link

prepare:
	mkdir -p obj

obj/str.o: src/str.c include/str.h
	gcc -c src/str.c -o obj/str.o -I include

obj/test_str.o: src/test_str.c include/test_str.h
	gcc -c src/test_str.c -o obj/test_str.o -I include

obj/test.o: src/test.c
	gcc -c src/test.c -o obj/test.o -I include

link: obj/test.o obj/str.o obj/test_str.o 
	gcc obj/test.o obj/str.o obj/test_str.o -o lab_02 -I include

run_tests:
	./lab_02

clean: 
	rm obj/*.o lab_02