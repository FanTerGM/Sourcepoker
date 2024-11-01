#include <gameObject.h>
#include "Evaluator.h"

Evaluator::Evaluator(vector<Card> hand): hand(hand){
    for (const Card& card : hand) {
        suitMap[card.getSuitEnum()]++;
        rankMap[card.getRankEnum()]++;
    }
}

bool Evaluator::FourOfAKind() const {
    return any_of(rankMap.begin(), rankMap.end(), [](auto& p) {return p.second == 4; });
}

bool Evaluator::ThreeOfAKind() const {
    return any_of(rankMap.begin(), rankMap.end(), [](auto& p) {return p.second == 3; });
}

bool Evaluator::Pair() const {
    return any_of(rankMap.begin(), rankMap.end(), [](auto& p) {return p.second == 2; });
}

bool Evaluator::FullHouse() const {
    return Pair() && ThreeOfAKind();
}

bool Evaluator::Flush() const {
    return any_of(suitMap.begin(), suitMap.end(), [](auto& p) {return p.second == 5; });
}

bool Evaluator::StraightFlush() const {
    return Flush() && Straight();
}

bool Evaluator::Straight() const {
    for (int i = 0; i < hand.size() - 1; ++i) {
        if (static_cast<int>(hand[i].getRankEnum()) + 1 != static_cast<int>(hand[i + 1].getRankEnum()))
            return false;
    }
    return true;
}

bool Evaluator::TwoPairs() const {
    int numTwo = 0;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 2) numTwo++;
    return numTwo == 4;
}


bool Evaluator::RoyalFlush() const {
    return StraightFlush() && 
        hand[0].getRankEnum() == Card::Rank::TEN && hand[hand.size() - 1].getRankEnum() == Card::Rank::ACE;
}


int Evaluator::strengthRank() const {
    if (RoyalFlush()) return 10;
    if (StraightFlush()) return 9;
    if (FourOfAKind()) return 8;
    if (FullHouse()) return 7;
    if (Flush()) return 6;
    if (Straight()) return 5;
    if (ThreeOfAKind()) return 4;
    if (TwoPairs()) return 3;
    if (Pair()) return 2;
    return 1;
}

string Evaluator::getStrategy() {
    return strategy[strengthRank() - 1];
}

string Evaluator::getCardFlush() const {
    Hand temp = *this;
    sort(temp.cards.begin(), temp.cards.end());
    string res = {};
    for (int i = 4; i >= 0; i--)
        res = res + (char)('a' + temp.cards[i].getRank());

    return res;
}

string Evaluator::getCardStraight() const {
    Hand temp = *this;
    sort(temp.cards.begin(), temp.cards.end());
    if (temp.cards[0].getRank() == 0 && temp.cards[4].getRank() == 12) {
        return "d";
    }
    char c = ('a' + temp.cards[4].getRank());
    string res = {};
    res = res + c;
    return res;
}

string Evaluator::getCardFullHouse() const {
    string res = {};
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    char isThree, isTwo;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 3) isThree = (char)('a' + cards[i].getRank());
        else isTwo = (char)('a' + cards[i].getRank());
    for (int i = 0; i < 3; i++)
        res = res + isThree;
    for (int i = 0; i < 2; i++)
        res = res + isTwo;
    return res;
}

string Evaluator::getCardFourOfAKind() const {
    string res = {};
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    char isFour, isOne;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 4) isFour = (char)('a' + cards[i].getRank());
        else isOne = (char)('a' + cards[i].getRank());
    for (int i = 0; i < 4; i++)
        res = res + isFour;
    res = res + isOne;
    return res;
}

string Evaluator::getCardThreeOfAKind() const {
    string res = {};
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    char isThree, otherCardA = 'A', otherCardB;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 3) isThree = (char)('a' + cards[i].getRank());
        else if (otherCardA == 'A') otherCardA = (char)('a' + cards[i].getRank());
        else otherCardB = (char)('a' + cards[i].getRank());
    if (otherCardA < otherCardB) swap(otherCardA, otherCardB);
    for (int i = 0; i < 3; i++)
        res = res + isThree;
    res = res + otherCardA;
    res = res + otherCardB;
    return res;
}

string Evaluator::getCardTwoPairs() const {
    string res = {};
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    char isTwoA = 'A', isTwoB, notTwo;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 1) notTwo = (char)('a' + cards[i].getRank());
        else if (isTwoA == 'A') isTwoA = (char)('a' + cards[i].getRank());
        else isTwoB = (char)('a' + cards[i].getRank());
    if (isTwoA < isTwoB) swap(isTwoA, isTwoB);
    res = res + isTwoA; res = res + isTwoA;
    res = res + isTwoB; res = res + isTwoB;
    res = res + notTwo;
    return res;
}

string Evaluator::getCardPair() const {
    string res = {};
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++) cntRank[cards[i].Rank]++;
    char isTwo;
    vector<char> notTwo;
    for (int i = 0; i < 5; i++) {
        if (cntRank[cards[i].Rank] == 2) isTwo = (char)('a' + cards[i].getRank());
        else notTwo.emplace_back((char)('a' + cards[i].getRank()));
    }
    res += isTwo; res += isTwo;
    sort(notTwo.begin(), notTwo.end());
    for (int i = 2; i >= 0; i--)
        res += notTwo[i];
    return res;
}

string Evaluator::strengthCard() const {
    if (Straight()) return getCardStraight();
    if (Flush()) return getCardFlush();
    if (FullHouse()) return getCardFullHouse();
    if (FourOfAKind()) return getCardFourOfAKind();
    if (ThreeOfAKind()) return getCardThreeOfAKind();
    if (TwoPairs()) return getCardTwoPairs();
    if (Pair()) return getCardPair();
    return getCardFlush();
}

bool Evaluator::operator < (const Hand& other) {
    if (strengthRank() != other.strengthRank())
        return strengthRank() < other.strengthRank();
    return strengthCard() < other.strengthCard();
}

bool Evaluator::operator == (const Hand& other) {
    return strengthRank() == other.strengthRank() && strengthCard() == other.strengthCard();
}


