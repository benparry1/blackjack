blackjack: cards.o blackjack.o
        g++ cards.o blackjack.o -o blackjack
cards.o: cards.cpp
        g++ -c cards.cpp
blackjack.o: blackjack.cpp
        g++ -c blackjack.cpp
clean:
        rm *.o blackjack
