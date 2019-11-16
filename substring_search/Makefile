CC=g++

app: app.o longest_palindrom.o knuth_morris_pratt.o
	$(CC) -o app *.o

app.o: app.cpp
	$(CC) -c app.cpp

longest_palindrom.o: longest_palindrom.cpp
	$(CC) -c longest_palindrom.cpp

knuth_morris_pratt.o: knuth_morris_pratt.cpp
	$(CC) -c knuth_morris_pratt.cpp

.PHONY: clean
clean:
	rm -rf *.o app
