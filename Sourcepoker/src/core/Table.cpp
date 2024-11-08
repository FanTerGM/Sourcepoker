#include <gameObject.h>


Table::Table() : numberOfPlayer(1), numberOfNPC(1) { populateTable(); }
Table::Table(int numberOfPlayer, int numberOfNPC) : numberOfPlayer(numberOfPlayer), numberOfNPC(numberOfNPC) {}


void Table::populateTable() {
	for (int i = 0; i < numberOfPlayer; i++) {
		string input;
		cout << "Enter Player " << i+1 << "'s name: ";  cin >> input;
		Player player = player.loadPlayer(input);
		players.push_back(player);
	}

	for (int i = 0; i < numberOfNPC; i++) {
		string name = "AI_" + to_string(i);
		Player AI(name);
		players.push_back(AI); 
	}
}

void Table::dealCardtoPlayers() {
	for (Player& player : players) {
		player.cardToHand(deck, 5, true);
	}
}

string Table::getModeName(){
	return "Default5";
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

void Table::createDeck(){
	deck = Deck();
}

int Table::printTie() {
	int i = 0;
	while (players[0] == players[++i]) {
		players[i].updateGameHistoryAndWinrate(true, 1);
		cout << players[i].getPlayerUsername() << endl;
	}
	return i;
}

void Table::checkWinner() {
	sort(players.begin(), players.end(), greater<Player>()); 
	int i = (players.size() != 1)? printTie() : 0;
	for (i; i < players.size(); i++) 
		players[i].updateGameHistoryAndWinrate(false, 1);
	cout << "Winner:" << endl; 
	cout << players[0].getPlayerUsername() << endl;
	players[0].updateGameHistoryAndWinrate(true, 1);
	cout << Evaluator(players[0].getHand()).strengthRank() << endl;
}

void Table::clearTable() {
	for (Player& player : players) {
		player.clearHand();
	}
}

void Table::StartGame() {
	cout << "unavalable" << endl;
}

void Table::raiseBet() {
	cout << "unavalable" << endl;
}