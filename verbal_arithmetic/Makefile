CC=g++
FLAG=-std=c++11

app: app.o verbal_arithmetic.o solution.o
	$(CC) *.o -o app

app.o: app.cpp
	$(CC) $(FLAG) -c app.cpp

solution.o: solution.cpp
	$(CC) $(FLAG) -c solution.cpp

verbal_arithmetic.o: verbal_arithmetic.cpp
	$(CC) $(FLAG) -c verbal_arithmetic.cpp

.PHONY: clean
clean:
	rm -rf app *.o
