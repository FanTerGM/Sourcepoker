#pragma once

class Deck {
public:
    /// @brief Creates a standard 52-card deck (unshuffled)
    Deck();

    /// @brief Deals the top card from the deck
    /// @param Shown Set to true if the dealt card should be shown, false if hidden
    /// @return The next card in the deck
    Card deal(bool Shown = true);

    /// @brief Gets the number of remaining cards in the deck
    /// @return The count of cards left to deal
    int remainingCards() const;

private:
    Card cards[52];         ///< Array to hold 52 cards
    int topCardIndex;       ///< Tracks the index of the next card to be dealt
};