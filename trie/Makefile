CC=g++

app: node.o trie.o app.o
	$(CC) -o app *.o

app.o: app.cpp
	$(CC) -c app.cpp

node.o: node.cpp
	$(CC) -c node.cpp

trie.o : trie.cpp
	$(CC) -c trie.cpp

.PHONY: clean
clean: 
	rm -rf *.o app
