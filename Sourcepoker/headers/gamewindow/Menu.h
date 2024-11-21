#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML-2.6.1/include/SFML/Graphics.hpp>
#include <vector>
#include <string>


enum GameState { //quản lý trạng thái game
    MAIN_MENU,
    PLAY_MENU, //PLAY_MENU have 3 diffirents game mode
    LEADERBOARD,
    CREDIT,
    EXIT
};

class Menu {
private:
    sf::Font font;                           // Font để hiển thị menu
    std::vector<sf::Text> menuOptions;       // Các tùy chọn menu
    int selectedItemIndex;                   // Chỉ mục của mục được chọn

public:
    Menu(float width, float height, const std::vector<std::string>& options ); // Constructor (options: một danh sách chứa các mục trong menu)
    void draw(sf::RenderWindow& window);     // Vẽ menu lên cửa sổ
    void handleMouseHover(sf::Vector2i mousePosition); // Xử lý di chuột
    void handleMouseClick(sf::Vector2i mousePosition, GameState& currentState);  // Xử lý sự kiện chuột
    int getSelectedItemIndex();              // Lấy chỉ mục mục được chọn
};

#endif // MENU_H
