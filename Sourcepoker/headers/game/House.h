#pragma once
#include <gameObject.h>

class Table;

class House {
public:
	House(Table* table);

    void setTable(Table* table);

    void processPlayerAction(int& highestBet, int currentPlayerIndex, int& raiseIndex);
    void populateTable();
    void showPlayersHand();
    void showCards();

    void createDeck();
    void clearTable();
    void dealFlop();
    void StartGame();
    void checkWinner();
    void dealCardtoPlayers();
    
    ~House();
private:
    Table* currentTable;
};