CC= gcc
CXXFLAGS= -Wall -ansi --pedantic -O3

CPP_O_FILE = binary_binomial_heap.o analyzer.o main.o
LIB = -lm

all: $(CPP_O_FILE)
	$(CC) $(CXXFLAGS) -o heap_analysis $(CPP_O_FILE) $(LIB)
	gcc test_heap.c binary_binomial_heap.c -o test_heap
test:
	./heap_analysis
	gnuplot -c plot_script --persist

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf heap_analysis
	rm -rf test_heap