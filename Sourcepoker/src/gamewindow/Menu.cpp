#include "../headers/gamewindow/Menu.h"
#include "iostream"


Menu::Menu(float width, float height, const std::vector<std::string>& options) {
    if (!font.loadFromFile("Pangolin-Regular.ttf")) { // Đảm bảo tệp font tồn tại
        std::cerr << "Error loading font\n";
    }

    // Danh sách tùy chọn menu
    //  std::vector<std::string> options = { "Play", "Leaderboard", "Credit", "Exit"};
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]); //get the text
        text.setFillColor(sf::Color::White); //coulor of the text
        text.setPosition(sf::Vector2f(width / 2.5, height / (options.size() + 1) * (i + 1)));
        menuOptions.push_back(text);
    }

    selectedItemIndex = -1; // if no option
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
void Menu::handleMouseClick(sf::Vector2i mousePosition, GameState &currentState) {
    // find the diffirent between size_t and rsize_t
    for (size_t i = 0; i < menuOptions.size(); ++i) {
        sf::FloatRect bounds = menuOptions[i].getGlobalBounds();
        if (bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            selectedItemIndex = i;
            switch (i) {
            case 0:
                currentState = PLAY_MENU;  // Chọn chế độ chơi
                break;
            case 1:
                currentState = LEADERBOARD;  // Hiển thị Leaderboard
                break;
            case 2:
                currentState = CREDIT;  // Hiển thị thông tin credit
                break;
            case 3:
                currentState = EXIT;  // Thoát game
                break;
            }
        }
    }
}

//// Lấy mục được chọn
//int Menu::getSelectedItemIndex() {
//    return selectedItemIndex;
//}
