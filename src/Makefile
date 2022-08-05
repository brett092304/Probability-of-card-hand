output: Main.o Deck.o Card.o Hand.o
	g++ -Wall *.o -lpthread -o output

Main.o: Main.cpp
	g++ -Wall -c -lpthread Main.cpp

Deck.o: Deck.cpp Deck.h
	g++ -Wall -c -lpthread Deck.cpp

Card.o: Card.cpp Card.h
	g++ -Wall -c -lpthread Card.cpp

Hand.o: Hand.cpp
	g++ -Wall -c -lpthread Hand.cpp

debug: Main.cpp Deck.cpp Deck.h Card.cpp Card.h
	g++ -g Main.cpp Deck.cpp Card.cpp Hand.cpp -lpthread -o output.debug

clean:
	rm *.o output *.debug