#pragma once
#include "gameObject.h"
#include "Hand.h"

class Player : public Hand{
public:
    Player();
    Player(string);

    int getID();
    string getPlayerUsername();
    int getPlayerRank();
    double getPlayertWinrate();
    vector<Card> getPlayerfavoriteHand();
    
private:
    int id;
    string username;
    double winrate;
    int rank;
    vector<Card> favoriteHand;
    static int currentId;
};
    
