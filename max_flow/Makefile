CC=g++

app: edge.o flow_graph.o ford_fulkerson.o app.o
	$(CC) -o app *.o

edge.o: edge.cpp
	$(CC) -c edge.cpp

flow_graph.o: flow_graph.cpp
	$(CC) -c flow_graph.cpp

ford_fulkerson.o: ford_fulkerson.cpp
	$(CC) -c ford_fulkerson.cpp

app.o: app.cpp
	$(CC) -c app.cpp

.PHONY: clean
clean:
	rm -rf *.o app
