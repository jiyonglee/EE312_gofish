//
// Created by brian on 11/7/2018.
//

#include "deck.h"
//default constructor
Deck::Deck() {
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 14; j++) {
            myCards[index] = Card(j,(Card::Suit)i);
            index++;
        }
    }
    myIndex = SIZE-1;
}

//shuffles deck by picking random card from first i cards then putting it at back
//i is decremented and operation repeats until i is 1
void Deck::shuffle() {
    srand(time(NULL));
    int currentIndex = myIndex;
    while(currentIndex>0){
        int randomIndex = rand()%(currentIndex + 1);
        Card temp = myCards[randomIndex];
        myCards[randomIndex] = myCards[currentIndex];
        myCards[currentIndex] = temp;
        currentIndex--;
    }
}

//returns card at top of deck
Card Deck::dealCard() {
    myIndex--;
    return myCards[myIndex + 1];
}

//returns current size of deck
int Deck::size() const {
    return myIndex + 1;
}