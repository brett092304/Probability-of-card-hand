output: Main.o Deck.o Card.o
	g++ -Wall *.o -o output

Main.o: Main.cpp
	g++ -Wall -c Main.cpp

Deck.o: Deck.cpp Deck.h
	g++ -Wall -c Deck.cpp

Card.o: Card.cpp Card.h
	g++ -Wall -c Card.cpp

debug: Main.cpp Deck.cpp Deck.h Card.cpp Card.h
	g++ -g Main.cpp Deck.cpp Card.cpp -o output.debug

clean:
	rm *.o output *.debug