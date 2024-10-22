#pragma once
#include "gameObject.h"
#include "CommunityCard.h"


class Table {
public:
    enum gameMode { TEXAS, DRAW, STUD, SUPER };
    Table(gameMode g, int countPlayer, int countNPC);  
    int pot;
    int BBID;
    int SBID;
    void populateTable();
    void dealCardtoPlayers();
private:
    int countPlayer;
    int countNPC;
    Deck deck;
    gameMode mode; 
    communityCard com;
    vector<Player> players;

};