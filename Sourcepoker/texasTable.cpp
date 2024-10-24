#include "gameObject.h"
#include "texasTable.h"

texasTable::texasTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers, numberOfNPCs) {}

void texasTable::dealFlop() { cardToHand(deck, 3, true);}
