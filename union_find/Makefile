CC=g++

app: app.o uf.o
	$(CC) -o app *.o

app.o: app.cpp
	$(CC) -c app.cpp

uf.o: uf.cpp
	$(CC) -c uf.cpp

.PHONY: clean
clean:
	rm -rf app *.o
