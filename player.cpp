//
// Created by brian on 11/8/2018.
//

#include "player.h"

//adds a card to player's hand
//input: card to add to hand
void Player::addCard(Card c) {
    myHand.push_back(c);
}

//adds two cards to player's book
//input: pair of cards to add to book
void Player::bookCards(Card c1, Card c2) {
    myBook.push_back(c1);
    myBook.push_back(c2);
}

//returns if player's hand has a book or not
//input: cards to store book in
bool Player::checkHandForBook(Card &c1, Card &c2) {
    if(myHand.size()==0){
        return false;
    }
    for (int i = 0; i < myHand.size() - 1; i++) {
        vector<Card>::const_iterator iter;
        int currentRank = myHand[i].getRank(); //rank of starting card in for loop
        for (iter = myHand.begin()+ i + 1; iter != myHand.end(); iter++) {
            if((*iter).getRank() == currentRank){ //if card after starting card has same rank, true
                c1 = myHand[i];
                c2 = *iter;
                return true;
            }
        }
    }
    return false;
}

//returns random card from player's hand
Card Player::chooseCardFromHand() const {
    int size = myHand.size();
    srand(time(NULL));
    int index = rand()%size;
    return myHand[index]; //return card from random index
}

//returns boolean if another card of the same rank is in player's hand
//input: card with rank that is wanted
bool Player::rankInHand(Card c) const {
    vector<Card>::const_iterator iter;
    for(iter = myHand.begin(); iter!=myHand.end();iter++){
        if((*iter).getRank() == c.getRank()){ //if rank same, return true
            return true;
        }
    }
    return false;
}

//returns boolean of if player's hand has the card specified
//input: card to find in player's hand
bool Player::cardInHand(Card c) const {
    vector<Card>::const_iterator iter;
    iter = find(myHand.begin(),myHand.end(), c); //find card
    if(iter!= myHand.end()){
        return true;
    }
    return false;
}

//returns card to be removed from player's hand
//input: card to be removed
Card Player::removeCardFromHand(Card c) {
    vector<Card>::const_iterator iter;
    for (int i = 0; i < myHand.size(); i++) {
        if(myHand[i] == c){
            Card temp = myHand[i]; //store card
            myHand.erase(myHand.begin()+i); //remove card from hand
            return temp;
        }
    }
}

//returns string showing cards in the player's hand
string Player::showHand() const {
    string out; //output string
    vector<Card>::const_iterator iter;
    for(iter = myHand.begin(); iter!=myHand.end();iter++){
        out += " " + (*iter).toString();
    }
    return out;
}

//returns string showing cards in the player's book
string Player::showBooks() const {
    string out; //output string
    vector<Card>::const_iterator iter;
    for(iter = myBook.begin(); iter!=myBook.end();iter++){
        out += " " + (*iter).toString();
    }
    return out;
}

//returns size of player's book
int Player::getBookSize() const {
    return myBook.size();
}
//returns size of player's hand
int Player::getHandSize() const {
    return myHand.size();
}