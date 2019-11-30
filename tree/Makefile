CC=g++

app: bst.o app.o red_black_tree.o
	$(CC) -o app *.o
	
.cpp.o:
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm -rf app *.o
