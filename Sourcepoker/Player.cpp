#include "gameObject.h"
#include "Player.h"

int Player::currentId = 0; 

Player::Player(string name) : id(currentId++), username(name), rank(0),  winrate(-1){}

void Player::cardToHand(Deck& deck, int count) {
	for (int i = 0; i < count; i++) {
		const Card& dealtCard = deck.deal();
		hand.addCard(dealtCard);
	}
}

int Player::getPlayerRank() { return rank; }
int Player::getID() { return id;}

float Player::getPlayertWinrate() { return winrate; }

string Player::getPlayerUsername(){ return username; }


vector<Card> Player::getPlayerfavoriteHand() { return favoriteHand; }
vector<Card> Player::getPlayerHand() { return hand.getHand(); }