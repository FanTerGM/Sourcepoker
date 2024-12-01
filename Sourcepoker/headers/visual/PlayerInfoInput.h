#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <gameObject.h>

class PlayerInfoInput {
public:
    PlayerInfoInput(float width, float height, int numPlayers);

    void render(sf::RenderWindow& window);
    void handleMouseClick(const sf::Vector2i& mousePosition);
    void handleTextInput(sf::Event& event);

private:
    std::vector<sf::Text> playerNames; // Lưu trữ tên người chơi
    std::vector<sf::RectangleShape> nameInputBoxes; // Các hộp nhập tên người chơi
    int numPlayers;

    sf::Font font;
    sf::RectangleShape inputBox;    // Ô nhập thông tin người chơi
    sf::Text inputText;             // Text nhập

    std::vector<bool> isActive; // Mảng kiểm tra ô nhập hiện tại có đang được chọn hay không
    int activePlayerIndex; // Chỉ số người chơi đang nhập tên
    std::vector<std::string> playerInputs; // Lưu tên người chơi
    sf::RectangleShape continueButton;
};