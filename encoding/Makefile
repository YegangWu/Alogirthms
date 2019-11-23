CC=g++

app: app.o huffman.o
	$(CC) -o app *.o

app.o: app.cpp
	$(CC) -c app.cpp
	
huffman.o: huffman.cpp
	$(CC) -c huffman.cpp


.PHONY: clean
clean:
	rm -rf app *.o
