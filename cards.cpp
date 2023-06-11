#include "cards.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//helper function to shuffle deck
//used to check if the random number from rand() has been used before
bool isUnique(int n, int * arr, int c)
{
   for(int i=0; i<c; i++)
   {
      if(n==arr[i])
      {
         return false;
      }
   }
   return true;
}

Card::Card(){}				//card default constructor

Deck::Deck()				//deck default constructor, make a deck of 52 cards
{
   num_cards=52;
   cards_d=new Card[52];
}

Dealer::Dealer(){d_size=0;}		//Dealer constructor, sets hand size to zero

Player::Player(double m){money=m; p_size=0; hand_p=new Card[1];}  //sets money to m, hand size to 0 and creates a hand of size 1
Player::Player(){money=0; p_size=0; hand_p = new Card[1];}        //sets money to 0, hand size to 0 and creates a hand of size 1 

void Deck::makeDeck()  		//fills in the deck array with 52 cards in A-K order for hearts, diamonds, clubs, spades
{
   delete [] cards_d;		//if the deck has cards in it already, deletes and reinitializes array
   cards_d = new Card[52];
   num_cards=52;
   for(int i=0; i<=12; i++)
   {
      cards_d[i].S='H';
      cards_d[i].R=i+1;
   }
   for(int i=0; i<=12; i++)
   {
      cards_d[13+i].S='D';
      cards_d[13+i].R=i+1;

   }
   for(int i=0; i<=12; i++)
   {
      cards_d[26+i].S='C';
      cards_d[26+i].R=i+1;
   }
   for(int i=0; i<=12; i++)
   {
      cards_d[39+i].S='S';
      cards_d[39+i].R=i+1;
   }
}

void Deck::printDeck() const		//if  rank=1,11,12 or 13 then the number cannot be printed
{
   for(int i=0; i<num_cards; i++)
   {
      if(cards_d[i].R==1)
         cout<<'A'<<cards_d[i].S<<", ";
      else if(cards_d[i].R==11)
	 cout<<'J'<<cards_d[i].S<<", ";
      else if(cards_d[i].R==12)
         cout<<'Q'<<cards_d[i].S<<", ";
      else if(cards_d[i].R==13)
         cout<<'K'<<cards_d[i].S<<", ";
      else
         cout<<cards_d[i].R<<cards_d[i].S<<", ";
   }
   cout<<'\n';
} 

void Player::printHand() const		
{
   for(int i=0; i<p_size-1; i++)
   {
      if(hand_p[i].R==1)
         cout<<'A'<<hand_p[i].S<<", ";
      else if(hand_p[i].R==11)
         cout<<'J'<<hand_p[i].S<<", ";
      else if(hand_p[i].R==12)
         cout<<'Q'<<hand_p[i].S<<", ";
      else if(hand_p[i].R==13)
         cout<<'K'<<hand_p[i].S<<", ";
      else
         cout<<hand_p[i].R<<hand_p[i].S<<", ";
    }
    if(hand_p[p_size-1].R==1)
       cout<<'A'<<hand_p[p_size-1].S;
    else if(hand_p[p_size-1].R==11)
       cout<<'J'<<hand_p[p_size-1].S;
    else if(hand_p[p_size-1].R==12)
       cout<<'Q'<<hand_p[p_size-1].S;
    else if(hand_p[p_size-1].R==13)
       cout<<'K'<<hand_p[p_size-1].S;
    else
       cout<<hand_p[p_size-1].R<<hand_p[p_size-1].S;
}

void Dealer::printHand() const
{
   for(int i=0; i<d_size-1; i++)
   {
      if(hand_d[i].R==1)
         cout<<'A'<<hand_d[i].S<<", ";
      else if(hand_d[i].R==11)
         cout<<'J'<<hand_d[i].S<<", ";
      else if(hand_d[i].R==12)
         cout<<'Q'<<hand_d[i].S<<", ";
      else if(hand_d[i].R==13)
         cout<<'K'<<hand_d[i].S<<", ";
      else
         cout<<hand_d[i].R<<hand_d[i].S<<", ";
    }
    if(hand_d[d_size-1].R==1)
       cout<<'A'<<hand_d[d_size-1].S;
    else if(hand_d[d_size-1].R==11)
       cout<<'J'<<hand_d[d_size-1].S;
    else if(hand_d[d_size-1].R==12)
       cout<<'Q'<<hand_d[d_size-1].S;
    else if(hand_d[d_size-1].R==13)
       cout<<'K'<<hand_d[d_size-1].S;
    else
       cout<<hand_d[d_size-1].R<<hand_d[d_size-1].S;
}

void Dealer::showCard(int index) const
{
    if(hand_d[index].R==1)
       cout<<'A'<<hand_d[index].S;
    else if(hand_d[index].R==11)
       cout<<'J'<<hand_d[index].S;
    else if(hand_d[index].R==12)
       cout<<'Q'<<hand_d[index].S;
    else if(hand_d[index].R==13)
       cout<<'K'<<hand_d[index].S;
    else
       cout<<hand_d[index].R<<hand_d[index].S;
}


