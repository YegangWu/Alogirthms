app: app.o graph.o node.o eucycle.o
	g++ -o app *.o

app.o: app.cpp
	g++ -c app.cpp

graph.o: graph.cpp
	g++ -c graph.cpp

node.o: node.cpp
	g++ -c node.cpp

eucycle.o: eucycle.cpp
	g++ -c eucycle.cpp

.PHONY: clean
clean:
	rm -rf app *.o
