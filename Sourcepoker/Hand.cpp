#include "gameObject.h"
#include "Hand.h"

Hand::Hand() {}

int Hand::getHandSize() {
	return cards.size();
}

void Hand::clearHand() { cards.clear();}

void Hand::addCard(const Card& card) {cards.push_back(card);}

vector<Card> Hand::getHand () { return cards; }