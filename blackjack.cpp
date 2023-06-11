#include <iostream>
#include <stdlib.h>
#include "cards.h"
#include <unistd.h>
#include <iomanip>
using namespace std;

int main()
{
   //create deck c that will be played with, initialize that deck, then shuffle it so its ready for game play

   cout<<fixed<<setprecision(2);		//sets the precision of any numbers to 2 decimal places

   Deck c;
   c.makeDeck();
   double prize=0;				//prize tracks the bets
   char play;					//play condition for while loop
   int run_count;				//run_count keeps track of the sum of the player's hand
   int dealer_count;				//dealer_count keeps track fo the sum of the dealer's hand


   Dealer D;			
   Player P;
   D.shuffle(c);

   cout<<"\nWelcome to the blackjack table! My name is Daniel, I'll be the dealer today.\n";
   cout<<"Please enter an the amount you'd like to trade for chips: ";
   double p;
   do{cin>>p;}
   while(p<0);			//make sure number is positive
   
   P.addMoney(p);		//sets player's money to p
   
   cout<<"\nExcellent, you know have $"<<P.getMoney()<<" to bet with.\n";

   char choice;
   cout<<"\nWould you like to begin the game?   [Y/N]: ";
   cin>>choice;
   
   if(choice=='N'||choice=='n')
   {
      do {cout<<"\nThat's alright, let me know when you're ready.\n\nAre you ready to begin now?    [Y/N]: ";
      cin>>choice;}while(choice=='N'||choice=='n');
   }
   do{
      prize=0;			//each time the loop runs, resets the bet, and the counts
      run_count=0;
      dealer_count=0;

      cout<<"How much would you like to bet [$"<<P.getMoney()<<" available]: ";
      cin>>p;
      while(p<0)
      {
         cout<<"Invalid bet, enter another amount: ";
         cin>>p;
      }								//make sure the bet is a valid amount
      prize=P.bet(p);						//subtract p from player's money and assign prize

      cout<<"\nDealing cards now...\n";
      sleep(1);

      //deal the user one, then the dealer, do this twice
      D.deal(P, 'p', c);				
      D.deal(P, 'd', c);
      D.deal(P, 'p', c);
      D.deal(P, 'd', c);

      dealer_count=D.getValue(0)+D.getValue(1);			//add up the dealer's intial count for intial blackjack cases 

      cout<<"\nYour cards are: ";
      P.printHand();

      cout<<"\nThe dealer's card: ";				//only show the first card, since the second is "face down"
      D.showCard(0);

      cout<<'\n';      
      if(P.getValue(0)+P.getValue(1)==21)	//if player is dealt blackjack from the start. The only way for the total to be 21 from the start is to have blackjack.
      {
         if(dealer_count==21)		//if both have 21 ->push
         {
            cout<<"\nTie!\n"; 
            cout<<"\nYour hand: ";
            P.printHand();
            cout<<"\nDealer's hand: ";
            D.printHand();
            cout<<"\n\nNo loss or gain: $"<<prize<<" returned.\n";
            P.addMoney(prize);
            cout<<"Your current balance is: $"<<P.getMoney()<<'\n';
            cout<<"\nWould you like to play again?    [Y/N]: ";
            cin>>play;
         }
         else				//if only the player has blackjack, then players gets paid 1.5*bet
         {
            cout<<"\nBlackjack!\n";
            cout<<"\nYour hand: ";
            P.printHand();
            cout<<"\nDealer's hand: ";
            D.printHand();
            cout<<"\n\nYou won: $"<<prize*1.5<<'\n';
            P.addMoney(prize*1.25);
            cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
            cout<<"\nWould you like to play again?    [Y/N]: ";
            cin>>play;
         }
      }
      else if(P.getValue(0)==P.getValue(1))	//in the case the two cards have the same value, the option to split is presented
      {
         cout<<"\nWould you like to split your cards?    [Y/N]: ";
         cin>>choice;
         if(choice=='Y' || choice=='y' && P.getMoney()>=prize)		//the player does want to split and an addition hand is played: two hands at once, with the second hand matching the original bet
            { 
               int run_count2=0;
               Player P2;
               P2.giveCard(0,P.getCard(1));
               P2.changeSize();
               P.remCard(1);
               cout<<"\nDealing second cards...\n";
               sleep(.5);
               D.deal(P,'p',c );
               D.deal(P2, 'p', c);
               cout<<"\nFirst hand: ";
               P.printHand();
               cout<<"\nSecond hand: ";
               P2.printHand();

               prize+=P.bet(prize);
               cout<<"\n\nPlaying first hand: \n\n";
               if(P.getValue(0)+P.getValue(1)==21) 	//in the case the hand 1 is 21
               {
                  if(dealer_count==21)			//if dealer also has 21 -> push
                  {
                     cout<<"Tie!\n";
                     cout<<"\nYour hand: ";
                     P.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nNo loss or gain: $"<<prize/2<<" returned for hand one.\n";
                     P.addMoney(prize/2);
                     cout<<"Your current balance is: $"<<P.getMoney()<<'\n';
                  }
                  else					//if the dealer does not also have 21 -> player gets paid 1.5x the bet
                  {
                     cout<<"Blackjack!\n";
                     cout<<"\nYour hand: ";
                     P.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nYou won: $"<<prize*1.25<<'\n';
                     P.addMoney(1.25*prize);  //half of total prize is bet on each game, pay out if 1.5 prize -> origianl bet=prize/2 + payout=1.5*prize/2
                     cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                  }                  
               }
               else  			//hand 1 is not 21-> regular play for the first hand
               {
                  run_count=P.getValue(0)+P.getValue(1);
                  cout<<"Would you like another card for the first hand?    [Y/N]: ";
                  cin>>choice;
                  while(choice=='y'|| choice=='Y' && run_count<21)
                  {
                     cout<<"\nDealing new card...";
                     sleep(0.5);
                     D.deal(P,'p',c);
                     run_count+=P.getValue(P.getSize()-1);
                     cout<<"\nYour new hand is: ";
                     P.printHand();
                     cout<<'\n';
                     if(run_count<21)
                     {
                        cout<<"\nWould you like another card?    [Y/N]: ";
                        cin>>choice;
                     }
                     else 
                        choice='n';
                  }
                  
                  if(run_count>21)		//bust
                  {
                     cout<<"\nBust!\n";
                     cout<<"\nYour hand: ";
                     P.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nYou lost $"<<prize/2<<'\n';
                     cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                  }
                  else
                  {
                     while(dealer_count<17)		//play dealer's hand
                     {
                        D.deal(P,'d',c);
                        dealer_count+=D.getValue(D.getSize()-1);
                     }

                     if(dealer_count>21)			//dealer bust
                     {
                        cout<<"\nDealer bust. You win!\n";
                        cout<<"\nYour hand: ";
                        P.printHand();
                        cout<<"\nDealer's hand: ";
                        D.printHand();
                        cout<<"\n\nYou won $"<<prize/2<<"\n";
                        P.addMoney(prize);
                        cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                     }
                     else if(run_count==dealer_count)           //push scenerio
                     {
                        cout<<"\nTie!\n";
                        cout<<"\nYour hand: ";
                        P.printHand();
                        cout<<"\nDealer's hand: ";
                        D.printHand();
                        cout<<"\n\nNo loss or gain: $"<<prize<<" returned.\n";
                        P.addMoney(prize/2);
                        cout<<"Your current balance is: $"<<P.getMoney()<<'\n';
                     }
                     else if(run_count<dealer_count)            //House wins
                     {
                        cout<<"\nHouse wins.\n";
                        cout<<"\nYour hand: ";
                        P.printHand();
                        cout<<"\nDealer's hand: ";
                        D.printHand();
                        cout<<"\n\nYou lost $"<<prize/2<<'\n';
                        cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                     }
                     else   //Player wins
                     {
                        cout<<"\nYou win!\n";
                        cout<<"\nYour hand: ";
                        P.printHand();
                        cout<<"\nDealer's hand: ";
                        D.printHand();
                        cout<<"\n\nYou won $"<<prize/2<<'\n';
                        P.addMoney(prize);
                        cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                     }
                  }
               }

               cout<<"\nPlaying second hand:\n\n";		//run scenerios of the seond split hand
               cout<<"Reminder, second hand is: ";
               P2.printHand();
               cout<<'\n';
               if(P2.getValue(0)+P2.getValue(1)==21)	//check is hand 2 is black jack
               {
                  if(dealer_count==21)  //if dealer also has 21 then it is a push
                  {
                     cout<<"\nTie!\n";
                     cout<<"\nYour hand: ";
                     P2.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nNo loss or gain: $"<<prize/2<<" returned for hand one.\n";
                     P.addMoney(prize/2);
                     cout<<"Your current balance is: $"<<P.getMoney()<<'\n';
                     cout<<"\nWould you like to play again?    [Y/N]: ";
                     cin>>play;

                  }
                  else			//if dealer does not have 21 then player wins 1.5x their bet
                  {
                     cout<<"\nBlackjack!\n";
                     cout<<"\nYour hand: ";
                     P2.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nYou won: $"<<prize*1.25<<'\n';
                     P.addMoney(1.25*prize);  					//half of total prize is bet on each game, pay out if 1.5 prize -> origianl bet=prize/2 + payout=1.5*prize/2
                     cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                     cout<<"\nWould you like to play again?    [Y/N]: ";
                     cin>>play;
                  }

               }
               else		//hand 2 is not blackjack -> regular play for hand 2
               {
                  run_count2=P2.getValue(0)+P2.getValue(1);
                  cout<<"\nWould you like another card for the second hand?    [Y/N]: ";
                  cin>>choice;
                  while(choice=='y'|| choice=='Y' && run_count2<21)
                  {
                     cout<<"\nDealing new card...";
                     sleep(0.5);
                     D.deal(P2,'p',c);
                     run_count2+=P2.getValue(P2.getSize()-1);
                     cout<<"\nYour new hand is: ";
                     P2.printHand();
                     cout<<'\n';
                     if(run_count2<21)
                     {
                        cout<<"\nWould you like another card?    [Y/N]: ";
                        cin>>choice;
                     }
                     else
                        choice='n';
                  }

                  if(run_count2>21)		//player bust
                  {
                     cout<<"\nBust!\n";
                     cout<<"\nYour hand: ";
                     P2.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nYou lost $"<<prize/2<<'\n';
                     cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                     cout<<"\nWould you like to play again?    [Y/N]: ";
                     cin>>play;
                  }
                  else				//if player has not bust then the dealer plays their hand
                  {
                     cout<<"\nPlaying dealer's hand...\n";
                     sleep(1);
                     while(dealer_count<17)
                     {
                        D.deal(P,'d',c);
                        dealer_count+=D.getValue(D.getSize()-1);
                     }

                     if(dealer_count>21)		//if dealer busts, then if the player has not busted, wins
                     {
                        cout<<"\nDealer bust. You win!\n";
                        cout<<"\nYour hand: ";
                        P.printHand();
                        cout<<"\nDealer's hand: ";
                        D.printHand();
                        cout<<"\n\nYou won $"<<prize/2<<"\n";
                        P.addMoney(prize);
                        cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                        cout<<"\nWould you like to play again?    [Y/N]: ";
                        cin>>play;
                     }
                     else if(run_count2==dealer_count)           //push scenerio
                     {
                        cout<<"\nTie!\n";
                        cout<<"\nYour hand: ";
                        P2.printHand();
                        cout<<"\nDealer's hand: ";
                        D.printHand();
                        cout<<"\n\nNo loss or gain: $"<<prize/2<<" returned.\n";
                        P.addMoney(prize/2);
                        cout<<"Your current balance is: $"<<P.getMoney()<<'\n';
                        cout<<"\nWould you like to play again?    [Y/N]: ";
                        cin>>play;
                     }
                     else if(run_count2<dealer_count)            //House wins
                     {
                        cout<<"\nHouse wins.\n";
                        cout<<"\nYour hand: ";
                        P2.printHand();
                        cout<<"\nDealer's hand: ";
                        D.printHand();
                        cout<<"\n\nYou lost $"<<prize/2<<'\n';
                        cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                        cout<<"\nWould you like to play again?    [Y/N]: ";
                        cin>>play;
                     }
                     else               //Player wins
                     {
                        cout<<"\nYou win!\n";
                        cout<<"\nYour hand: ";
                        P2.printHand();
                        cout<<"\nDealer's hand: ";
                        D.printHand();
                        cout<<"\n\nYou won $"<<prize/2<<'\n';
                        P.addMoney(prize);
                        cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                        cout<<"\nWould you like to play again?    [Y/N]: ";
                        cin>>play;
                     }
                  }
               }
               
               P2.clearHand();		//clear P2 for next game
            }
            else		//does not want to split-> regular play for the orinal hand of 2 same-valued cards
            {
               if(P.getMoney()<prize)
                  cout<<"\nSorry, not enough funds to split cards.\n";
               run_count=P.getValue(0)+P.getValue(1);
               cout<<"\nWould you like another card?    [Y/N]: ";
               cin>>choice;

               while(choice=='y' || choice=='Y' && run_count<21)	//player hits one card at a time until holds or busts
               {
                  cout<<"\nDealing new card...";
                  sleep(0.5);
                  D.deal(P,'p',c);
                  cout<<"\nYour new hand: ";
                  P.printHand();
                  cout<<'\n';
                  run_count+=P.getValue(P.getSize()-1);
                  if(run_count<21)
                  {
                     cout<<"\nWould you like another card?    [Y/N]: ";
                     cin>>choice;
                  }
                  else
                     choice='n';
               }

               if(run_count>21)    //player bust
               {
                  cout<<"\nBust!\n";
                  cout<<"\nYour hand: ";
                  P.printHand();
                  cout<<"\nDealer's hand: ";
                  D.printHand();
                  cout<<"\n\nYou lost $"<<prize<<'\n';
                  cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                  cout<<"Would you like to play again?    [Y/N]: ";
                  cin>>play;
               }	
               else	//if player has not busted, then dealer plays hand
               {
                  cout<<"\nPlaying dealer's hand...\n";
                  sleep(1);
                  while(dealer_count<17)
                  {
                     D.deal(P,'d',c);
                     dealer_count+=D.getValue(D.getSize()-1);
                  }

                  if(dealer_count>21)		//dealer bust
                  {
                     cout<<"\nDealer bust. You win!\n";
                     cout<<"\nYour hand: ";
                     P.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nYou won $"<<prize<<"\n";
                     cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                     cout<<"\nWould you like to play again?    [Y/N]: ";
                     cin>>play;
                  }
                  else if(run_count==dealer_count)		//push scenerio
                  {
                     cout<<"\nTie!\n";
                     cout<<"\nYour hand: ";
                     P.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nNo loss or gain: $"<<prize<<" returned.\n";
                     P.addMoney(prize);
                     cout<<"Your current balance is: $"<<P.getMoney()<<'\n';
                     cout<<"\nWould you like to play again?    [Y/N]: ";
                     cin>>play;
                  }
                  else if(run_count<dealer_count)		//house wins
                  {
                     cout<<"\nHouse wins.\n";
                     cout<<"\nYour hand: ";
                     P.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nYou lost $"<<prize<<'\n';
                     cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                     cout<<"\nWould you like to play again?    [Y/N]: ";
                     cin>>play;
                  }
                  else					//Player wins
                  {
                     cout<<"\nYou win!\n";
                     cout<<"\nYour hand: ";
                     P.printHand();
                     cout<<"\nDealer's hand: ";
                     D.printHand();
                     cout<<"\n\nYou won $"<<prize<<'\n';
                     P.addMoney(2*prize);
                     cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                     cout<<"\nWould you like to play again?    [Y/N]: ";
                     cin>>play;
                  }
               }                
            }    
         }          
         else   //regular two different cards, less than 21
         {
            run_count=P.getValue(0)+P.getValue(1);            

            if(run_count==9 || run_count==10 || run_count==11)		//if player has a 9,10,11 from the start, they can
            {								//double their bet and get just 1 more card
               cout<<"\nWould you like to double down?    [Y/N]: ";
               cin>>choice;
   
               if(choice=='y' || choice=='Y')				//if they want to double down, deal one more card
               {
                  prize+=P.bet(prize);
                  cout<<"\nDealing new card...\n";
                  sleep(0.5);
                  D.deal(P,'p',c);
                  run_count+=P.getValue(P.getSize()-1);
               }	
               else							//if they do not than regular hit
               {
                  cout<<"\nWould you like another card?    [Y/N]: ";
                  cin>>choice;

                  while(choice=='y'|| choice=='Y' && run_count<21)
                  {
                     cout<<"\nDealing new card...";
                     sleep(0.5);
                     D.deal(P,'p',c);
                     run_count+=P.getValue(P.getSize()-1);
                     cout<<"\nYour new hand is: ";
                     P.printHand();
                     cout<<'\n';
                     if(run_count<21)
                     {
                        cout<<"\nWould you like another card?    [Y/N]: ";
                        cin>>choice;
                     }
                     else
                        choice='n';
                  }
               }
            }
            else if(run_count!=9 && run_count!=10 && run_count!=11)	//if not a double down scenerio, then just regular hit
            {
               cout<<"\nWould you like another card?    [Y/N]: ";
               cin>>choice;

               while(choice=='y'|| choice=='Y' && run_count<21)
               {   
                  cout<<"\nDealing new card..."; 
                  sleep(0.5);
                  D.deal(P,'p',c);
                  run_count+=P.getValue(P.getSize()-1);
                  cout<<"\nYour new hand is: ";
                  P.printHand();
                  cout<<'\n';
                  if(run_count<21)
                  {
                     cout<<"\nWould you like another card?    [Y/N]: ";
                     cin>>choice;
                  }
                  else
                     choice='n';
               }
            }
            if(run_count>21)			//Bust
            {
               cout<<"\nBust!\n";
               cout<<"\nYour hand: ";
               P.printHand();
               cout<<"\nDealer's hand: ";
               D.printHand();
               cout<<"\n\nYou lost $"<<prize<<'\n';
               cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
               cout<<"\nWould you like to play again?    [Y/N]: ";
               cin>>play;
            }
            else	//if player has not busted, play dealer's hand
            {
               cout<<"\nPlaying dealer's hand...\n";
               sleep(1);
               while(dealer_count<17)
               {
                  D.deal(P,'d',c);
                  dealer_count+=D.getValue(D.getSize()-1);
               }
            
               if(dealer_count>21)		//dealer bust
               {
                  cout<<"\nDealer bust. You win!\n";
                  cout<<"\nYour hand: ";
                  P.printHand();
                  cout<<"\nDealer's hand: ";
                  D.printHand();
                  cout<<"\n\nYou won $"<<prize<<"\n";
                  P.addMoney(2*prize);
                  cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                  cout<<"\nWould you like to play again?    [Y/N]: ";
                  cin>>play;
               }
               else if(run_count==dealer_count)		//push scenerio
               {
                  cout<<"\nTie!\n";
                  cout<<"\nYour hand: ";
                  P.printHand();
                  cout<<"\nDealer's hand: ";
                  D.printHand();
                  cout<<"\n\nNo loss or gain: $"<<prize<<" returned.\n";
                  P.addMoney(prize);
                  cout<<"Your current balance is: $"<<P.getMoney()<<'\n';
                  cout<<"\nWould you like to play again?    [Y/N]: ";
                  cin>>play;
               }  
               else if(run_count<dealer_count)		//House wins
               {
                  cout<<"\nHouse wins.\n";
                  cout<<"\nYour hand: ";
                  P.printHand();
                  cout<<"\nDealer's hand: ";
                  D.printHand();
                  cout<<"\n\nYou lost $"<<prize<<'\n';
                  cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                  cout<<"\nWould you like to play again?    [Y/N]: ";
                  cin>>play;
               }
               else		//Player wins
               {
                  cout<<"\nYou win!\n";
                  cout<<"\nYour hand: ";
                  P.printHand();
                  cout<<"\nDealer's hand: ";
                  D.printHand();
                  cout<<"\n\nYou won $"<<prize<<'\n';
                  P.addMoney(2*prize);
                  cout<<"Your new balance is: $"<<P.getMoney()<<'\n';
                  cout<<"\nWould you like to play again?    [Y/N]: ";
                  cin>>play;
               }     
            }
         }
      D.clearHand();		//clear player and dealer hand for next run through while loop
      P.clearHand();
       
   }while(play=='Y'||play=='y' && P.getMoney()>0);	//if user chooses to play again and they still have money to get, repeat

cout<<"\nThank you for playing! Your winnings are: $"<<P.getMoney()<<"\n\n";	//if not, say goodbye
cout.precision();								//reset cout
return 0;
}
