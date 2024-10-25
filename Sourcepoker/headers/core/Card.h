#pragma once
#include "../../headers/config/gameObject.h"

using namespace std;

class Card {
public:
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
 
    Card();
    Card(Suit s, Rank r);

    //set the card to hidden when using showCards
    void setShown(bool set);
    bool getShowState() const;


    //get suit and rank as value;
    Suit getSuitEnum() const;
    Rank getRankEnum() const;

    //Fuction to get suit & rank as string
    string getSuit() const;
    string getRank() const;

    // Function to return the card as a string (e.g., "Ace of Spades")
    string toString() const;
    

private:
    bool isShown = true;
    Suit suit;
    Rank rank;

};