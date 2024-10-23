#include "gameObject.h"
#include "Hand.h"

Hand::Hand() {}

int Hand::getHandSize() {
	return cards.size();
}

void Hand::clearHand() { cards.clear();}

void Hand::cardToHand(Deck& deck) {
	const Card& dealtCard = deck.deal();
	cards.push_back(dealtCard);
}

void Hand::cardToHandMulti(Deck& deck, int count) {
	for (int i = 0; i < count; i++) {
		const Card& dealtCard = deck.deal();
		cards.push_back(dealtCard);
	}
}

void Hand::showCards() {
	for (const Card& card : cards) {
		cout << card.getRank() << " of " << card.getSuit() << endl;
	}
}

vector<Card> Hand::getHand () { return cards; }