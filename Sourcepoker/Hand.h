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
    void addCard(const Card& card);
    vector<Card> getHand();

private:
    vector<Card> cards;
};
