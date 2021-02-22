all: obj obj/my_vector.o obj/main.o lab_06

obj:
	mkdir -p obj

obj/my_vector.o: src/my_vector.cpp include/my_vector.h
	g++ -std=c++17 -c src/my_vector.cpp -o obj/my_vector.o -I include

obj/main.o: src/main.cpp
	g++ -std=c++17 -c src/main.cpp -o obj/main.o -I include

lab_06: obj/main.o obj/my_vector.o
	g++ -std=c++17 obj/main.o obj/my_vector.o -o lab_06 -I include

clean: 
	rm -f obj/*.o lab_06 *.txt *.bin
