#pragma once
#include "gameObject.h"
#include "Hand.h"

class Player {
public:
    static int currentId;
    Player();
    int getID();
    string getPlayerUsername();
    int getPlayerRank();
    float getPlayertWinrate();
    string getPlayerfavoriteHand();
    vector<Card> getPlayerHand();

private:
    int id;
    string username;
    float winrate;
    int rank;
    string favoriteHand;
    Hand hand;
};
