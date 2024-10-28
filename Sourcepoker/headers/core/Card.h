#pragma once
#include <nlohmann/json.hpp>
using namespace std;

class Card {
public:

    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

    NLOHMANN_JSON_SERIALIZE_ENUM(Suit, {
        {Suit::HEARTS, "HEARTS"},
        {Suit::DIAMONDS, "DIAMONDS"},
        {Suit::CLUBS, "CLUBS"},
        {Suit::SPADES, "SPADES"}
        });

    // Use NLOHMANN_JSON_SERIALIZE_ENUM to create JSON conversion for Rank
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
        {Rank::KING, "KING"}
        { Rank::ACE, "ACE" },
        })



    //default constructor
    Card();
    //Regular constructor with specified suit & rank
    Card(Suit s, Rank r);

    //set the card to hidden when using showCards
    void setShown(bool set);

    //Get hidden state of the card (true or false)
    bool getShowState() const;


    //get suit as a enum value
    Suit getSuitEnum() const;
    //get rank as a enum value;
    Rank getRankEnum() const;

    //Fuction to get suit as string
    string getSuit() const;
    //Fuction to get rank as string
    string getRank() const;

    // Function to return the card as a string (e.g., "Ace of Spades")
    string toString() const;

    // Define to_json for Card
    friend void to_json(nlohmann::json& j, const Card& c);
    // Define from_json for Card
    friend void from_json(const nlohmann::json& j, Card& c);

private:
    bool isShown = true;
    Suit suit;
    Rank rank;

};

// Define to_json for Card
void to_json(nlohmann::json& j, const Card& c);
// Define from_json for Card
void from_json(const nlohmann::json& j, Card& c);
