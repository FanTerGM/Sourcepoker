
#include "Card.h"
#include <iostream>


using namespace std;

Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

Card::Suit Card::getSuit() const { return suit; }
Card::Rank Card::getRank() const { return rank; }

