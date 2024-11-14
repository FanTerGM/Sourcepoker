#include <gameObject.h>
#include <gameModes.h>

texasTable::texasTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers, numberOfNPCs) {}

void texasTable::dealCardsToPlayers() {
	for (Player& player : players) {
		player.cardToHand(deck, 2, true);
	}
}

void texasTable::dealFlop() { cardToHand(deck, 3, true);}

std::string texasTable::getModeName() const{
	return "texas";
}
