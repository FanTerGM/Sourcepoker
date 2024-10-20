#pragma once
#include "gameObject.h"
#include "Player.h"

class Table {
public:
    Table();
    int playerCount;
    int gameMode;
    int BBID;
    int SBID;
    vector<Player> createTable();
};