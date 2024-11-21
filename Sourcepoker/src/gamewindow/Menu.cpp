#include "../headers/gamewindow/Menu.h"
#include "iostream"


Menu::Menu(float width, float height) {
    if (!font.loadFromFile("Pangolin.ttf")) { // Đảm bảo tệp font tồn tại
        std::cerr << "Error loading font\n";
    }

    // Danh sách tùy chọn menu
    std::vector<std::string> options = { "Play", "Leaderboard", "Credit", "Exit"};
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

// Lấy mục được chọn
int Menu::getSelectedItemIndex() {
    return selectedItemIndex;
}


//Menu::Menu(float width, float height) {
//	if (!font.loadFromFile("Pangolin.ttf")) {
//		//handle error
//		std::cerr << "Error loading font\n";
//	}
//	menu[0].setFont(font);
//	menu[0].setFillColor(sf::Color::White);
//	menu[0].setString("Game Mode");
//	menu[0].setPosition(sf::Vector2f(width / 4, height / (MAX_ITEMS + 1) * 1));
//
//	std::vector<std::string> options = { "Game Mode", "Leaderboard", "Credit", "Exit"};
//		for (size_t i = 0; i < options.size(); ++i) {
//			Text text;
//	        text.setFont(font);
//	        text.setString(options[i]);
//	        text.setFillColor(i == 0 ? Color::Red : Color::White); // Đánh dấu mục đầu tiên
//	        text.setPosition(Vector2f(width / 2.5, height / (options.size() + 1) * (i + 1)));
//		}
//Menu::~Menu(){
//
//
//
//}