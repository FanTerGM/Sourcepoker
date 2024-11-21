#pragma once
#include <SFML/Graphics.hpp>

class GameWindow {
public:
    GameWindow(int width, int height, const std::string& title);
    void run();
    //// Create a window with a width of 800 and height of 600
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Poker Game");

    //// Set the framerate limit
    //Window.setFramerateLimit(60);


private:
    sf::RenderWindow window;
    void processEvents();
    void render();
};
