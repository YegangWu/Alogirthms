CC=g++
CFLAGS=-I. -I../graph/


app: app.o graph_basic.o dfs.o bfs.o ccomponents.o bipartite.o
	$(CC) -o app app.o dfs.o graph_basic.o bfs.o ccomponents.o bipartite.o

graph_basic.o: ../graph/graph_basic.cpp
	$(CC) -c ../graph/graph_basic.cpp 

dfs.o: dfs.cpp 
	$(CC) -c dfs.cpp $(CFLAGS) 

bfs.o: bfs.cpp 
	$(CC) -c bfs.cpp $(CFLAGS) 

ccomponents.o: ccomponents.cpp 
	$(CC) -c ccomponents.cpp $(CFLAGS) 

bipartite.o: bipartite.cpp
	$(CC) -c bipartite.cpp $(CFLAGS)

app.o: app.cpp
	$(CC) -c app.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o app
