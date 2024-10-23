#pragma once
#include "gameObject.h"



class Table: public Hand{
public:

    
    
    Table();
    
    Table(int numberOfPlayer, int numberOfNPC);

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

    Deck deck;
    vector<Player> players;
    vector<Player> NPCs;

};