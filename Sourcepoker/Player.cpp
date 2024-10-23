#include "gameObject.h"
#include "Player.h"

int Player::currentId = 0; 

Player::Player() : id(-1), username("Admin"), rank(0), winrate(-1){}

Player::Player(string name) : id(currentId++), username(name), rank(0),  winrate(-1){}


int Player::getPlayerRank() { return rank; }
int Player::getID() { return id;}

double Player::getPlayertWinrate() { return winrate; }

string Player::getPlayerUsername(){ return username; }


vector<Card> Player::getPlayerfavoriteHand() { return favoriteHand; }
