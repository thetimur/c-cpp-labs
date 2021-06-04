all: obj obj/huffman.o obj/main.o huffman obj/autotest.o obj/huffman_test.o test_huffman

obj:
	mkdir -p obj

obj/huffman.o: src/huffman.cpp src/huffman.h
	g++ -std=c++17 -c src/huffman.cpp -o obj/huffman.o -I include

obj/main.o: src/main.cpp
	g++ -std=c++17 -c src/main.cpp -o obj/main.o -I include

obj/huffman_test.o: test/huffman_test.cpp
	g++ -std=c++17 -c test/huffman_test.cpp -o obj/huffman_test.o -I include -I include -I src

obj/autotest.o: test/autotest.cpp test/autotest.h
	g++ -std=c++17 -c test/autotest.cpp -o obj/autotest.o -I include

huffman: obj/main.o obj/huffman.o
	g++ -std=c++17 obj/main.o obj/huffman.o -o huffman -I include -I src

test_huffman: obj/huffman.o obj/autotest.o obj/huffman_test.o
	g++ -std=c++17 obj/huffman.o obj/autotest.o obj/huffman_test.o -o test_huffman -I include

clean: 
	rm -f obj/*.o huffman test_huffman
