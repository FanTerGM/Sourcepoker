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
	organize();
}

void Hand::replaceCard(int placeInVector, Deck& deck){
	const Card& dealtCard = deck.deal();
	cards[placeInVector] = dealtCard;
}

void Hand::clearHand() {
	cards.clear();
}

void Hand::showCards() {
	int i = 0;
	for (const Card& card : cards) {
		if (card.getShowState()) cout << ++i << ". " << card.getRank() << " of " << card.getSuit() << endl;
		else cout << "Hidden" << endl;
	}
}

vector<Card> Hand::getHand () const{
	return cards;
}