void Dealer::shuffle(Deck &d)		//uses rand() to pick a number between 0 and 52
{					//isUnique is then used to see if the random number generated is equal to any
					//previous number generated, and if it is not, it gets stored in r_array
   Deck copy;			        //if it has been used before, a new number gets generated and checked again
   int * r_array;			//this process is repeated untill all 52 numbers have been used
   r_array= new int[1];
					//the result is an array of randomized order 
   int * copy_arr;

   srand(time(0));
   int r=rand()%d.num_cards;
   r_array[0]=r;
   r=rand()%d.num_cards;
   
   int count=1;
   while(count<d.num_cards)   
   {
      if(isUnique(r,r_array,count))
      {
         copy_arr = new int[count];
         for(int i=0; i<count; i++)
            copy_arr[i]=r_array[i];
         r_array= new int[count+1];
         for(int i=0; i<count; i++)
            r_array[i]=copy_arr[i];
         r_array[count]=r;
         count++;
         delete [] copy_arr;
      }
      r=rand()%d.num_cards;
   }
   for(int i=0; i<d.num_cards; i++)			//the card at that random index is then copied into the copy deck
   {
      copy.cards_d[i]=d.cards_d[r_array[i]];
   }
   delete [] d.cards_d;					//the deck is then cleared and refilled with the randomized cards
   d.cards_d=new Card[d.num_cards];
   for(int i=0; i<d.num_cards; i++)
   {
      d.cards_d[i]=copy.cards_d[i];
   }

   delete [] r_array;
}

int Player::getSize() const
{
   return p_size;
}

void Player::giveCard(int i,Card c)
{
   hand_p[i]=c;
}

void Player::changeSize()
{
   p_size++;
}

void Player::remCard(int index)			//removes card at index and shifts to remove the empty spot
{
   Card copy_hand[p_size];
   for(int i=0; i<p_size; i++)
      copy_hand[i]=hand_p[i];

   p_size--;
   delete [] hand_p;
   hand_p=new Card[p_size];

   for(int i=0; i<p_size; i++)
   {
      if(i<index)
         hand_p[i]=copy_hand[i];
      else if(i>=index)
         hand_p[i]=copy_hand[i+1];
   }
}

void Player::resizeArr(int size)		//deletes and resizes hand_p to size
{
   if(p_size==0)
      hand_p= new Card[size];
   else
   {
      delete [] hand_p;
      hand_p = new Card[size];
   }
}

Card Player::getCard(int i) const
{
   return hand_p[i];
}

Card Dealer::getCard(int i) const
{
   return hand_d[i];
} 

double Player::bet(double amount)
{
   if(amount<=money && amount>0)
   {
      money-=amount;
      return amount;
   }
   else
   {
      while(amount>money)
      {
         cout<<"Bet is greater than money available.\nPlease enter an new amount: ";
         cin>>amount;
      }
      money-=amount;
      return amount;
   }
}

void Player::addMoney(double amount)
{
   money+=amount;

}

int Dealer::getSize() const
{
   return d_size;
}

double Player::getMoney() const
{
   return money;
}

int Dealer::getValue(int i) const
{
   int choice;
   if(hand_d[i].R==1)
   {
     return 11;
   }
   else if(hand_d[i].R>1 && hand_d[i].R<10)
      return hand_d[i].R;
   else
      return 10;
}

int Player::getValue(int i) const
{
   int choice;
   if(hand_p[i].R==1)
   {
      return 11;
   }
   else if(hand_p[i].R>1 && hand_p[i].R<10)
      return hand_p[i].R;
   else
      return 10;
}

void Dealer::deal(Player &p, char s, Deck &d)		//takes the card on top of deck and asigns it to the players hand
{							//adjusts the sizes of the deck and player's hand
   if(s=='p')
   {
      if(p.getSize()==0)
      {
         p.changeSize();    //p++
         p.resizeArr(p.getSize());
         if(d.num_cards==0)
         {
            d.makeDeck();
            shuffle(d);
         }
         p.giveCard(0,d.cards_d[d.num_cards-1]);
         d.num_cards--;
      }
      else{
         Card copy[p.getSize()];
         for(int i=0; i<p.getSize(); i++)
            copy[i]=p.getCard(i);

         p.changeSize();		//p_size++
         p.resizeArr(p.getSize());      //delete [] hand_p; hand_p= new Card[p_size];

         for(int i=0; i<p.getSize()-1; i++)
            p.giveCard(i,copy[i]);
         if(d.num_cards==0)
         {
            d.makeDeck();
            shuffle(d);
         }
         p.giveCard(p.getSize()-1,d.cards_d[d.num_cards-1]);
         d.num_cards--;
      }
   }
   else if(s=='d')
   {
      if(d_size==0)
      {
         d_size++;
         hand_d=new Card[d_size];
         if(d.num_cards==0)
         {
            d.makeDeck();
            shuffle(d);
         }
         hand_d[0]=d.cards_d[d.num_cards-1];
         d.num_cards--;
      }
      else
      {
         Card copy[d_size];
         for(int i=0; i<d_size; i++)
            copy[i]=hand_d[i];
         d_size++;
         delete [] hand_d;
         hand_d = new Card[d_size];
         for(int i=0; i<d_size-1; i++)
            hand_d[i]=copy[i];
         if(d.num_cards==0)
         {
            d.makeDeck();
            shuffle(d);
         }
         hand_d[d_size-1]=d.cards_d[d.num_cards-1];
         d.num_cards--;
      }
   }
   else
      cout<<"invalid entry";

}

void Dealer::clearHand()
{
   delete [] hand_d;
   d_size=0;
   hand_d=new Card[1];
}

void Player::clearHand()
{
   delete [] hand_p;
   p_size=0;
   hand_p=new Card[1];
}


Deck::~Deck(){ delete [] cards_d;}
Dealer::~Dealer(){delete[] hand_d;}
Player::~Player(){delete [] hand_p;}
