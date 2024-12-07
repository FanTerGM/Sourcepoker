#include <gameObject.h>
#include <gameModes.h>

studTable::studTable(sf::RenderWindow& window, sf::Font& font, std::vector<Player> players) : Table(window, font, players) {}

void studTable::dealFlop() {
	for (Player& player : players) {
		player.cardToHand(deck, 2, true);
	}
}

void studTable::dealCardsToPlayers() {
	for (Player& player : players) {
		player.cardToHand(deck, 5, true);
	}
}

std::string studTable::getModeName() const{
	return "stud";
}

void studTable::startGame() {
	createDeck();
	clearTable();
	dealFlop();
	dealCardsToPlayers();
	drawTable(window);
	// Display the player's hand and the community card.
	showPlayersHands();
	determineWinner();
	dialogBox();
}