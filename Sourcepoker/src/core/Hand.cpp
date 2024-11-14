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

void Hand::replaceCard(Deck& deck){
	std::vector<int> cardToReplace;
	int i = 0;
	do {
		int a; std::cin >> a; 
		if (a == 0) break;
		cardToReplace.push_back(a-1);
	} while (++i && i <= 5);
	for (const int& i : cardToReplace) {
		const Card& dealtCard = deck.deal();
		cards[i] = dealtCard;
	}
}

void Hand::clearHand() {
	cards.clear();
}

void Hand::showCards() const {
	int i = 0;
	for (const Card& card : cards) {
		if (card.getShowState()) std::cout << ++i << ". " << card.getRank() << " of " << card.getSuit() << std::endl;
		else std::cout << "Hidden" << std::endl;
	}
}

std::vector<Card> Hand::getHand () const{
	return cards;
}

