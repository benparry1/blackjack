class Card{
public:

   Card();			//card class constructor
   char S;			//suit letter: D=diamond, C=clubs, S=spades, H=hearts
   int R;			//card rank: 1=A, 2=2, 3=3, 4=4 ... 10=10, 11=jack, 12=queen, 13=king 
};

class Deck{
public:

   Deck();			//deck class constructor
   void makeDeck();		//fills the deck with default order
   void printDeck() const;	//prints deck, converting 1,11,12 and 13 to letter equivalents
   ~Deck();			//destructor for dynamic array cards_d

   int num_cards;		//number of cards in the deck
   Card * cards_d;		//initialy, number of cards in set to 52, but when ever a card is delt, num_cards decreases bu the number of cards delt 
};

class Player{
public:

   Player();				//default constrcutor leaves money as zero and money will have to be set by addMoney
   Player(double m);			//constructor sets the players money to m
   ~Player();			        //destructor for dynamic array hand_p

   double bet(double amount);   	//take that amount away from player's money and add it to prize pool in game, make sure bet is not more than money
   void printHand() const;      	//prints the contents of the player's curent hand

   //mutators
   void addMoney(double amount);		  //adds money to player's money ie exchanges for chips
   void giveCard(int i, Card c);		  //puts card c into index i of the player's hand
   void changeSize();                             //increases the player's hand size by 1 
   void resizeArr(int size);                      //increases the player's hand size by size
   void clearHand();				  //deletes and reinitializes hand_p for use after a hand has been played
   void remCard(int index);   		          //removes the card at index i, and resizes hand

   //accessors
   int getSize() const;				  //returns size of the hand
   Card getCard(int i) const;			  //returns the card at index i
   double getMoney() const;			  //returns money
   int getValue(int i) const;			  //returns the value of the card at index i: 2=2,3=3,...,jack/queen/king=10 
   

private:
   int p_size;			        //size of the dynamic array hand_p
   Card * hand_p;			//dynamic array of type Cards, used to hold the cards that make up the player's hand
   double money;			//money available to bet with

};

class Dealer
{
public:

   void shuffle(Deck &d);        //shuffles the Deck d, for a full deck of 52 cards before any have been delt
   Dealer();			 //default constructor
   ~Dealer();			 //deconstructor

   void deal(Player &p,char s, Deck &d);             //adds one to the players hand size and adds a card to their hand
   void printHand() const;   			     //displays the cards on the dealer's hand
   void clearHand();			             //deletes the dealer's hand for a new game
   void showCard(int index) const;		     //displays only one specific card at index

   //accessors
   Card getCard(int i) const;        		     //returns the card at index i in dealer's hand
   int getSize() const;				     //returns the current size of the dealer's hand	
   int getValue(int i) const;			     //returns the value of the card at index i
private:

   Card * hand_d;                //dynamic array of cards that holds the dealer's hand for a game
   int d_size;			 //size of the dealer's hand
};

