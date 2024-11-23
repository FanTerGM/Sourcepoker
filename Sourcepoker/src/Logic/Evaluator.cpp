#include <gameObject.h>

Evaluator::Evaluator(){}

Evaluator::Evaluator(std::vector<Card> hand) : hand(hand) {
    sort(hand.begin(), hand.end(), [](Card& left, Card& right) {return left.getRank() > right.getRank(); });
    for (const Card& card : hand) {
        suitMap[card.getSuitEnum()]++;
        rankMap[card.getRankEnum()]++;
    }
}

std::string Evaluator::IntToEnumName(int rank) {
    switch (rank) {
    case 0: return "HIGH";
    case 1: return "ONE_PAIR";
    case 2: return "TWO_PAIR";
    case 3: return "THREE_OF_A_KIND";
    case 4: return "STRAIGHT";
    case 5: return "FLUSH";
    case 6: return "FULL_HOUSE";
    case 7: return "FOUR_OF_A_KIND";
    case 8: return "STRAIGHT_FLUSH";
    case 9: return "ROYAL_STRAIGHT_FLUSH";
    default:
        return "UNKNOWN HAND"; 
    }
}

bool Evaluator::FourOfAKind() const {
    return any_of(rankMap.begin(), rankMap.end(), [](const auto& p) {return p.second == 4; });
}

bool Evaluator::ThreeOfAKind() const {
    return any_of(rankMap.begin(), rankMap.end(), [](const auto& p) {return p.second == 3; });
}

bool Evaluator::Pair() const {
    return any_of(rankMap.begin(), rankMap.end(), [](const auto& p) {return p.second == 2; });
}

bool Evaluator::FullHouse() const {
    return Pair() && ThreeOfAKind();
}

bool Evaluator::Flush() const {
    return any_of(suitMap.begin(), suitMap.end(), [](const auto& p) {return p.second == 5; });
}

bool Evaluator::StraightFlush() const {
    return Flush() && Straight();
}

bool Evaluator::Straight() const {
    for (int i = 0; i < hand.size() - 1; ++i) {
        if (hand[i].getRankEnum() + 1 != hand[i + 1].getRankEnum()) 
            return false;
    }
    return true;
}

bool Evaluator::TwoPairs() const {
    return count_if(rankMap.begin(), rankMap.end(), [](const auto& p) {return p.second == 2; }) == 2 ;
}


bool Evaluator::RoyalFlush() const {
    return StraightFlush() && 
        hand[0].getRankEnum() == Card::Rank::TEN && hand[hand.size() - 1].getRankEnum() == Card::Rank::ACE;
}

bool Evaluator::operator > (const Evaluator& other) const {
    int a = strengthRank(), b = other.strengthRank();
    if (a != b) return a > b;
    return strengthHand() > other.strengthHand();
}

// Evaluate the strength string of a 5-card hand
std::string Evaluator::evaluateHandStrength() const {
    switch (evaluateHandRank()) {
    case ONE_PAIR:
    case TWO_PAIR:
    case THREE_OF_A_KIND:
    case FOUR_OF_A_KIND:
        int handId = 0; 
        for (const Card& card : hand) {
            handId = handId * 100 + card.getRankEnum();
        }
        return handId;
    case HIGH:
    case STRAIGHT:
    case FLUSH:
    case FULL_HOUSE:
        return formatFullHouse();
    case STRAIGHT:
    case STRAIGHT_FLUSH:
    case ROYAL_STRAIGHT_FLUSH:
        return hand[0].getRankEnum();
    default:
        return hand[0].getRankEnum();
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
