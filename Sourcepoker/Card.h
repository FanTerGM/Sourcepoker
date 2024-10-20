#pragma once
#include <iostream> 
#include <string>
#include <stack>
#include <vector>

using namespace std;


class Card {
public:
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

    Card(Suit s, Rank r);

    Suit getSuit() const;
    Rank getRank() const;

private:
    Suit suit;
    Rank rank;
};

class Hand {
public:
    Card hand[5];
    void organize();            
};

class Player {
private:
    int id;
    string userNam;
    enum Blind {S, B, D, None};
    float winrate;
    int rank;
    string favoriteHand;
};

class Deck {
public:
    Deck();
    void shuffle();
    void deal();
};

class Table {
public:
    int playerCount;
    int gameMode;
    int BBID;
    int SBID;

};

vector<Player> createTable();