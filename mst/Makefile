CC=g++

app: app.o kruskal.o graph.o uf.o edge.o prim.o
	$(CC) -o app *.o 

app.o: app.cpp
	$(CC) -c app.cpp

edge.o: edge.cpp
	$(CC) -c edge.cpp

graph.o: graph.cpp
	$(CC) -c graph.cpp

uf.o: uf.cpp
	$(CC) -c uf.cpp

kruskal.o: kruskal.cpp
	$(CC) -c kruskal.cpp

prim.o: prim.cpp
	$(CC) -c prim.cpp

.PHONY: clean
clean:
	rm -rf *.o app
