#include <gameObject.h>
#include <algorithm>
#include <random>


//Create a deck (unshuffled)
Deck::Deck(): topCardIndex(0){
	int index = 0;
	for (int s = Card::HEARTS; s <= Card::SPADES; s++) {
		for (int r = Card::TWO; r <= Card::ACE; r++) {
			cards[index++] = Card(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r));
		}
	}
	random_device rd;
	mt19937 eng(rd());
	shuffle(&cards[0], &cards[52], eng);
}

Card Deck::deal(bool Shown = true) {
	if (topCardIndex < 52) {
		cards[topCardIndex].setShown(Shown);
		return cards[topCardIndex++];
	}
	throw out_of_range("Card not found, Deck out of bound");
}

int Deck::size() { return (52 - topCardIndex); }