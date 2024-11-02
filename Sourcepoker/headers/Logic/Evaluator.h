#pragma once
#include <gameObject.h>

class Evaluator{
private:
	map<Card::Suit, int> suitMap;
	map<Card::Rank, int> rankMap;
	vector<Card> hand;
public:
	enum HandType { HIGH, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_STRAIGHT_FLUSH };

	Evaluator(vector<Card> hand);

	bool FourOfAKind() const;
	bool ThreeOfAKind() const;
	bool Pair() const;
	bool FullHouse() const;
	bool Flush() const;
	bool StraightFlush() const;
	bool Straight() const;
	bool TwoPairs() const;
	bool RoyalFlush() const;

	int strengthRank() const;

	int strengthHand() const;

	bool operator<(const Evaluator& other);

};

