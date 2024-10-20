#pragma once
#include "gameObject.h"

using namespace std; 

class Hand {
public:
    void organize();
    void evaluate();
    int getHandSize();
    vector<Card> getHand();

private:
    vector<Card> cards;
    int handSize;
};
