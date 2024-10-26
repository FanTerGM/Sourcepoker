#pragma once

class Deck {
public:
    Deck();
    Card deal(bool Shown);
    int size();

private:
    Card cards[52];
    int topCardIndex;
};