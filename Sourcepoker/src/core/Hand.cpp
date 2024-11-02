#include <gameObject.h>

Hand::Hand() {}

void Hand::organize() {
	sort(cards.begin(), cards.end(), [](Card& left, Card& right) {return left.getRank() < right.getRank();});
}

void Hand::cardToHand(Deck& deck, int count, bool Shown) {
	for (int i = 0; i < count; i++) {
		const Card& dealtCard = deck.deal(Shown);
		cards.push_back( dealtCard);
	}
}

void Hand::showCards() {
    organize();
	for (const Card& card : cards) {
		if (card.getShowState()) cout << card.getRank() << " of " << card.getSuit() << endl;
		else cout << "Hidden" << endl;
	}
}

vector<Card> Hand::getHand () {
	return cards;
}

