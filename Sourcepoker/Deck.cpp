#include "gameObject.h"
#include "Deck.h"

//Create a deck (unshuffled)
Deck::Deck(): topCardIndex(0){
	int index = 0;
	for (int s = Card::HEARTS; s <= Card::SPADES; s++) {
		for (int r = Card::TWO; r <= Card::ACE; r++) {
			cards[index++] = Card(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r));
		}
	}
}

void Deck::shuffle() {
	srand(unsigned(std::time(0))); // Seed for randomness
	random_shuffle(&cards[0], &cards[52]); // Shuffle the fixed array
}

Card Deck::deal() {
	if (topCardIndex < 52) return cards[topCardIndex++];
	throw out_of_range("Card not found, Deck out of bound");
}

int Deck::size() { return (52 - topCardIndex); }