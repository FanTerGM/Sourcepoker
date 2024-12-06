#include <gameObject.h>
#include <gameModes.h>

studTable::studTable(sf::RenderWindow& window, int numberOfPlayers, int numberOfNPCs) : Table(window, numberOfPlayers, numberOfNPCs) {}

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

void studTable::startGame(){
	do {
		createDeck();
		clearTable();
		dealFlop(); 
		dealCardsToPlayers();
		//draw table
		DefaultMode defaultMode(numberOfPlayers, numberOfNPCs);
		defaultMode.renderGame(window);
		// Display the player's hand and the community card.
		showPlayersHands();
		determineWinner();
		dialogBox();

	} while (continuePlaying);
}