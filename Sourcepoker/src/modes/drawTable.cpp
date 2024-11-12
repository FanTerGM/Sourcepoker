#include <gameObject.h>
#include <gameModes.h>

drawTable::drawTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers,numberOfNPCs) {}

void drawTable::draw(int playerSeat){
	players[playerSeat].showCards();
	cout << "Choose Card to replace: ";
	replaceCard(cin.get(), deck);
}

void drawTable::dealCardtoPlayers() {
	for (Player& player: players) {
		cardToHand(deck, 5, true);
	}
}

string drawTable::getModeName(){
	return "draw";
}

