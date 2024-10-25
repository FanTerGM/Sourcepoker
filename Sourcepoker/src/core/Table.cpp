#include "../../headers/config/gameObject.h"


Table::Table() : numberOfPlayer(1), numberOfNPC(1) { populateTable(); }
Table::Table(int numberOfPlayer, int numberOfNPC) : numberOfPlayer(numberOfPlayer), numberOfNPC(numberOfNPC) {}


void Table::populateTable() {
	for (int i = 0; i < numberOfPlayer - numberOfNPC; i++) {
		string input;
		cout << "Enter Player " << i+1 << "'s name: ";  cin >> input;
		Player player(input);
		players.push_back(player);
	}

	for (int i = 0; i < numberOfNPC; i++) {
		string name = "AI_" + to_string(i);
		Player AI(name);
		players.push_back(name); 
	}
}

void Table::dealCardtoPlayers() {
	for (Player& player : players) {
		player.cardToHand(deck, 5, true);
	}
}

void Table::dealFlop() {
	cardToHand(deck, 3, true); 
}

void Table::showPlayersHand() {
	for (Player& player : players) {
		cout << player.getPlayerUsername() << endl;
		player.showCards();
	}
}

void Table::raiseBet() {
	cout << "unavalable" << endl;
}

void Table::checkWinner() {
	cout << "unavalable" << endl;
}

void Table::StartGame() {
	cout << "unavalable" << endl;
}