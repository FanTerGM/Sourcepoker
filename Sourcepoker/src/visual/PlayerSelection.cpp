#include "../headers/visual/PlayerSelection.h"
#include "iostream"

PlayerSelection::PlayerSelection(int width, int height) {
    font.loadFromFile("Pangolin-Regular.ttf");
    //setup text fields
    playerCountText.setFont(font);
    playerCountText.setString("Number of Players (human & AI): ");
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
    playerTextBox.setPosition(600, 150);
    playerTextBox.setFillColor(sf::Color(50, 50, 50));

    npcTextBox.setSize(sf::Vector2f(200, 40));
    npcTextBox.setPosition(600, 250);
    npcTextBox.setFillColor(sf::Color(50, 50, 50));

    //setup continue button
    continueButton.setSize(sf::Vector2f(200, 50));
    continueButton.setPosition(600, 350);
    continueButton.setFillColor(sf::Color(0, 150, 0));

    continueButtonText.setFont(font);
    continueButtonText.setString("Continue");
    continueButtonText.setCharacterSize(30);
    continueButtonText.setFillColor(sf::Color::White);
    continueButtonText.setPosition(620, 360);

    playerCount = "";
    npcCount = "";
}

void PlayerSelection::handleTextInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8) { //back space
                // Nếu người dùng nhấn backspace, xóa ký tự cuối trong text box hiện tại
                if (isPlayerTextBoxSelected && !playerCount.empty()) {
                    playerCount.pop_back();
                }else if (isNpcTextBoxSelected && !npcCount.empty()) {
                    npcCount.pop_back();
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
    else if (npcTextBox.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
        isPlayerTextBoxSelected = false;
        isNpcTextBoxSelected = true;
    }
    if (continueButton.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
        currentState = INPUT_PLAYER_INFO;
        std::cout << "pressed button - " << currentState<< std::endl;
    }
    else if (isContinueButtonPressed(mousePosition)){
        handleContinueButton(currentState);
        std::cout << "pressed button - X" << std::endl;
    }
}

void PlayerSelection::handleContinueButton(GameState& currentState) {
    // Nếu nhấn nút "Continue", chuyển sang trạng thái INPUT_PLAYER_INFO
    currentState = INPUT_PLAYER_INFO;
    // Ẩn phần nhập số lượng người chơi
    //playerCount.clear();
    //npcCount.clear();
    // Cập nhật các thành phần khác của giao diện nếu cần
    // Ví dụ: tạo các ô nhập thông tin cho từng người chơi ở INPUT_PLAYER_INFO
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

bool PlayerSelection::isContinueButtonPressed(const sf::Vector2i& mousePosition) {
    // Kiểm tra xem có bấm vào nút Continue hay không
    if (continueText.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
        return true;
    }
    return false;
}



void PlayerSelection::render(sf::RenderWindow& window) {

    window.draw(playerCountText);
    window.draw(npcCountText);
    window.draw(playerTextBox);
    window.draw(npcTextBox);


    // Vẽ lại văn bản đã nhập
    sf::Text playerCountDisplay(playerCount, font, 30);
    playerCountDisplay.setFillColor(sf::Color::White);
    playerCountDisplay.setPosition(610, 160);  // Vị trí của text box người chơi
    window.draw(playerCountDisplay);

    sf::Text npcCountDisplay(npcCount, font, 30);
    npcCountDisplay.setFillColor(sf::Color::White);
    npcCountDisplay.setPosition(610, 260);  // Vị trí của text box NPC
    window.draw(npcCountDisplay);

    window.draw(continueButton);
    window.draw(continueButtonText);
}
