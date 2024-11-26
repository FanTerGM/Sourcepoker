#include "../headers/core/PlayerSelection.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "iostream"

PlayerSelection::PlayerSelection(float width, float height) {
	if (!font.loadFromFile("Pangolin-Regular.ttf"))
		std::cerr << "Errror loading font for player selection\n";

    //label text
    labelText.setFont(font);
    labelText.setString("Enter number of players and NPCs:");
    labelText.setCharacterSize(30);
    labelText.setFillColor(sf::Color::White);
    labelText.setPosition(width / 2 - 200, height / 4);

	playerCountText.setFont(font);
	playerCountText.setString("Enter number of player (human & AI): ");
	playerCountText.setCharacterSize(24);
	playerCountText.setFillColor(sf::Color::White);
	playerCountText.setPosition(width / 2 - 150, height / 2);

	npcCountText.setFont(font);
	npcCountText.setString("Enter the amount of NPC: ");
	npcCountText.setCharacterSize(24);
	npcCountText.setFillColor(sf::Color::White);
	npcCountText.setPosition(width / 2 - 150, height / 1.5);

	playerCount = 1;
	npcCount = 0;

	isInputtingPlayerCount = true;
	isInputtingNpcCount = false;
}

void PlayerSelection::handleTextInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        //handle digit input 0->9
        if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            char enteredChar = static_cast<char>(event.text.unicode);
            if (isInputtingPlayerCount) {
                playerCountInput += enteredChar;
                playerCountText.setString("Players: " + playerCountInput);
            }
            else if (isInputtingNpcCount) {
                npcCountInput += enteredChar;
                npcCountText.setString("NPCs: " + npcCountInput);
            }
        }
        // Handle backspace to remove last character
        else if (event.text.unicode == 8) {  // Backspace
            if (isInputtingPlayerCount && !playerCountInput.empty()) {
                playerCountInput.pop_back();
                playerCountText.setString("Players: " + playerCountInput);
            }
            if (isInputtingNpcCount && !npcCountInput.empty()) {
                npcCountInput.pop_back();
                npcCountText.setString("NPCs: " + npcCountInput);
            }
        }
    }
}

void PlayerSelection::handleMouseClick(sf::Vector2i mousePosition, GameState& currentState) {
    // Switch from player input to NPC input
    if (isInputtingPlayerCount) {
        if (!playerCountInput.empty()) {
            playerCount = std::stoi(playerCountInput);
        }
        else {
            playerCount = 1; // Default to 1 if no input
        }
        isInputtingPlayerCount = false;
        isInputtingNpcCount = true;
    }
    // Finish NPC input and go to Play Menu
    else if (isInputtingNpcCount) {
        if (!npcCountInput.empty()) {
            npcCount = std::stoi(npcCountInput);
        }
        else {
            npcCount = 0; // Default to 0 if no input
        }
        currentState = PLAY_MENU; // Transition to Play Menu
    }
}


void PlayerSelection::render(sf::RenderWindow& window) {
    window.clear();

    window.draw(playerCountText);
    window.draw(npcCountText);

    // Hiển thị số lượng người chơi và NPC đã nhập
    if (isInputtingPlayerCount) {
        sf::Text playerCountInputText;
        playerCountInputText.setFont(font);
        playerCountInputText.setString(playerCountInput);
        playerCountInputText.setCharacterSize(24);
        playerCountInputText.setFillColor(sf::Color::White);
        playerCountInputText.setPosition(400, 100);
        window.draw(playerCountInputText);
    }
    else if (isInputtingNpcCount) {
        sf::Text npcCountInputText;
        npcCountInputText.setFont(font);
        npcCountInputText.setString(npcCountInput);
        npcCountInputText.setCharacterSize(24);
        npcCountInputText.setFillColor(sf::Color::White);
        npcCountInputText.setPosition(400, 150);
        window.draw(npcCountInputText);
    }

    window.display();
}
