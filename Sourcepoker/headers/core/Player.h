#pragma once
#include "Hand.h"

class Player : public Hand{
public:
    Player(string);
    Player(string name, double win, double played, double winrate, int favoriteHand);
    
    // call player's information
    string getPlayerUsername() const;
    int getPlayerRank() const;
    int getPlayerfavoriteHand() const;
    void updateGameHistoryAndWinrate(bool won);
    double getPlayertWinrate();
    
    void recordPlayer(const string& directory = "Resources/playerInfo/") const;
    Player loadPlayer(const string& username, const string& directory = "Resources/playerInfo/");

private:
    string username;
    double gameWon = 0;
    double gamePlayed = 0;
    double winrate = 0; 
    int rank;
    int favoriteHand = 0;
    
};
    
