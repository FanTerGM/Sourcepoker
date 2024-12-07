﻿#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <gameObject.h>

class PlayerInfoInput {
public:
    PlayerInfoInput();

    void setPlayerNPCs(int _numPlayers, int _numNPCs);

    void render(sf::RenderWindow& window);  // Function to render the UI
    void handleMouseClick(const sf::Vector2i& mousePosition, GameState &currentState);
    void handleTextInput(sf::Event& event);

    void loadPlayerListFromFile(const std::string& directory);
    void savePlayerNameToFile(const std::string& playerName, const std::string& directory);
    void initializePlayerList();
    void setNumberOfPlayers(int count) { numberOfPlayers = count; }
    std::vector<std::string> getPlayerNames() const { return playerInputs; }
    std::vector<Player> getPlayers() { return players; }
    sf::Font getFont() const { return font; }

    bool areAllPlayersNamesEntered();
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

    bool isPlayerNameTextBoxSelected = false;
 
};
