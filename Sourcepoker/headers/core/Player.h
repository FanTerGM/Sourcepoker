#pragma once

#include "Hand.h"
#include "../Logic/Evaluator.h"
#include <nlohmann/json.hpp>


/// @class Player
/// @brief Represents a player in the game, with unique statistics, game history, and profile management.
class Player : public Hand {
public:
    bool folded = false;
    int bet = 0;

    /// @brief Default constructor for a placeholder player.
    Player();

    /// @brief Constructs a new player profile with initial values.
    /// @param username The player's username.
    explicit Player(const std::string& username);

    /// @brief Constructs a player with existing profile data.
    /// @param username The player's username.
    /// @param gamesWon Number of games won.
    /// @param winRate The player's win rate as a percentage.
    /// @param balance Player's initial balance.
    /// @param rank Player's ranking in the game.
    /// @param handHistory Array tracking frequency of hands played by the player.
    Player(const std::string& username, double gamesWon, double winRate, int balance, int rank, const std::array<int, 10>& handHistory);

    /// @brief Returns the player's username.
    std::string getUsername() const;

    /// @brief Displays the player's statistics.
    void displayInfo() const;

    /// @brief Returns the player's ranking.
    int getRank() const;

    int getBalance() const;

    /// @brief Returns the player's win rate as a percentage.
    double getWinRate() const;

    /// @brief Returns the number of games played by the player.
    int getGamesPlayed() const;

    /// @brief Returns the player's favorite hand based on the most frequently played hand.
    std::string getFavoriteHand() const;

    /// @brief Updates player's ranking.
    /// @param newRank The updated rank to assign to the player.
    void updateRank(int newRank);

    /// @brief Updates the player's game history, win rate, and balance after a game.
    /// @param won True if the player won; otherwise, false.
    /// @param earnings The amount of money gained or lost in the game.
    void updateGameHistory(bool won = false, int earnings = 0);

    /// @brief Saves the player's profile as a JSON file.
    /// @param directory Directory path to save the profile file. Default is "Resources/playerInfo".
    void saveProfile(const std::string& directory = "Resources/playerInfo/") const;

    /// @brief Loads an existing player profile from a JSON file or creates a new profile if none exists.
    /// @param username The player's username.
    /// @param directory Directory path to look for the profile file. Default is "Resources/playerInfo".
    /// @return A Player object loaded with data from the JSON file.
    static Player loadProfile(const std::string& username, const std::string& directory = "Resources/playerInfo/");

    /// @brief Overloaded greater-than operator for comparing player ranks.
    bool operator>(const Player& other) const;

    /// @brief Overloaded equality operator for comparing player usernames.
    bool operator==(const Player& other) const;

    /// @brief JSON serialization function for Player.
    friend void to_json(nlohmann::json& j, const Player& p);

    /// @brief JSON deserialization function for Player.
    friend void from_json(const nlohmann::json& j, Player& p);

private:
    std::string username;           ///< The player's username.
    int balance = 1000;             ///< The player's initial money balance.
    double gamesWon = 0;            ///< Total number of games won by the player.
    double winRate = 0;             ///< Player's win rate as a percentage.
    int rank = 0;                   ///< Player's ranking.
    std::array<int, 10> handHistory{}; ///< Frequency of different hands played by the player.
};

// JSON serialization for Player
inline void to_json(nlohmann::json& j, const Player& p) {
    j = nlohmann::json{
        {"username", p.username},
        {"gamesWon", p.gamesWon},
        {"winRate", p.winRate},
        {"balance", p.balance},
        {"rank", p.rank},
        {"handHistory", p.handHistory}
    };
}

// JSON deserialization for Player
inline void from_json(const nlohmann::json& j, Player& p) {
    j.at("username").get_to(p.username);
    j.at("gamesWon").get_to(p.gamesWon);
    j.at("winRate").get_to(p.winRate);
    j.at("balance").get_to(p.balance);
    j.at("rank").get_to(p.rank);
    j.at("handHistory").get_to(p.handHistory);
}