#pragma once
#include "gameObject.h"
#include "Hand.h"

class Player {
public:
    Player(string);
    int getID();
    string getPlayerUsername();
    int getPlayerRank();
    void cardToHand(Deck&, int); 
    float getPlayertWinrate();
    vector<Card> getPlayerfavoriteHand();
    vector<Card> getPlayerHand();

private:
    int id;
    string username;
    double winrate;
    int rank;
    vector<Card> favoriteHand;
    Hand hand;
    static int currentId;
};
    
