CC=g++
CPPFLAGS=-Llib/
LIBS=-ltree

app: app.o line_tree.o line_segment.o
	$(CC) $(CPPFLAGS) $(LIBS) *.o -o app

app.o: app.cpp
	$(CC) -Ilib/ -c app.cpp

line_tree.o: line_tree.cpp
	$(CC) -Ilib/ -c line_tree.cpp

line_segment.o: line_segment.cpp
	$(CC) -Ilib/ -c line_segment.cpp

.PHONY: clean
clean:
	rm -rf *.o app
