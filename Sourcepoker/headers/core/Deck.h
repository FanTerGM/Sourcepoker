#pragma once

class Deck {
public:
    //Create a deck (unshuffled)
    Deck();

    //Take card from deck 
    Card deal(bool Shown);

    //get the number of remaning cards
    int remainingCards() const;

private:

    Card cards[52];
    int topCardIndex;
};