#pragma once
#include "../config/gameObject.h" 

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
