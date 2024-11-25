#include <gameObject.h>
using namespace sf;

GameWindow::GameWindow(int width, int height, const std::string& title)
    : window(sf::VideoMode(width, height), title) {}

void GameWindow::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void GameWindow::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GameWindow::render() {
    window.clear();
    // Create a window with a width of 800 and height of 600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Poker Game");

    // Set the framerate limit
    //Window.setFramerateLimit(60);

    window.display();
}
