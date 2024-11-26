#include "../headers/game/GameState.h"

GameState currentState = GameState::MAIN_MENU;

while (window.isOpen()) {
    //event polling
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            if (currentState == MAIN_MENU) {
                mainMenu.handleMouseHover(mousePosition);
            }
            else if (currentState == PLAY_MENU) {
                playMenu.handleMouseHover(mousePosition);
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (currentState == MAIN_MENU) {
                    mainMenu.handleMouseClick(mousePosition, currentState);
                }
                else if (currentState == PLAY_MENU) {
                    playMenu.handleMouseClick(mousePosition, currentState);
                }
                else if (currentState == GAME_DEFAULT) {
                    sf::Text text("Playing Default Poker", font, 30);
                    text.setFillColor(sf::Color::White);
                    text.setPosition(50, 50);
                    window.draw(text);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        currentState = PLAY_MENU; // Quay lại Play Menu
                }
                else if (currentState == GAME_STUD) {
                    sf::Text text("Playing Stud Poker", font, 30);
                    text.setFillColor(sf::Color::White);
                    text.setPosition(50, 50);
                    window.draw(text);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        currentState = PLAY_MENU; // Quay lại Play Menu
                }
                else if (currentState == GAME_SUPER) {
                    sf::Text text("Playing Super Poker", font, 30);
                    text.setFillColor(sf::Color::White);
                    text.setPosition(50, 50);
                    window.draw(text);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        currentState = PLAY_MENU; // Quay lại Play Menu
                }
            }
        }
    }