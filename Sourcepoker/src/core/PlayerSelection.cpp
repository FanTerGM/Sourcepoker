#include "../headers/core/PlayerSelection.h"
#include "iostream"

PlayerSelection::PlayerSelection(int width, int height) {
    font.loadFromFile("Pangolin-Regular.ttf");
    //setup text fields
    playerCountText.setFont(font);
    playerCountText.setString("Number of Players: ");
    playerCountText.setCharacterSize(30);
    playerCountText.setFillColor(sf::Color::White);
    playerCountText.setPosition(100, 150);

    npcCountText.setFont(font);
    npcCountText.setString("Number of NPCs: ");
    npcCountText.setCharacterSize(30);
    npcCountText.setFillColor(sf::Color::White);
    npcCountText.setPosition(100, 250);
    
    //setup text box
    playerTextBox.setSize(sf::Vector2f(200, 40));
    playerTextBox.setPosition(400, 150);
    playerTextBox.setFillColor(sf::Color(50, 50, 50));

    npcTextBox.setSize(sf::Vector2f(200, 40));
    npcTextBox.setPosition(400, 250);
    npcTextBox.setFillColor(sf::Color(50, 50, 50));

    //setup continue button
    continueButton.setSize(sf::Vector2f(200, 50));
    continueButton.setPosition(400, 350);
    continueButton.setFillColor(sf::Color(0, 150, 0));

    continueButtonText.setFont(font);
    continueButtonText.setString("Continue");
    continueButtonText.setCharacterSize(30);
    continueButtonText.setFillColor(sf::Color::White);
    continueButtonText.setPosition(420, 360);

    playerCount = "";
    npcCount = "";
}

void PlayerSelection::handleTextInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8) { //back space
                // Nếu người dùng nhấn backspace, xóa ký tự cuối trong text box hiện tại
                if (isPlayerTextBoxSelected && !playerCount.empty()) {
                    playerCount.pop_back();  // Xóa ký tự cuối cùng trong playerCount
                }else if (isNpcTextBoxSelected && !npcCount.empty()) {
                    npcCount.pop_back();  // Xóa ký tự cuối cùng trong npcCount
                }
            }
            else if (event.text.unicode >=48 && event.text.unicode <= 57) {
                char inputChar = static_cast<char>(event.text.unicode);
                if (isPlayerTextBoxSelected) {
                    playerCount += inputChar;
                }
                else if (isNpcTextBoxSelected) {
                    npcCount += inputChar;
                }
            }
        }
    }
}

void PlayerSelection::handleMouseClick(const sf::Vector2i& mousePosition, GameState& currentState) {
    if (playerTextBox.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
        isPlayerTextBoxSelected = true;
        isNpcTextBoxSelected = false;
    }
    if (npcTextBox.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
        isPlayerTextBoxSelected = false;
        isNpcTextBoxSelected = true;
    }
    if (continueButton.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
        std::cout << "Continue Button clicked!" << std::endl;
        currentState = INPUT_PLAYER_INFO;
    }
}

bool PlayerSelection::isContinueClicked(const sf::Vector2i& mousePosition) {
    return continueButton.getGlobalBounds().contains(sf::Vector2f(mousePosition));
}

int PlayerSelection::getNumPlayers() const {
    return std::stoi(playerCount);
}

int PlayerSelection::getNumNPCs() const {
    return std::stoi(npcCount);
}

void PlayerSelection::render(sf::RenderWindow& window) {
    // Draw the text boxes, labels, and continue button
    window.draw(playerCountText);
    window.draw(npcCountText);
    window.draw(playerTextBox);
    window.draw(npcTextBox);
    window.draw(continueButton);
    window.draw(continueButtonText);


    // Vẽ lại văn bản đã nhập
    sf::Text playerCountDisplay(playerCount, font, 30);
    playerCountDisplay.setFillColor(sf::Color::Red);
    playerCountDisplay.setPosition(410, 160);  // Vị trí của text box người chơi
    window.draw(playerCountDisplay);

    sf::Text npcCountDisplay(npcCount, font, 30);
    npcCountDisplay.setFillColor(sf::Color::Red);
    npcCountDisplay.setPosition(410, 260);  // Vị trí của text box NPC
    window.draw(npcCountDisplay);
}
