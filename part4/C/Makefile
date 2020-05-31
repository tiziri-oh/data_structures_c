CC= gcc
CXXFLAGS= -Wall -ansi --pedantic -O3

CPP_O_FILE = b_tree/btree.o b_tree/btree_util.o b_tree/btree_tools.o avl/avl.o analyzer.o main.o
LIB = -lm

all: $(CPP_O_FILE)
	$(CC) $(CXXFLAGS) -o tree_analysis $(CPP_O_FILE) $(LIB)

clean:
	rm -rf *.o
	rm -rf b_tree/*.o
	rm -rf avl/*.o
	rm -rf *~
	rm -rf tree_analysis
