CC=g++

app: bst.o app.o red_black_tree.o
	$(CC) -o app *.o
	
bst.o: bst.cpp bst.h
	$(CC) -c bst.cpp

app.o: app.cpp
	$(CC) -c app.cpp

red_black_tree.o: red_black_tree.cpp red_black_tree.h
	$(CC) -c red_black_tree.cpp

.PHONY: clean
clean:
	rm -rf app *.o
