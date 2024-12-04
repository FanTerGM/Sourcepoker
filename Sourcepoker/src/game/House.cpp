#include <gameObject.h>
#include "../../headers/game/House.h"

House::House(Table* table) : currentTable(table) {}

void House::setTable(Table* table) {
	delete currentTable;
	currentTable = table;
}

void House::processPlayerAction(int& highestBet, int currentPlayerIndex, int& raiseIndex) { currentTable->processPlayerAction(highestBet, currentPlayerIndex, raiseIndex); }
void House::populateTable() { currentTable->populateTable(); }
void House::showPlayersHand() { currentTable->showPlayersHands(); }
void House::showCards() { currentTable -> showCards(); }
void House::createDeck() { currentTable->createDeck(); }
void House::clearTable() { currentTable->clearTable();}

void House::dealFlop() { currentTable->dealFlop(); }
void House::StartGame() { currentTable->startGame(); }
void House::checkWinner() { currentTable->determineWinner(); }
void House::dealCardtoPlayers() { currentTable->dealCardsToPlayers(); }

House::~House() {
	delete currentTable; 
}