#include <gameObject.h>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <iostream>
#include <algorithm> // For std::max_element

using json = nlohmann::json;

/* --- Definitions for the Player class, representing a user's profile and gameplay statistics --- */

// Default constructor for an empty player object
Player::Player() {}

// Constructor for a new player with a username
Player::Player(const std::string& name) : username(name) {}

// Constructor for a player with existing profile data
Player::Player(const std::string& username, double gamesWon, double winRate, int balance, int rank, const std::array<int, 10>& handHistory)
    : username(username), gamesWon(gamesWon), winRate(winRate), balance(balance), rank(rank), handHistory(handHistory) {}


// Returns the player's username
std::string Player::getUsername() const {
    return username;
}

// Displays player's profile information in the console
void Player::displayInfo() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Winrate: " << winRate << "%" << std::endl;
    std::cout << "Current Ranking: " << rank << std::endl;
    std::cout << "Favorite Hand: " << getFavoriteHand() << std::endl;
}

// Returns the player's rank
int Player::getRank() const {
    return rank;
}

// Returns the player's win rate
double Player::getWinRate() const {
    return winRate;
}

// Returns the total number of games played by the player
int Player::getGamesPlayed() const {
    return std::accumulate(handHistory.begin(), handHistory.end(), 0);
}

// Returns the player's favorite hand based on most frequently played hand
std::string Player::getFavoriteHand() const {
    auto maxPlayedHand = std::max_element(handHistory.begin(), handHistory.end());
    int handId = std::distance(handHistory.begin(), maxPlayedHand);
    return Evaluator().rankToString(handId); // Convert hand ID to a human-readable name
}

// Updates the player's ranking
void Player::updateRank(int newRank) {
    rank = newRank;
}

// Updates game history, calculates win rate, and updates balance after a game
void Player::updateGameHistory(bool won, int earnings) {
    if (won){
        int handStrengthIndex = static_cast<int>(Evaluator(getHand()).evaluateHandRank());
        handHistory[handStrengthIndex]++; // Track this hand's occurrence
        gamesWon++;
    }
    winRate = (gamesWon * 100) / getGamesPlayed(); // Calculate win rate as a percentage
    balance += earnings;

    saveProfile(); // Save the updated player profile
}

// Saves player profile to a JSON file in the specified directory
void Player::saveProfile(const std::string& directory) const {
    // Avoid saving profiles of AI players
    if (username.find("AI_") != std::string::npos) return;

    std::filesystem::create_directories(directory);

    std::ofstream outFile(directory + username + ".json");
    if (outFile.is_open()) {
        outFile << json(*this).dump(4); // Pretty-print JSON with indentation
        outFile.close();
    }
}

// Loads an existing player profile from a JSON file or creates a new one if none exists
Player Player::loadProfile(const std::string& username, const std::string& directory) {
    std::string filename = directory + username + ".json";

    std::cout << "Loading player..." << std::endl;

    if (std::filesystem::exists(filename)) {
        std::ifstream file(filename);
        if (file.is_open()) {
            json playerData;
            file >> playerData;
            file.close();

            std::cout << "Player found! Loading..." << std::endl;
            return playerData.get<Player>(); // Deserialize JSON to Player
        }
    }

    // If profile not found, create a new player profile
    std::cout << "Player not found...Creating new player..." << std::endl;
    Player newPlayer(username);
    newPlayer.saveProfile();
    return newPlayer;
}

// Overloaded greater-than operator for comparing player hands
bool Player::operator>(const Player& other) const {
    return Evaluator(getHand()) > Evaluator(other.getHand());
}

// Overloaded equality operator for comparing player hands
bool Player::operator==(const Player& other) const {
    return Evaluator(getHand()) == Evaluator(other.getHand());
}

