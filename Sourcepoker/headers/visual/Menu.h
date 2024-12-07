#pragma once

#include <SFML-2.6.1/include/SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../headers/game/GameState.h"

class Menu {
private:

    sf::Font font;                           // Font để hiển thị menu
    std::vector<sf::Text> menuOptions;       // Các tùy chọn menu
    int selectedItemIndex;                   // Chỉ mục của mục được chọn

public:
    Menu(int width, int height, const std::vector<std::string>& options); // Constructor (options: một danh sách chứa các mục trong menu)
    void draw(sf::RenderWindow& window);     // Vẽ menu lên cửa sổ
    void handleMouseHover(sf::Vector2i mousePosition); // Xử lý di chuột
    void handleMouseClickMain(sf::Vector2i mousePosition, GameState& currentState); // Xử lý sự kiện chuột Main menu
    void handleMouseClickPlay(sf::Vector2i mousePosition, GameState& currentState); // Xử lý sự kiện chuột play menu
    //int getSelectedItemIndex();              // Lấy chỉ mục mục được chọn
    bool isOptionClicked(const std::string& option) {
        for (int i = 0; i < menuOptions.size(); ++i) {
            if (menuOptions[i].getString() == option && menuOptions[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition()))) {
                return true;
            }
        }
        return false;
    };
};

