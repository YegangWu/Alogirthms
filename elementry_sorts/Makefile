CC=g++

app: app.o insertion.o shell_sort.o convex_hull.o
	$(CC) -o app *.o

app.o: app.cpp
	$(CC) -c app.cpp	

insertion.o: insertion.cpp
	$(CC) -c insertion.cpp

shell_sort.o: shell_sort.cpp
	$(CC) -c shell_sort.cpp

convex_hull.o: convex_hull.cpp
	$(CC) -c convex_hull.cpp

.PHONY: clean
clean:
	rm -rf app *.o
