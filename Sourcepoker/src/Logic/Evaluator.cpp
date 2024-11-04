#include <gameObject.h>

Evaluator::Evaluator(vector<Card> hand) : hand(hand) {
    sort(hand.begin(), hand.end(), [](Card& left, Card& right) {return left.getRank() > right.getRank(); });
    for (const Card& card : hand) {
        suitMap[card.getSuitEnum()]++;
        rankMap[card.getRankEnum()]++;
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

bool Evaluator:: operator == (const Evaluator& other) const {
   return strengthRank() == other.strengthRank() && strengthHand() == other.strengthHand();
}

int Evaluator::strengthRank() const {
    if (RoyalFlush()) return ROYAL_STRAIGHT_FLUSH;
    if (StraightFlush()) return STRAIGHT_FLUSH;
    if (FourOfAKind()) return FOUR_OF_A_KIND;
    if (FullHouse()) return FULL_HOUSE;
    if (Flush()) return FLUSH;
    if (Straight()) return STRAIGHT;
    if (ThreeOfAKind()) return THREE_OF_A_KIND;
    if (TwoPairs()) return TWO_PAIR;
    if (Pair()) return ONE_PAIR;
    return HIGH;
}

int Evaluator::getCardHighAndFlush() const {
    int res = 0;
    for (const Card& card : hand) {
        res = res * 100 + card.getRankEnum();  // Shift left and add next rank
    }
    return res;
}

bool Evaluator::isAceLowStraight() const {
    return hand[0].getRankEnum() == 14 && hand[4].getRankEnum() == 5;
}

int Evaluator::getCardStraight() const {
    if (isAceLowStraight()) {
        return 500;  // Arbitrary low value for Ace-low straight
    }
    return hand[0].getRankEnum();  // High card of the straight
}

int Evaluator::getCardFullHouse() const {
    int threeRank = 0, pairRank = 0;
    for (const auto& [key, value] : rankMap) {
        if (value == 3) threeRank = key;
        else if (value == 2) pairRank = key;
    }
    return threeRank * 100 + pairRank;
}

int Evaluator::getCardMult() const {
    int isMult = 0, other = 0;
    for (const auto& [key, value] : rankMap) {
        if (value >= 2) isMult = isMult * 100 + key;  // For pairs, trips, quads
        else other = other * 100 + key;  // Remaining single cards
    }
    return isMult * 10000 + other;  // Combine multiplets with other cards
}

int Evaluator::strengthHand() const {
    switch (strengthRank()) {
    case ONE_PAIR:
    case TWO_PAIR:
    case THREE_OF_A_KIND:
    case FOUR_OF_A_KIND:
        return getCardMult();
    case HIGH:
    case FLUSH:
        return getCardHighAndFlush();
    case FULL_HOUSE:
        return getCardFullHouse();
    case STRAIGHT:
    case STRAIGHT_FLUSH:
        return getCardStraight();
    case ROYAL_STRAIGHT_FLUSH:
        return 1000000;  // Highest possible hand with a unique high value
    default:
        return 0;  // Fallback for unexpected cases
    }
}

bool Evaluator::operator<(const Evaluator& other) const{
    int a = strengthRank(), b = other.strengthRank();
    if (a != b) return a < b;
    return strengthHand() < other.strengthHand();
}
