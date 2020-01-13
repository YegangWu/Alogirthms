CC=g++
CPPFLAGS=-L../tree_lib/
LIBS=-ltree

app: app.o line_tree.o line_segment.o
	$(CC) $(CPPFLAGS) $(LIBS) *.o -o app

app.o: app.cpp
	$(CC) -I../tree_lib/ -c app.cpp

line_tree.o: line_tree.cpp
	$(CC) -I../tree_lib/ -c line_tree.cpp

line_segment.o: line_segment.cpp
	$(CC) -I../tree_lib/ -c line_segment.cpp

.PHONY: clean
clean:
	rm -rf *.o app
