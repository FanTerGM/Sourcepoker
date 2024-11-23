#include <gameObject.h>
#include <algorithm>
#include <string>
#include <vector>

// Constructor Implementations
Evaluator::Evaluator() {}

Evaluator::Evaluator(std::vector<Card> hand) : hand(hand) {
    if (hand.size() > 5) {
        hand = calculateBestHand();
    }
    std::sort(hand.begin(), hand.end(), [](const Card& first, const Card& second) { return first.getRankEnum() > second.getRankEnum(); });
    populateMaps(hand);
}

// Populate maps for rank and suit counts
void Evaluator::populateMaps(const std::vector<Card>& cards) {
    suitMap.clear();
    rankMap.clear();
    for (const Card& card : cards) {
        suitMap[card.getSuitEnum()]++;
        rankMap[card.getRankEnum()]++;
    }
}

// Generate all 5-card combinations from a 7-card hand
std::vector<std::vector<Card>> Evaluator::generateCombinations() const {
    std::vector<std::vector<Card>> combinations;
    std::vector<int> indices(hand.size(), 0);
    std::fill(indices.begin(), indices.begin() + 5, 1); // First 5 indices set to 1

    do {
        std::vector<Card> combo;
        for (size_t i = 0; i < hand.size(); ++i) {
            if (indices[i] == 1) {
                combo.push_back(hand[i]);
            }
        }
        combinations.push_back(combo);
    } while (std::prev_permutation(indices.begin(), indices.end()));

    return combinations;
}

// Determine if a hand is a straight
bool Evaluator::isStraight() const {
    if (isAceLowStraight()) return true;
    for (size_t i = 0; i < hand.size() - 1; ++i) {
        if (hand[i].getRankEnum() + 1 != hand[i + 1].getRankEnum()) return false;
    }
    return true;
}

// Check for Ace-Low Straight
bool Evaluator::isAceLowStraight() const {
    return hand[0].getRankEnum() == 2 && hand[4].getRankEnum() == 14;
}

// Evaluate the rank of a 5-card hand
int Evaluator::evaluateHandRank() const {
    if (std::any_of(rankMap.begin(), rankMap.end(), [](const auto& pair) { return pair.second == 4; })) return FOUR_OF_A_KIND;
    if (std::any_of(rankMap.begin(), rankMap.end(), [](const auto& pair) { return pair.second == 3; }) &&
        std::any_of(rankMap.begin(), rankMap.end(), [](const auto& pair) { return pair.second == 2; }))
        return FULL_HOUSE;
    if (std::any_of(suitMap.begin(), suitMap.end(), [](const auto& pair) { return pair.second == 5; })) {
        if (isStraight()) return hand[0].getRankEnum() == Card::Rank::TEN ? ROYAL_FLUSH : STRAIGHT_FLUSH;
        return FLUSH;
    }
    if (isStraight()) return STRAIGHT;
    if (std::any_of(rankMap.begin(), rankMap.end(), [](const auto& pair) { return pair.second == 3; })) return THREE_OF_A_KIND;
    if (std::count_if(rankMap.begin(), rankMap.end(), [](const auto& pair) { return pair.second == 2; }) == 2) return TWO_PAIR;
    if (std::any_of(rankMap.begin(), rankMap.end(), [](const auto& pair) { return pair.second == 2; })) return ONE_PAIR;
    return HIGH;
}

// Evaluate the strength string of a 5-card hand
std::string Evaluator::evaluateHandStrength() const {
    switch (evaluateHandRank()) {
    case ONE_PAIR:
    case TWO_PAIR:
    case THREE_OF_A_KIND:
    case FOUR_OF_A_KIND:
        return formatMult();
    case HIGH:
    case FLUSH:
        return formatHigh();
    case FULL_HOUSE:
        return formatFullHouse();
    case STRAIGHT:
    case STRAIGHT_FLUSH:
        return hand[0].getRankEnum() == 1 && hand[4].getRankEnum() ? "f" : std::string(1, 'a' + hand[0].getRankEnum());
    case ROYAL_FLUSH:
        return "a";
    default:
        return "a";
    }
}

std::string Evaluator::formatMult() const {
    std::string multiples, others;
    for (const auto& [rank, count] : rankMap) {
        if (count >= 2) multiples += ('a' + rank);
        else others += ('a' + rank);
    }
    return multiples + "-" + others;
}

std::string Evaluator::formatHigh() const {
    std::string result;
    for (const Card& card : hand) {
        result += ('a' + card.getRankEnum());
    }
    return result;
}

std::string Evaluator::formatFullHouse() const {
    std::string threeRank, pairRank;
    for (const auto& [rank, count] : rankMap) {
        if (count == 3) threeRank += ('a' + rank);
        else if (count == 2) pairRank += ('a' + rank);
    }
    return threeRank + pairRank;
}

// Evaluate the best hand rank from all combinations
std::vector<Card> Evaluator::calculateBestHand() const {
    auto combinations = generateCombinations();
    std::vector<Card> bestHand = combinations[0];
    for (const std::vector<Card>& combo : combinations) {
        bestHand = std::max(bestHand, combo, [](const auto& a, const auto& b) {
            return Evaluator(a) < Evaluator(b);
            });;
    }
    return bestHand;
}

// Comparison Operators
bool Evaluator::operator>(const Evaluator& other) const {
    int thisRank = evaluateHandRank();
    int otherRank = other.evaluateHandRank();
    if (thisRank != otherRank) return thisRank > otherRank;
    return evaluateHandStrength() > other.evaluateHandStrength();
}

bool Evaluator::operator==(const Evaluator& other) const {
    return evaluateHandRank() == other.evaluateHandRank() &&
        evaluateHandStrength() == other.evaluateHandStrength();
}

bool Evaluator::operator<(const Evaluator& other) const {
    int thisRank = evaluateHandRank();
    int otherRank = other.evaluateHandRank();
    if (thisRank != otherRank) return thisRank < otherRank;
    return evaluateHandStrength() < other.evaluateHandStrength();
}

// Rank to String Helper
std::string Evaluator::rankToString(int rank) const {
    switch (rank) {
    case HIGH: return "HIGH";
    case ONE_PAIR: return "ONE_PAIR";
    case TWO_PAIR: return "TWO_PAIR";
    case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
    case STRAIGHT: return "STRAIGHT";
    case FLUSH: return "FLUSH";
    case FULL_HOUSE: return "FULL_HOUSE";
    case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
    case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
    case ROYAL_FLUSH: return "ROYAL_FLUSH";
    default: return "UNKNOWN";
    }
}