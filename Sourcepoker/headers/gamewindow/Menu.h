#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


enum GameState { //quản lý trạng thái game
    MAIN_MENU,
    MODE_MENU,
    GAMEPLAY
};

class Menu {
private:
    sf::Font font;                           // Font để hiển thị menu
    std::vector<sf::Text> menuOptions;       // Các tùy chọn menu
    int selectedItemIndex;                   // Chỉ mục của mục được chọn

public:
    Menu(float width, float height /*, const std::vector<std::string>& options*/ );         // Constructor (find more information about index 3)
    void draw(sf::RenderWindow& window);     // Vẽ menu lên cửa sổ
    void handleMouseClick(sf::Vector2i mousePosition); // Xử lý sự kiện chuột
    void handleMouseHover(sf::Vector2i mousePosition); // Xử lý di chuột
    int getSelectedItemIndex();              // Lấy chỉ mục mục được chọn
};

#endif // MENU_H
