CC=g++

app: app.o kd_tree.o
	$(CC) *.o -o app

app.o: app.cpp
	$(CC) -c app.cpp

kd_tree.o: kd_tree.cpp
	$(CC) -c kd_tree.cpp

.PHONY: clean
clean:
	rm -rf app *.o
