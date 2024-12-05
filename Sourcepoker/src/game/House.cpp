#include <gameObject.h>
#include "../../headers/game/House.h"

House::House(Table* table) : currentTable(table) {}

void House::setTable(Table* table) {
	delete currentTable;
	currentTable = table;
}

void House::populateTable() { currentTable->populateTable(); }
void House::showPlayersHand() { currentTable->showPlayersHands(); }
void House::showCards(sf::RenderWindow& window) { currentTable -> showCards(window); }
void House::createDeck() { currentTable->createDeck(); }
void House::clearTable() { currentTable->clearTable();}

void House::dealFlop() { currentTable->dealFlop(); }
void House::StartGame() { currentTable->startGame(); }
void House::determineWinner() { currentTable->determineWinner(); }
void House::dealCardtoPlayers() { currentTable->dealCardsToPlayers(); }

std::string House::getModeName() { return currentTable->getModeName();}

House::~House() {
	delete currentTable; 
}