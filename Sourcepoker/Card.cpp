#include "gameObject.h"


Card::Card() : suit(HEARTS), rank(TWO) {}

Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

Card::Suit Card::getSuitEnum() const { return suit; }
Card::Rank Card::getRankEnum() const { return rank; }

string Card::getSuit() const {
    switch (suit) {
    case HEARTS: return "Hearts";
    case DIAMONDS: return "Diamonds";
    case CLUBS: return "Clubs";
    case SPADES: return "Spades";
    default: return "Unknown";
    }
}

string Card::getRank() const {
    switch (rank) {
    case TWO: return "2";
    case THREE: return "3";
    case FOUR: return "4";
    case FIVE: return "5";
    case SIX: return "6";
    case SEVEN: return "7";
    case EIGHT: return "8";
    case NINE: return "9";
    case TEN: return "10";
    case JACK: return "Jack";
    case QUEEN: return "Queen";
    case KING: return "King";
    case ACE: return "Ace";
    default: return "Unknown";
    }
}

// Function to return the card as a string (e.g., "Ace of Spades")
string Card::toString() const {
    return getRank() + " of " + getSuit();
}
