
#include "gameObject.h"

int main() {
    // Create a deck of cards
    Deck deck;
    // Shuffle the deck
    deck.shuffle();

    // Deal 5 cards and display them
    for (int i = 0; i < 5; ++i) {
        Card card = deck.deal();
        std::cout << "Dealt card: " << card.toString() << std::endl;
    }

    std::cout << "Remaining cards in deck: " << deck.size() << std::endl;

    return 0;
}
