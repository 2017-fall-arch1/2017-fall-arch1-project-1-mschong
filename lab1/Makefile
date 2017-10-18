all: bst

CFLAGS=-g

# Symbols helpful for understanding the productions
#   $@ is the production's target
#   $^ are the production's prerequisites

bst: bst.o	
	cc -o $@ $^

bst.o: bst.c bst.h
	cc -c $(CFLAGS) bst.c

clean:
	rm -f *.o bst

demo: bst
	 ./bst

