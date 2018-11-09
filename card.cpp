//
// Created by brian on 11/7/2018.
//

#include "card.h"

//default constructor
Card::Card(){
    mySuit = spades;
    myRank = 1;
}

//constructor with
//inputs: card rank and card suit
Card::Card(int rank, Suit s) {
    mySuit = s;
    myRank = rank;
}

//returns boolean if this card matches Card c suitwise
//input: pass by ref card
bool Card::sameSuitAs(const Card &c) const {
    return c.mySuit == mySuit;
}

//return rank
int Card::getRank() const {
    return myRank;
}

//string format of card
string Card::toString() const {
    return rankString(myRank) + suitString(mySuit);
}

//string format of card suit
//input:card suit
string Card::suitString(Card::Suit s) const {
    switch (mySuit){
        case spades: return "s";
        case hearts: return "h";
        case diamonds: return "d";
        case clubs: return "c";
    }
}

//string format of card rank
//input: card rank
string Card::rankString(int r) const {
    if(r>1 && r<11){
        char buffer[33];
        sprintf(buffer,"%d",r);
        return buffer;
    } else{
        switch (r){
            case 1: return "A";
            case 11: return "J";
            case 12: return "Q";
            case 13: return "K";
        }
    }
}

//overloads == operator for cards
//suit and rank must match
bool Card::operator==(const Card &rhs) const {
    if(mySuit == rhs.mySuit){
        if(myRank == rhs.myRank){
            return true;
        }
    }
    return false;
}

//overloads != operator for cards
//either suit or rank must not match
bool Card::operator!=(const Card &rhs) const {
    if(mySuit == rhs.mySuit){
        if(myRank == rhs.myRank){
            return false;
        }
    }
    return true;
}