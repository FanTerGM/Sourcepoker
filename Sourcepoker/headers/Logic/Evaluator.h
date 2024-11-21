#pragma once
#include <gameObject.h> 

struct Descend{
	bool operator()(const int& a, const int& b) const {
		return a > b;
	}
};

// Constructor Implementations
class Evaluator {
public:
    // Constructors
    Evaluator();
    explicit Evaluator(std::vector<Card> hand);

    // Hand Evaluation Methods
    std::vector<Card> calculateBestHand() const;

    // Give the hand name
    std::string rankToString(int rank) const;

    int evaluateHandRank() const;

    // Comparison Operators
    bool operator>(const Evaluator& other) const;
    bool operator==(const Evaluator& other) const;
    bool operator<(const Evaluator& other) const;

private:
    // Helper Methods
    void populateMaps(const std::vector<Card>& cards);
    bool isStraight() const;
    bool isAceLowStraight() const;
    std::string formatMult() const;
    std::string formatHigh() const;
    std::string formatFullHouse() const;
    
    std::string evaluateHandStrength() const;
    std::vector<std::vector<Card>> generateCombinations() const;

    // Data Members
    std::vector<Card> hand;
    std::unordered_map<int, int> suitMap;
    std::map<int, int, Descend> rankMap;

    // Constants for Hand Ranks
    enum HandRank {
        HIGH = 0,
        ONE_PAIR,
        TWO_PAIR,
        THREE_OF_A_KIND,
        STRAIGHT,
        FLUSH,
        FULL_HOUSE,
        FOUR_OF_A_KIND,
        STRAIGHT_FLUSH,
        ROYAL_FLUSH
    };
};
