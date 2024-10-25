#include "../../headers/config/gameObject.h"
#include "../../headers/config/gameModes.h"

drawTable::drawTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers,numberOfNPCs) {}

void drawTable::dealCardtoPlayers() {
	for (Player& player: players) {
		cardToHand(deck, 5, true);
	}
}

