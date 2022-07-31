output: Main.o Deck.o Card.o Hand.o
	g++ -Wall *.o -o output

Main.o: Main.cpp
	g++ -Wall -c Main.cpp

Deck.o: Deck.cpp Deck.h
	g++ -Wall -c Deck.cpp

Card.o: Card.cpp Card.h
	g++ -Wall -c Card.cpp

Hand.o: Hand.cpp Hand.h
	g++ -Wall -c Hand.cpp

clean:
	rm *.o output