CC=g++

app: graph.o edge.o dijkstra.o app.o topological_sort.o diag.o bellman_ford.o
	$(CC) -o app *.o
	
app.o: app.cpp
	$(CC) -c app.cpp

edge.o: edge.cpp
	$(CC) -c edge.cpp

graph.o: graph.cpp
	$(CC) -c graph.cpp

dijkstra.o: dijkstra.cpp
	$(CC) -c dijkstra.cpp

diag.o: diag.cpp
	$(CC) -c diag.cpp

topological_sort.o: topological_sort.cpp
	$(CC) -c topological_sort.cpp

bellman_ford.o: bellman_ford.cpp
	$(CC) -c bellman_ford.cpp

.PHONY: clean
clean:
	rm -rf *.o app
