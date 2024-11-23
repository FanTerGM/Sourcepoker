#pragma once
#include <gameObject.h> 

struct Descend{
	bool operator()(const Card::Rank& a, const Card::Rank& b) const {
		return a > b;
	}
};

class Evaluator{
private:
	std::map<Card::Suit, int> suitMap;
	std::map<Card::Rank, int, Descend> rankMap;
	std::vector<Card> hand;
public:
	enum HandType { HIGH = 0, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_STRAIGHT_FLUSH };

	Evaluator();
	Evaluator(std::vector<Card> hand);

	std::string IntToEnumName(int rank);

	bool FourOfAKind() const;
	bool ThreeOfAKind() const;
	bool Pair() const;
	bool FullHouse() const;
	bool Flush() const;
	bool StraightFlush() const;
	bool Straight() const;
	bool TwoPairs() const;
	bool RoyalFlush() const;

	bool operator>(const Evaluator& other) const;

	int strengthRank() const;

	std::string getCardHighAndFlush() const;

	bool isAceLowStraight() const;

	std::string getCardStraight() const;

	std::string getCardFullHouse() const;

	std::string getCardMult() const;

	std::string strengthHand() const;

	bool operator<(const Evaluator& other) const;

	bool operator==(const Evaluator& other) const;

};

