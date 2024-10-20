#include "gameObject.h"
#include "Player.h"



int Player::getID() { return id;}

string Player::getPlayerUsername(){ return username; }
int Player::getPlayerRank() { return rank; }

vector<Card> Player::getPlayerHand() { return hand.getHand(); }