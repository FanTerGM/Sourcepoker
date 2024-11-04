#pragma once
#include "Hand.h"

class Table: public Hand{

protected:
    int numberOfPlayer;
    int numberOfNPC;

    Deck deck;
    vector<Player> players;

public:
    
    Table();
    Table(int numberOfPlayer, int numberOfNPC);

    int pot;
    int call;

    void raiseBet();
    void populateTable();
    void showPlayersHand();
    void createDeck();

    virtual string getModeName();
    virtual void dealFlop();
    virtual void StartGame();
    virtual void checkWinner();
    void clearTable();
    virtual void dealCardtoPlayers();
    virtual ~Table() {}
};