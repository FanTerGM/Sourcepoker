#pragma once
#include "../../headers/config/gameObject.h"

class Player : public Hand{
public:
    Player();
    Player(string);
    
    int money;
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
    
