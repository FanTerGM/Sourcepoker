
#include "gameObject.h"

int main() {
    Deck deck;
    deck.shuffle();
    Player player("Alice");

    // Deal 5 cards to the player's hand
    player.cardToHand(deck, 5);

    // Display the player's hand
    std::vector<Card> playerHand = player.getPlayerHand();
    for (const auto& card : playerHand) {
        std::cout << "Card: " << card.getRank() << " of " << card.getSuit() << std::endl;
    }

    return 0;
}
