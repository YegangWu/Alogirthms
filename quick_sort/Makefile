CC=g++

app: app.o quick_sort.o
	$(CC) -o app *.o

.cpp.o:
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm -rf app *.o
