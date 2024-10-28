#pragma once

class Hand {
public:
    Hand();

    //Sort the card according to Rank
    void organize();

    //Empty hand;
    void clearHand();

    //Add card to Hand
    void cardToHand(Deck& deck, int count, bool Shown);

    //Display Cards 
    void showCards();

   //Get vector cards that make up the Hand
    vector<Card> getHand();

private:
    vector<Card> cards;
};
