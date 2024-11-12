#include <gameObject.h>
#include <gameModes.h>

drawTable::drawTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers,numberOfNPCs) {}

void drawTable::dealCardtoPlayers() {
	for (Player& player: players) {
		player.cardToHand(deck, 5, true);
	}
}

string drawTable::getModeName(){
	return "draw";
}

void drawTable::StartGame(){
	do {
		createDeck();
		clearTable();
		dealCardtoPlayers();
		// Display the player's hand and the community card.
		cout << "Player hand:" << endl;
		for (Player& player : players) {
			cout << player.getPlayerUsername() << endl;
			player.showCards();
			if (player.getPlayerUsername().find("AI_") != string::npos) continue;
			cout << "Choose cards to replace: " << endl;
			player.replaceCard(deck);
			cout << "After replacement: " << endl;
			player.showCards();
		}
		checkWinner();
		cout << "Another round? (Press 1 to continue)" << endl;
		cin.clear();
		cin.ignore(1000, '\n');

	} while (cin.get() == '1');
}

