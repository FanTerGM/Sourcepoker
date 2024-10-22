
#include "gameObject.h"

int main() {
    Table table(TEXAS);
    deck.shuffle();
    Player player("Alice");

    // Deal 5 cards to the player's hand
    for (int i = 0; i < 5; i ++) player.cardToHand(deck);

    // Display the player's hand
    std::vector<Card> playerHand = player.getPlayerHand();
    for (const auto& card : playerHand) {
        std::cout << "Card: " << card.getRank() << " of " << card.getSuit() << std::endl;
    }

    return 0;
}
