#pragma once
#include "gameObject.h"



class Table: public Hand{
public:

    enum gameMode { TEXAS, DRAW, STUD, SUPER };
    
    
    Table();
    
    Table(gameMode g, int numberOfPlayer, int numberOfNPC);

    int pot;
    int call;

 
    void populateTable();
    void dealCardtoPlayers();
    void showPlayersHand();
    void showNPCsHand();


    void raiseBet();
    void dealFlop();

private:
    int numberOfPlayer;
    int numberOfNPC;

    gameMode mode;
    Deck deck;
    vector<Player> players;
    vector<Player> NPCs;

};