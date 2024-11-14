#include <gameObject.h>
#include <gameModes.h>

drawTable::drawTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers,numberOfNPCs) {}

void drawTable::dealCardsToPlayers() {
	for (Player& player: players) {
		player.cardToHand(deck, 5, true);
	}
}

std::string drawTable::getModeName() const{
	return "draw";
}

void drawTable::startGame(){
	do {
		createDeck();
		clearTable();
		dealCardsToPlayers();
		// Display the player's hand and the community card.
		std::cout << "Player hand:\n";
		for (Player& player : players) {
			std::cout << player.getUsername() << std::endl;
			player.showCards();
			if (player.getUsername().find("AI_") != std::string::npos) continue;
			std::cout << "Choose cards to replace: " << std::endl;
			player.replaceCard(deck);
			std::cout << "After replacement: " << std::endl;
			player.showCards();
		}
		determineWinner();
		std::cout << "Another round? (Press 1 to continue)" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

	} while (std::cin.get() == '1');
}

