#include <gameObject.h>
#include <gameModes.h>

studTable::studTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers, numberOfNPCs) {}

void studTable::dealFlop() {
	for (Player& player : players) {
		player.cardToHand(deck, 2, false);
	}
}

void studTable::dealCardtoPlayers() {
	cardToHand(deck, 1, true);
}