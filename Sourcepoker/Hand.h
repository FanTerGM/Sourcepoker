#pragma once
#include "gameObject.h"

using namespace std; 

class Hand {
public:
    Hand();
    void organize();
    void evaluate();
    int getHandSize();
    void clearHand();

    void cardToHand(Deck& deck, int count, bool Shown);

    void showCards();
    vector<Card> getHand();

private:
    vector<Card> cards;
};
