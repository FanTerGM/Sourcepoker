#pragma once

class Hand {
public:
    Hand();

    //Sort the card according to Rank
    void organize();

    //Add card to Hand / Replace all current card. 
    void cardToHand(Deck& deck, int count, bool Shown);

    void replaceCard(Deck& deck);

    //Display Cards 
    void showCards() const;

    void clearHand();

   //Get vector cards that make up the Hand
    vector<Card> getHand() const ;

private:
    vector<Card> cards;
};
