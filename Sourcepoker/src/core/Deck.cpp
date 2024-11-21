#include <gameObject.h>
#include <algorithm>
#include <random>

// Constructor: Initializes deck with 52 cards and shuffles them
Deck::Deck() : topCardIndex(0) {
    int index = 0;

    // Populate deck with each suit and rank combination
    for (int s = Card::HEARTS; s <= Card::SPADES; s++) {
        for (int r = Card::TWO; r <= Card::ACE; r++) {
            cards[index++] = Card(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r));
        }
    }

    // Shuffle deck using random_device and mt19937 for randomness
    std::random_device rd;
    std::mt19937 eng(rd());
    std::shuffle(std::begin(cards), std::end(cards), eng);
}

// Deals the top card and increments the index
Card Deck::deal(bool Shown) {
    if (topCardIndex < 52) {
        cards[topCardIndex].setShown(Shown);
        return cards[topCardIndex++];
    }
    throw std::out_of_range("No cards left in deck");
}

// Returns the count of cards remaining in the deck
int Deck::remainingCards() const {
    return 52 - topCardIndex;
}