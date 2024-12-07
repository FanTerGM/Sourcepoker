#include <gameObject.h>
#include <gameModes.h>


drawTable::drawTable(sf::RenderWindow& window, sf::Font& font, std::vector<Player> players): Table(window, font, players) {
	this->startGame();
}

void drawTable::dealCardsToPlayers() {
	for (Player& player : players) {
		player.cardToHand(deck, 5, true);
	}
}

std::string drawTable::getModeName() const{
	return "draw";
}

void drawTable::startGame() {
	createDeck();
	clearTable();
	dealCardsToPlayers();

	// Display the player's hand and the community card.
	std::cout << "Player hand:\n";
	int xOffset = 100, yOffset = 100;
	for (Player& player : players) {
		std::cout << player.getUsername() << std::endl;
		player.showCards(window, xOffset, yOffset);
		if (player.getUsername().find("AI_") != std::string::npos) continue;
		std::cout << "Choose cards to replace: " << std::endl;
		player.replaceCard(deck);
		std::cout << "After replacement: " << std::endl;
		player.showCards(window, xOffset, yOffset);
	}
	determineWinner();
	dialogBox();
}

