#pragma once
#include <gameObject.h>

class Evaluator{
private:
	map<Card::Suit, int> suitMap;
	map<Card::Rank, int> rankMap;
	vector<Card> hand;
public:
	Evaluator(vector<Card> hand);
	bool FourOfAKind() const;
	bool ThreeOfAKind() const;
	bool Pair() const;
	bool FullHouse() const;
	bool Flush() const;
	bool StraightFlush() const;
	bool Straight() const;
	bool RoyalFlush() const;

	int getHandStrength();
};

