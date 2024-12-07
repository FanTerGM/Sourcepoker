#pragma once
#include <gameObject.h>

class Hand {
public:
    Hand();

    ///Sort the card according to Rank
    void organize();

    //Add card to Hand / Replace all current card. 
    void cardToHand(Deck& deck, int count, bool Shown);

    // Replace card, currently only use for draw mode
    void replaceCard(Deck& deck);

    //Display Cards 
    void showCards(sf::RenderWindow& window, int xOffset, int yOffset) const;

    //Clear all cards in hand
    void clearHand();

   //Get vector cards that make up the Hand
    std::vector<Card> getHand() const ;

private:
    std::vector<Card> cards;
};
