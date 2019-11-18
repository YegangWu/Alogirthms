CC=g++

app: app.o longest_palindrom.o knuth_morris_pratt.o regx_nfa.o digraph.o
	$(CC) -o app *.o

app.o: app.cpp
	$(CC) -c app.cpp

longest_palindrom.o: longest_palindrom.cpp
	$(CC) -c longest_palindrom.cpp

knuth_morris_pratt.o: knuth_morris_pratt.cpp
	$(CC) -c knuth_morris_pratt.cpp

regx_nfa.o: regx_nfa.cpp
	$(CC) -c regx_nfa.cpp

digraph.o: digraph.cpp
	$(CC) -c digraph.cpp

.PHONY: clean
clean:
	rm -rf *.o app
