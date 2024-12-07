#include <gameObject.h>
#include <gameModes.h>

drawTable::drawTable(sf::RenderWindow& window, sf::Font& font, int numberOfPlayers, int numberOfNPCs) :
	window(window), font(font), Table(window, font, numberOfPlayers, numberOfNPCs) {}
drawTable::drawTable(sf::RenderWindow& window, sf::Font& font): window(window), font(font), Table(window, font) {}

void drawTable::dealCardsToPlayers() {
	for (Player& player : players) {
		player.cardToHand(deck, 5, true);
	}
}

std::string drawTable::getModeName() const{
	return "draw";
}

//void drawTable::startGame(){
//	do {
//		createDeck();
//		clearTable();
//		dealCardsToPlayers();
//		// Display the player's hand and the community card.
//		std::cout << "Player hand:\n";
//		for (Player& player : players) {
//			std::cout << player.getUsername() << std::endl;
//			player.showCards(window);
//			if (player.getUsername().find("AI_") != std::string::npos) continue;
//			std::cout << "Choose cards to replace: " << std::endl;
//			player.replaceCard(deck);
//			std::cout << "After replacement: " << std::endl;
//			player.showCards(window);
//		}
//		determineWinner();
//		std::cout << "Another round? (Press 1 to continue)" << std::endl;
//		std::cin.clear();
//		std::cin.ignore(1000, '\n');
//
//	} while (std::cin.get() == '1');
//}

