#include <gameObject.h>
#include <gameModes.h>
#include "main.h"

void ShowLeaderboard(sf::RenderWindow &window);
void ShowCredit(sf::RenderWindow &window);

void Games() {
    std::cout << "0. Default 5 cards" << std::endl;
    std::cout << "1. Texas Hold 'em" << std::endl;
    std::cout << "2. Draw 5 Poker" << std::endl;
    std::cout << "3. Stud Poker" << std::endl;
    int choice; std::cout << "Enter a number to choose what to do: ";  std::cin >> choice;

    int numberOfPlayers, numberOfNPCs;
    std::cout << "Enter the totabl number of players (Humans & AIs): "; std::cin >> numberOfPlayers;
    std::cout << "Enter the amount of NPC: "; std::cin >> numberOfNPCs;
    House house = new Table();
    if (choice == 0) house.setTable(new Table(numberOfPlayers, numberOfNPCs));
    if (choice == 3) house.setTable(new studTable(numberOfPlayers, numberOfNPCs));
    if (choice == 2) house.setTable(new drawTable(numberOfPlayers, numberOfNPCs));
    if (choice == 1) house.setTable(new texasTable(numberOfPlayers, numberOfNPCs));
    
    house.StartGame();
}

int main() {
    //window   
    const int SCREEN_WIDTH = 1080;
    const int SCREEN_HEIGHT = 720;
    
    //add logo game
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Poker Game"); //can add ,sf::style::Titlebar | sf::Style::Close

    GameState currentState = MAIN_MENU;

    //main menu
    Menu mainMenu(SCREEN_WIDTH, SCREEN_HEIGHT, { "Play", "Leaderboard", "Credit", "Exit" });
    
    //Play menu
    Menu playMenu(SCREEN_WIDTH, SCREEN_HEIGHT, { "Default", "Draw Table", "Stud table" });

    
    //game loop
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
                }
            }
        }
        //update

        //render
        window.clear(sf::Color::Black); // clear old frames

        if (currentState == MAIN_MENU) {
            mainMenu.draw(window);
        }
        else if (currentState == PLAY_MENU) {
            playMenu.draw(window);
        }
        //else if (currentState == LEADERBOARD) {
        //    showLeaderboard(window);
        //    currentState = MAIN_MENU;  // Quay lại menu chính
        //}
        //else if (currentState == CREDIT) {
        //    showCredit(window);
        //    currentState = MAIN_MENU;  // Quay lại menu chính
        //}
        else if (currentState == EXIT) {
            window.close();
        }

        window.display(); //tell app that window is done drawing
    }

    //end of application

 /*   while (true){
        std::cout << "Welcome to poker!" << std::endl;
        std::cout << "Please choose what to do" << std::endl;
        std::cout << "1. Play poker" << std::endl;
        std::cout << "2. view Leaderboard" << std::endl;
        std::cout << "3. Exit program" << std::endl;
        int choice; std::cout << "Enter a number to choose what to do: ";  std::cin >> choice;

        if (choice == 1) Games();
        if (choice == 2) leaderboard().display();
        if (choice == 3) return 0;
    }   */
    return 0;
}
