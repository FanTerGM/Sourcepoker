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
		// terminate loop when 0 or out of bound index is entered
		if (a == 0 || a > cards.size()) break;
		// Contain all the card to replace in an array
		cardToReplace.push_back(a-1);
	} while (++i && i <= cards.size());

	// Perform adding new card via overwrite
	for (const int& i : cardToReplace) {
		const Card& dealtCard = deck.deal();
		cards[i] = dealtCard;
	}
}

void Hand::clearHand() {
	cards.clear();
}

void Hand::showCards(sf::RenderWindow& window, int xOffset, int yOffset) const {

	int i = 0;
	int cardOffset = 0;
	for (const Card& card : cards) {
		if (card.getShowState()) {
			std::cout << ++i << ". " << card.getRank() << " of " << card.getSuit() << std::endl;
			std::string cardName = card.toString();
			sf::Texture cardTexture;
			if (!cardTexture.loadFromFile("Resources/cards/" + cardName + ".png")) {
				std::cerr << "Error loading card image: " << cardName << std::endl;
				continue;
			}

			sf::Sprite cardSprite(cardTexture);
			cardSprite.setPosition(xOffset + cardOffset, yOffset); // position of card;
			cardSprite.setScale(0.1f, 0.1f);
			cardOffset += cardTexture.getSize().x * 0.2f;
			window.draw(cardSprite);
		}
		else {
			sf::Texture cardTexture;
			if (!cardTexture.loadFromFile("Resources/cards/back.png")) {
				std::cerr << "Error loading card image" << std::endl;
				continue;
			}

			sf::Sprite cardSprite(cardTexture);
			cardSprite.setPosition(xOffset + cardOffset, yOffset); // position of card;
			cardSprite.setScale(0.1f, 0.1f);
			cardOffset += cardTexture.getSize().x * 0.2f;
			window.draw(cardSprite);
		}
	}
}

std::vector<Card> Hand::getHand () const{
	return cards;
}

