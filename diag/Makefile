CC=G++
CFLAGS=-I. -I../graph

app: app.o diag.o graph_basic.o scc.o
	$(CC) -o app *.o

app.o: app.cpp
	$(CC) -c app.cpp $(CFLAGS)

diag.o: diag.cpp
	$(CC) -c diag.cpp $(CFLAGS)

graph_basic.o: ../graph/graph_basic.cpp
	$(CC) -c ../graph/graph_basic.cpp $(CFLAGS)

scc.o: scc.cpp
	$(CC) -c scc.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o app
