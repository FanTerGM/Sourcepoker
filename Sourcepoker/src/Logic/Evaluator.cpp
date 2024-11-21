#include <gameObject.h>

Evaluator::Evaluator(vector<Card> hand) : hand(hand) {
    sort(hand.begin(), hand.end());
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
    if (hand[0].getRankEnum() == Card::Rank::TWO &&
        hand[1].getRankEnum() == Card::Rank::THREE &&
        hand[2].getRankEnum() == Card::Rank::FOUR &&
        hand[3].getRankEnum() == Card::Rank::FIVE &&
        hand[4].getRankEnum() == Card::Rank::ACE)
        return true;

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

bool Evaluator::operator < (const Evaluator& other) {
    int a = strengthRank(), b = other.strengthRank();
    if (a != b) return a < b;
    return strengthHand() < other.strengthHand();
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

int Evaluator::strengthHand() const {
    switch (strengthRank()) {
    case ONE_PAIR:
    case TWO_PAIR:
    case THREE_OF_A_KIND:
    case FOUR_OF_A_KIND:
    case FULL_HOUSE:

    case HIGH:
    case FLUSH:

    case STRAIGHT:
    case STRAIGHT_FLUSH:

    case ROYAL_STRAIGHT_FLUSH:
        return 1;
    }
}
