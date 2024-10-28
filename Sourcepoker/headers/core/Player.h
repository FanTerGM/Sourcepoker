#pragma once
#include "Hand.h"
#include <nlohmann/json.hpp>

struct gameRecord {
    gameRecord();
    gameRecord(string gameMode, int earning, vector<Card> hand);
    string gameMode;
    int earning = 0;
    vector<Card> hand;
};

class Player : public Hand{
public:

    //Default player placeholder
    Player();

    // Create new player with gameWon, gamePlayed, winrate and favorite hand as 0, money as 1000 
    Player(string);

    // Create player with already avalable profile.
    Player(string name, double win, vector<gameRecord> gameHistory, double winrate, int money, int rank, vector<Card> favoriteHand);
    
    // get player's username
    string getPlayerUsername() const;
    
    // get player's ranking
    int getPlayerRank() const;

    // get player's favorite hand
    vector<Card> getPlayerfavoriteHand() const;

    // get winrate
    double getPlayertWinrate() const;

    // Update gameHistory (Win or lose) amd win rate
    void updateGameHistoryAndWinrate(bool won, const vector<Card>& hand, string gameMode, int earning);
    
    //Update ranking
    void updateRanking(int rank);

    // Save player profile as json file
    void recordPlayer(const string& directory = "Resources/playerInfo/") const;

    // Load player's json file if exist, if not create a new one.
    Player loadPlayer(const string& username, const string& directory = "Resources/playerInfo/");

    /* Friend of fuctions to get private atribute of player's profile*/
    friend void to_json(nlohmann::json& j, const Player& p);

    friend void from_json(const nlohmann::json& j, Player& p);

private:
    string username;
    int money = 1000;
    double gameWon = 0;
    vector<gameRecord> gameHistory;
    double winrate = 0; 
    int rank = 0;
    vector<Card> favoriteHand;
};



/* Fuctions to get player profile*/
void to_json(nlohmann::json& j, const gameRecord& g);
/* Fuctions to get player profile*/
void from_json(const nlohmann::json& j, gameRecord& g);
/* Fuctions to get player profile*/
void to_json(nlohmann::json& j, const Player& p);
/* Fuctions to get player profile*/
void from_json(const nlohmann::json& j, Player& p);
