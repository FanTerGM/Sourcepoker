#include "../../headers/config/gameObject.h"
#include "../../headers/config/gameModes.h"

texasTable::texasTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers, numberOfNPCs) {}

void texasTable::dealCardtoPlayers() {
	for (Player& player : players) {
		player.cardToHand(deck, 2, true);
	}
}

void texasTable::dealFlop() { cardToHand(deck, 3, true);}
