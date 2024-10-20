#pragma once
#include "gameObject.h"
#include "Card.h"

class Deck {
public:
    Deck();
    void shuffle();
    Card deal();
    int size();

private:
    Card cards[52];
    int topCardIndex;
};