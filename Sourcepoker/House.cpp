#include "gameObject.h"
#include "House.h"

House::House(Table* table) : currentTable(table) {}

void House::setTable(Table* table) {
	delete currentTable;
	currentTable = table;
}

void House::raiseBet() { currentTable->raiseBet(); }
void House::populateTable() { currentTable->populateTable(); }
void House::showPlayersHand() { currentTable->showPlayersHand(); }
void House::showNPCsHand() { currentTable->showNPCsHand(); }
void House::showCards() { currentTable -> showCards(); }

void House::dealFlop() { currentTable->dealFlop(); }
void House::StartGame() { currentTable->StartGame(); }
void House::checkWinner() { currentTable->checkWinner(); }
void House::dealCardtoPlayers() { currentTable->dealCardtoPlayers(); }

House::~House() {
	delete currentTable; 
}