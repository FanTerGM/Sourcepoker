#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <gameObject.h>

class PlayerInfoInput {
public:
    PlayerInfoInput(int playerCount, int npcCount);

    void render(sf::RenderWindow& window);  // Function to render the UI
    void handleMouseClick(const sf::Vector2i& mousePosition);
    void handleTextInput(sf::Event& event);
    void handleEvents(sf::RenderWindow& window);  // Function to handle events like mouse and keyboard input

    void loadPlayerListFromFile(const std::string& directory);
    void savePlayerNameToFile(const std::string& playerName, const std::string& directory);
    void initializePlayerList();
    void setNumberOfPlayers(int count) { numberOfPlayers = count; }
    const std::vector<std::string>& getPlayerNames() const { return playerInputs; }
    const std::vector<Player>& getPlayers() const { return players; }
private:

    int numberOfPlayers;
    std::vector<std::string> playerInputs;
    std::vector<Player> players;
    std::vector<std::string> playerList;
    int activePlayerIndex = -1;  // Khai báo biến lưu chỉ số người chơi hiện đang nhập (mặc định là không có ai)
    std::vector<sf::RectangleShape> nameInputBoxes;

    //ui elements
    sf::Font font;
    sf::Text playerNameText;
    std::vector<sf::RectangleShape> playerNameBoxes;
    sf::RectangleShape continueButton;
    sf::Text continueText;
    sf::Text errorText;

    int numPlayers;
    int numNPCs;

    //sf::Text infoText;
    //std::string playerName; // Tên người chơi

    bool isPlayerNameTextBoxSelected = false;
 
};
