#pragma once

#include <nlohmann/json.hpp>
#include <string>

/// @brief Represents a playing card with a suit and rank, and handles its visibility state.
class Card {
public:
    /// @brief Enum representing the four card suits.
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };

    /// @brief Enum representing the ranks of cards, from TWO to ACE.
    enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

    // JSON serialization for Suit
    NLOHMANN_JSON_SERIALIZE_ENUM(Suit, {
        {Suit::HEARTS, "HEARTS"},
        {Suit::DIAMONDS, "DIAMONDS"},
        {Suit::CLUBS, "CLUBS"},
        {Suit::SPADES, "SPADES"}
        })

    // JSON serialization for Rank
    NLOHMANN_JSON_SERIALIZE_ENUM(Rank, {
        {Rank::TWO, "TWO"},
        {Rank::THREE, "THREE"},
        {Rank::FOUR, "FOUR"},
        {Rank::FIVE, "FIVE"},
        {Rank::SIX, "SIX"},
        {Rank::SEVEN, "SEVEN"},
        {Rank::EIGHT, "EIGHT"},
        {Rank::NINE, "NINE"},
        {Rank::TEN, "TEN"},
        {Rank::JACK, "JACK"},
        {Rank::QUEEN, "QUEEN"},
        {Rank::KING, "KING"},
        {Rank::ACE, "ACE"}
        })

    /// @brief Default constructor, initializes card as the 2 of Hearts.
    Card();

    /// @brief Constructor with specified suit and rank.
    /// @param s The suit of the card.
    /// @param r The rank of the card.
    Card(Suit s, Rank r);

    /// @brief Sets whether the card is shown or hidden.
    /// @param set True to show the card, false to hide it.
    void setShown(bool set);

    /// @brief Gets the show state of the card.
    /// @return True if the card is shown, false if hidden.
    bool getShowState() const;

    /// @brief Gets the suit of the card as an enum value.
    /// @return Suit enum (HEARTS, DIAMONDS, CLUBS, or SPADES).
    Suit getSuitEnum() const;

    /// @brief Gets the rank of the card as an enum value.
    /// @return Rank enum (TWO to ACE).
    Rank getRankEnum() const;

    /// @brief Gets the suit of the card as a string.
    /// @return The suit as a string (e.g., "Hearts").
    std::string getSuit() const;

    /// @brief Gets the rank of the card as a string.
    /// @return The rank as a string (e.g., "Ace").
    std::string getRank() const;

    /// @brief Converts the card to a string format (e.g., "Ace of Spades").
    /// @return The card in "Rank of Suit" format.
    std::string toString() const;

    /// @brief JSON serialization for Card.
    /// @param j JSON object to store the serialized card.
    /// @param c Card object to be serialized.
    friend void to_json(nlohmann::json& j, const Card& c);

    /// @brief JSON deserialization for Card.
    /// @param j JSON object containing serialized card data.
    /// @param c Card object to be deserialized.
    friend void from_json(const nlohmann::json& j, Card& c);

private:
    bool isShown = true;  ///< True if the card is visible, false if hidden.
    Suit suit;            ///< Suit of the card.
    Rank rank;            ///< Rank of the card.
};

// JSON serialization for Card
inline void to_json(nlohmann::json& j, const Card& c) {
    j = nlohmann::json{ {"Suit", c.suit}, {"Rank", c.rank} };
}

// JSON deserialization for Card
inline void from_json(const nlohmann::json& j, Card& c) {
    j.at("Suit").get_to(c.suit);
    j.at("Rank").get_to(c.rank);
}
