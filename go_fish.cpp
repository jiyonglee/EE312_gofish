#include <iostream>
#include <fstream>
#include <cstdlib>     // Provides EXIT_SUCCESS

#include "player.h"

using namespace std;


// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);
void bookPairs(Player &p1, Player &p2, ofstream &myfile);
void turnP1(Player &p1, Player &p2, Deck &d, bool &p1Turn, ofstream &myfile);
void turnP2(Player &p1, Player &p2, Deck &d, bool &p1Turn, ofstream &myfile);


int main( )
{
    int numCards = 7; //opening hand size
    bool p1Turn = true; //indicates if it's player one's turn or not
    Player p1("Joe");
    Player p2("Jane");

    ofstream myfile("gofish_results.txt");
    if(!myfile.is_open()){
        cout<< "Unable to open file";
        return EXIT_FAILURE;
    }


    Deck d;  //create a deck of cards
    d.shuffle();

    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);
    myfile<< "Hands are dealt"<<endl;
    myfile << p1.getName() <<" has : " << p1.showHand() << endl;
    myfile << p2.getName() <<" has : " << p2.showHand() << endl;
    bookPairs(p1,p2, myfile); // books opening hands
    myfile<< "Turns begin now"<<endl;
    myfile<<"\n";

    while(true) {
        while (p1Turn) { //player one's turn
            turnP1(p1, p2, d, p1Turn, myfile);
            bookPairs(p1, p2, myfile);
            myfile<<"\n";
            if(p1.getBookSize() == 26){
                myfile<<p1.getName()<< " has won the game!";
                myfile.close();
                return EXIT_SUCCESS;
            }
        }
        while (!p1Turn) { //player two's turn
            turnP2(p1, p2, d, p1Turn, myfile);
            bookPairs(p1, p2, myfile);
            myfile<<"\n";
            if(p2.getBookSize() == 26){
                myfile<<p2.getName()<< " has won the game!";
                myfile.close();
                return EXIT_SUCCESS;
            }
        }
    }
}


//deals hands to both players
//input: pass by reference game deck, player, and normal pass # of cards to deal
void dealHand(Deck &d, Player &p, int numCards)
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}

//checks for pairs in both players hands and books them
//input: pass by reference both players and output file
void bookPairs(Player &p1, Player &p2, ofstream &myfile){
    Card c1; //temporary storage cards
    Card c2;
    while(p1.checkHandForBook(c1,c2)){ //books pairs until none left for p1
        c1 = p1.removeCardFromHand(c1);
        c2 = p1.removeCardFromHand(c2);
        p1.bookCards(c1,c2);
        myfile<<p1.getName() << " books the " << c1.rankString(c1.getRank())<<endl;
    }
    while(p2.checkHandForBook(c1,c2)){ //books pairs until none left for p2
        c1 = p2.removeCardFromHand(c1);
        c2 = p2.removeCardFromHand(c2);
        p2.bookCards(c1,c2);
        myfile<<p2.getName() << " books the " << c1.rankString(c1.getRank())<<endl;
    }
}

//one turn of player one asking for a card from player two
//if player two has it, player one gets the card and turn
//else, player one draws a card and passes turn
//input: pass by reference both players, the deck, boolean of if it's player one's turn, output file
void turnP1(Player &p1, Player &p2, Deck &d, bool &p1Turn, ofstream &myfile){
    if(p1.getHandSize() == 0){
        if(d.size()>0){
            p1.addCard(d.dealCard());
        }
        p1Turn = false;
    }
    Card currentCard = p1.chooseCardFromHand(); //select random card from hand
    myfile << p1.getName()<< " says- ";
    myfile << p2.getName() << " do you have a " << currentCard.rankString(currentCard.getRank()) << "?"<<endl;
    myfile<< p2.getName() << " says- ";
    if(p2.rankInHand(currentCard)){
        for(int i = 0; i<4;i++){ //searches for all four suits
            Card copy = Card(currentCard.getRank(),(Card::Suit)i);
            if(p2.cardInHand(copy)){ //if found, give to other player
                Card temp = p2.removeCardFromHand(copy);
                p1.addCard(temp);
            }
        }
        myfile<< "Yes, I have a " << currentCard.rankString(currentCard.getRank()) << endl;
    }
    else{
        myfile<< "Go Fish" << endl;
        if(d.size()>0){
            p1.addCard(d.dealCard());
        }
        p1Turn = false;
    }
}

//one turn of player two asking for a card from player one
//if player one has it, player two gets the card and turn
//else, player two draws a card and passes turn
//input: pass by reference both players, the deck, boolean of if it's player one's turn, output file
void turnP2(Player &p1, Player &p2,Deck &d, bool &p1Turn, ofstream &myfile){
    if(p2.getHandSize() == 0){
        if(d.size()>0){
            p2.addCard(d.dealCard());
        }
        p1Turn = true;
    }
    Card currentCard = p2.chooseCardFromHand();//select random card from hand
    myfile << p2.getName()<< " says- ";
    myfile << p1.getName() << " do you have a " << currentCard.rankString(currentCard.getRank()) << "?"<<endl;
    myfile<< p1.getName() << " says- ";
    if(p1.rankInHand(currentCard)){
        for(int i = 0; i<4;i++){ //searches for all four suits
            Card copy = Card(currentCard.getRank(),(Card::Suit)i);
            if(p1.cardInHand(copy)){ //if found, give to other player
                Card temp = p1.removeCardFromHand(copy);
                p2.addCard(temp);
            }
        }
        myfile<< "Yes, I have a " << currentCard.rankString(currentCard.getRank()) << endl;
    }
    else{
        myfile<< "Go Fish" << endl;
        if(d.size()>0){
            p2.addCard(d.dealCard());
        }
        p1Turn = true;
    }
}