#include <gameObject.h>

Hand::Hand() {}

void Hand::organize() {
	sort(cards.begin(), cards.end(), [](Card& left, Card& right) {return left.getRank() < right.getRank();});
}

void Hand::cardToHand(Deck& deck, int count, bool Shown) {
	for (int i = 0; i < count; i++) {
		const Card& dealtCard = deck.deal(Shown);
		cards.push_back( dealtCard);
	}
}

void Hand::showCards() {
    organize();
	for (const Card& card : cards) {
		if (card.getShowState()) cout << card.getRank() << " of " << card.getSuit() << endl;
		else cout << "Hidden" << endl;
	}
}

vector<Card> Hand::getHand () { return cards;}

/*
bool Hand::FourOfAKind() const {
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 4) return true;
    return false;
}

bool Hand::FullHouse() const {
    bool isThree = 0, isTwo = 0;
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    for (int i = 0; i < 5; i++) {
        if (cntRank[cards[i].Rank] == 3) isThree = 1;
        if (cntRank[cards[i].Rank] == 2) isTwo = 1;
    }
    return isTwo && isThree;
}

bool Hand::Flush() const {
    map<string, int> cntSuit;
    for (int i = 0; i < 5; i++)
        cntSuit[cards[i].Suit]++;

    return cntSuit[cards[0].Suit] == 5;
}

bool Hand::Straight() const {
    Hand temp = *this;
    sort(temp.cards, temp.cards + 5);

    for (int i = 0; i < 3; i++)
        if (temp.cards[i].getRank() + 1 != temp.cards[i + 1].getRank()) return false;

    if (temp.cards[3].getRank() + 1 == temp.cards[4].getRank()) return true;
    if (temp.cards[4].getRank() == 12 && temp.cards[0].getRank() == 0) return true;
    return false;
}

bool Hand::RoyalFlush() const {
    bool isKing = 0, isAce = 0;
    for (int i = 0; i < 5; i++) {
        if (cards[i].Rank == "King") isKing = 1;
        if (cards[i].Rank == "Ace") isAce = 1;
    }
    if (Flush() && Straight() && isKing && isAce) return 1;
    return 0;
}

bool Hand::StraightFlush() const {
    if (Flush() && Straight()) return 1;
    return 0;
}

bool Hand::ThreeOfAKind() const {
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 3) return true;
    return false;
}

bool Hand::TwoPairs() const {
    int numTwo = 0;
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 2) numTwo++;
    return numTwo == 4;
}

bool Hand::Pair() const {
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 2) return true;
    return false;
}

int Hand::strengthRank() const {
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

string Hand::getStrategy() {
    return strategy[strengthRank() - 1];
}

string Hand::getCardFlush() const {
    Hand temp = *this;
    sort(temp.cards.begin(), temp.cards.end());
    string res = {};
    for (int i = 4; i >= 0; i--)
        res = res + (char)('a' + temp.cards[i].getRank());

    return res;
}

string Hand::getCardStraight() const {
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

string Hand::getCardFullHouse() const {
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

string Hand::getCardFourOfAKind() const {
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

string Hand::getCardThreeOfAKind() const {
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

string Hand::getCardTwoPairs() const {
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

string Hand::getCardPair() const {
    string res = {};
    map<string, int> cntRank;
    for (int i = 0; i < 5; i++)
        cntRank[cards[i].Rank]++;
    char isTwo;
    vector<char> notTwo;
    for (int i = 0; i < 5; i++)
        if (cntRank[cards[i].Rank] == 2) isTwo = (char)('a' + cards[i].getRank());
        else notTwo.emplace_back((char)('a' + cards[i].getRank()));
    res += isTwo; res += isTwo;
    sort(notTwo.begin(), notTwo.end());
    for (int i = 2; i >= 0; i--)
        res += notTwo[i];
    return res;
}

string Hand::strengthCard() const {
    if (Straight()) return getCardStraight();
    if (Flush()) return getCardFlush();
    if (FullHouse()) return getCardFullHouse();
    if (FourOfAKind()) return getCardFourOfAKind();
    if (ThreeOfAKind()) return getCardThreeOfAKind();
    if (TwoPairs()) return getCardTwoPairs();
    if (Pair()) return getCardPair();
    return getCardFlush();
}

bool Hand::operator < (const Hand& other) {
    if (strengthRank() != other.strengthRank())
        return strengthRank() < other.strengthRank();
    return strengthCard() < other.strengthCard();
}

bool Hand::operator == (const Hand& other) {
    return strengthRank() == other.strengthRank() && strengthCard() == other.strengthCard();
}*/