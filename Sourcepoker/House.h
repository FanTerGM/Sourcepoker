#pragma once
#include "gameObject.h"

class Table;

class House {
public:
	House(Table* table);

    void setTable(Table* table);

    void raiseBet();
    void populateTable();
    void showPlayersHand();
    void showNPCsHand();
    void showCards();

    void dealFlop();
    void StartGame();
    void checkWinner();
    void dealCardtoPlayers();
    
    ~House();
private:
    Table* currentTable;
};