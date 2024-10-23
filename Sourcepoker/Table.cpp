#include "gameObject.h"


Table::Table() : mode(TEXAS), numberOfPlayer(1), numberOfNPC(1) { populateTable(); }
Table::Table(gameMode g, int numberOfPlayer, int numberOfNPC) : mode(g), numberOfPlayer(numberOfPlayer), numberOfNPC(numberOfNPC) { populateTable();}


void Table::populateTable() {
	for (int i = 0; i < numberOfPlayer; i++) {
		string input;
		cin >> input;
		Player player(input);
		players.push_back(player);
	}

	for (int i = 0; i < numberOfNPC; i++) {
		string name = "AI_" + to_string(i);
		Player AI(name);
		NPCs.push_back(name); 
	}
}



void Table::dealCardtoPlayers() {
	for (Player& player : players) {
		player.cardToHandMulti(deck, 1);
	}
}

void Table::dealFlop() {
	cardToHandMulti(deck, 3); 
}

void Table::showPlayersHand() {
	for (Player& player : players) {
		cout << player.getPlayerUsername() << endl;
		player.showCards();
	}
}

void Table::showNPCsHand() {
	for (Player& player : NPCs) {
		cout << player.getPlayerUsername() << endl;
		player.showCards();
	}
}