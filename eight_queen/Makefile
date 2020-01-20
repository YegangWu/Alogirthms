CC=g++

app: app.o eight_queen.o
	$(CC) *.o -o app

app.o: app.cpp
	$(CC) -c app.cpp

eight_queen.o: eight_queen.cpp
	$(CC) -c eight_queen.cpp


.PHONY: clean
clean:
	rm -rf app *.o
