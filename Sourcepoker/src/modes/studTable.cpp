#include <gameObject.h>
#include <gameModes.h>

studTable::studTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers, numberOfNPCs) {}

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
		// Display the player's hand and the community card.
		showPlayersHands();
		determineWinner();
		std::cout << "Another round? (Press 1 to continue)" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

	} while (std::cin.get() == '1');
}