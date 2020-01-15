CC=g++
CPPFLAG=-I../tree_lib
LIG=-ltree

app: app.o interval_tree.o
	$(CC)  *.o -o app
	
app.o: app.cpp
	$(CC) $(CPPFLAG) -c app.cpp

interval_tree.o: interval_tree.cpp
	$(CC) $(CPPFLAG) -c interval_tree.cpp

.PHONY: clean
clean:
	rm -rf *.o app
