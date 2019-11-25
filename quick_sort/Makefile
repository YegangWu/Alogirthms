CC=g++

app: app.o quick_sort.o
	$(CC) -o app *.o

app.o: app.cpp
	$(CC) -c app.cpp

quick_sort.o: quick_sort.cpp
	$(CC) -c quick_sort.cpp

.PHONY: clean
clean:
	rm -rf app *.o
