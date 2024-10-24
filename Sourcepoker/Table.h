#pragma once
#include "gameObject.h"



class Table: public Hand{

protected:
    int numberOfPlayer;
    int numberOfNPC;

    Deck deck;
    vector<Player> players;
    vector<Player> NPCs;

public:
    
    Table();
    Table(int numberOfPlayer, int numberOfNPC);

    int pot;
    int call;

    void raiseBet();
    void populateTable();
    void showPlayersHand();
    void showNPCsHand();

    virtual void dealFlop();
    virtual void StartGame();
    virtual void checkWinner();
    virtual void dealCardtoPlayers();
    virtual ~Table() {}
};