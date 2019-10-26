CC=g++

app: lsd.o app.o msd.o three_way_radix.o
	$(CC) -o app *.o

app.o: app.cpp
	$(CC) -c app.cpp

lsd.o: lsd.cpp
	$(CC) -c lsd.cpp

msd.o: msd.cpp
	$(CC) -c msd.cpp

three_way_radix.o: three_way_radix.cpp
	$(CC) -c three_way_radix.cpp

.PHYONY: clean
clean: 
	rm -rf *.o app
