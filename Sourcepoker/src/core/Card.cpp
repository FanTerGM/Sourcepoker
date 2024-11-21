#include "gameObject.h"

// Default constructor: initializes card as the 2 of Hearts.
Card::Card() : suit(HEARTS), rank(TWO) {}

// Constructor with specified suit and rank.
Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

// Gets the suit of the card as an enum value.
Card::Suit Card::getSuitEnum() const { return suit; }

// Gets the rank of the card as an enum value.
Card::Rank Card::getRankEnum() const { return rank; }

// Gets the show state of the card.
bool Card::getShowState() const { return isShown; }

// Sets whether the card is shown or hidden.
void Card::setShown(bool set) { isShown = set; }

// Converts the suit of the card to a string.
std::string Card::getSuit() const {
    switch (suit) {
    case HEARTS: return "Hearts";
    case DIAMONDS: return "Diamonds";
    case CLUBS: return "Clubs";
    case SPADES: return "Spades";
    default: return "Unknown";
    }
}

// Converts the rank of the card to a string.
std::string Card::getRank() const {
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

// Converts the card to a string in the format "Rank of Suit".
std::string Card::toString() const {
    return getRank() + " of " + getSuit();
}