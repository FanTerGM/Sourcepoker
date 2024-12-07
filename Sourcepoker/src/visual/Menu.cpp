#include "../headers/visual/Menu.h"
#include "iostream"


Menu::Menu(int width, int height, const std::vector<std::string>& options) {
    if (!font.loadFromFile("Pangolin-Regular.ttf")) { // load font 
        std::cerr << "Error loading font\n";
    }

    // Main menu option
    //  std::vector<std::string> options = { "Play", "Leaderboard", "Credit", "Exit"};
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]); //get the text
        text.setFillColor(sf::Color::White); //coulor of the text
        text.setPosition(sf::Vector2f(width / 10, height / (options.size() + 1) * (i + 1))); 
        menuOptions.push_back(text);
    }

    selectedItemIndex = 0; // if no option
}

// draw menu
void Menu::draw(sf::RenderWindow& window) {
    for (const auto& option : menuOptions) {
        window.draw(option);
    }
}

// Xử lý di chuột (thay đổi màu khi trỏ chuột lên mục)
void Menu::handleMouseHover(sf::Vector2i mousePosition) {
    for (size_t i = 0; i < menuOptions.size(); ++i) {
        sf::FloatRect bounds = menuOptions[i].getGlobalBounds();
        if (bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            menuOptions[i].setFillColor(sf::Color::Red); //nếu di tới sẽ chuyển màu đỏ
        }
        else {
            menuOptions[i].setFillColor(sf::Color::White);
        }
    }
}

//xử lý sự kiện nhấn chuột
void Menu::handleMouseClickMain(sf::Vector2i mousePosition, GameState& currentState) {
    // duyệt qua các thư mục trong menu
    for (int i = 0; i < menuOptions.size(); ++i) {
        sf::FloatRect bounds = menuOptions[i].getGlobalBounds();
        if (bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            selectedItemIndex = i;
            switch (i) {
            case 0:
                currentState = PLAYER_SELECTION;  // nhập số lượng ng chơi và npc
                break;
            case 1:
                currentState = LEADERBOARD;  // Hiển thị Leaderboard
                break;
            case 2:
                currentState = EXIT;  // Thoát game
                break;
            }
        }
    }
}

void Menu::handleMouseClickPlay(sf::Vector2i mousePosition, GameState& currentState) {
    // duyệt qua các thư mục trong menu
    for (int i = 0; i < menuOptions.size(); ++i) {
        sf::FloatRect bounds = menuOptions[i].getGlobalBounds();
        if (bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            selectedItemIndex = i;
            switch (i) {
            case 0:
                currentState = GAME_DEFAULT;  // nhập số lượng ng chơi và npc
                break;
            case 1:
                currentState = GAME_STUD_5;  // Hiển thị Leaderboard
                break;
            case 2:
                currentState = GAME_STUD_7;  // Hiển thị thông tin credit
                break;
            case 3:
                currentState = GAME_DRAW;  // Thoát game
                break;
            }
        }
    }
}
