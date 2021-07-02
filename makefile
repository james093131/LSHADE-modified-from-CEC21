all:
	g++ -Wall -O3 -o LSHADE_17 cec17_test_func.cpp   search_algorithm.cpp    lshade.cpp main.cpp

clean:
	rm -f main *.o
