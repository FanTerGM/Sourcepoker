#include "gameObject.h"

Table::Table(gameMode g, int countPlayer, int countNPC) : mode(g), countPlayer(countPlayer), countNPC(countNPC){}

void Table::populateTable() {
	for (int i = 0; i < countPlayer; i++) {
		Player player();
	}
}