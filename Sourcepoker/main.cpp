#include <gameObject.h>
#include <gameModes.h>
#include "main.h"


//void Games() {
    ///*std::cout << "0. Default 5 cards" << std::endl;
    //std::cout << "1. Texas Hold 'em" << std::endl;
    //std::cout << "2. Draw 5 Poker" << std::endl;
    //std::cout << "3. Stud Poker" << std::endl;*/
    //int choice; std::cout << "Enter a number to choose what to do: ";  std::cin >> choice;
//    int choice;
//    int numberOfPlayers, numberOfNPCs;
//    std::cout << "Enter the total number of players (Humans & AIs): "; std::cin >> numberOfPlayers;
//    std::cout << "Enter the amount of NPC: "; std::cin >> numberOfNPCs;
//    House house = new Table();
//    if (choice == 0) house.setTable(new Table(numberOfPlayers, numberOfNPCs));
//    if (choice == 3) house.setTable(new studTable(numberOfPlayers, numberOfNPCs));
//    if (choice == 2) house.setTable(new drawTable(numberOfPlayers, numberOfNPCs));
//    if (choice == 1) house.setTable(new texasTable(numberOfPlayers, numberOfNPCs));
//    
//    house.StartGame();
//}

int main() {
    //window   
    const int SCREEN_WIDTH = 1080;
    const int SCREEN_HEIGHT = 720;

    //title bar
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Poker Game"/*, sf::style::Titlebar | sf::Style::Close*/);
    sf::Image icon; //icon at title bar
    if (!icon.loadFromFile("Resources/images/icon.png")) {
        std::cerr << "Error loading icon image\n";
        return -1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //font 
    sf::Font font;
    if (!font.loadFromFile("Pangolin-Regular.ttf")) { // load font 
        std::cerr << "Error loading font\n";
    }

    //upload logo (at main menu)
    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("Resources/images/logo.png")) {
        std::cerr << "Error loading logo image\n";
        return -1;
    }

    sf::Sprite logoSprite;
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(SCREEN_WIDTH - logoTexture.getSize().x - 20, 50);

    GameState currentState = MAIN_MENU;

    //main menu
    Menu mainMenu(SCREEN_WIDTH, SCREEN_HEIGHT, { "Play", "Leaderboard", "Credit", "Exit" });

    //Play menu
    Menu playMenu(SCREEN_WIDTH, SCREEN_HEIGHT, { "Default", "Stud table" });

    PlayerSelection playerSelection(SCREEN_WIDTH, SCREEN_HEIGHT);
    PlayerInfoInput playerInfoInput(SCREEN_WIDTH, SCREEN_HEIGHT, 3); // Giả sử có 3 người chơi

    //game loop
    while (window.isOpen()) {
        //event polling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (currentState == MAIN_MENU) {
                    mainMenu.handleMouseHover(mousePosition);
                }
                else if (currentState == PLAY_MENU) {
                    playMenu.handleMouseHover(mousePosition);
                }
            }

            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (currentState == MAIN_MENU) {
                        mainMenu.handleMouseClick(mousePosition, currentState);
                    }
                    else if (currentState == PLAY_MENU) {
                        playMenu.handleMouseClick(mousePosition, currentState);
                    }
                    else if (currentState == PLAYER_SELECTION) {
                        playerSelection.handleMouseClick(mousePosition, currentState);
                        if (playerSelection.isContinueButtonPressed(mousePosition)) {
                            playerSelection.handleContinueButton(currentState);
                        }
                    }
                    else if (currentState == INPUT_PLAYER_INFO) {
                        playerInfoInput.handleMouseClick(mousePosition);
                        if (event.type == sf::Event::TextEntered) {
                            playerInfoInput.handleTextInput(event);
                        }
                    }
                    else if (currentState == GAME_DEFAULT) {
                        sf::Text text("Playing Default Poker", font, 30);
                        text.setFillColor(sf::Color::White);
                        text.setPosition(50, 50);
                        window.draw(text);
                        //add logic game here
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
                }
            }
            if (event.type == sf::Event::TextEntered && currentState == PLAYER_SELECTION) {
                playerSelection.handleTextInput(event);
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                currentState = MAIN_MENU; // return to main menu (when press esc)
        }
        else if (currentState == PLAYER_SELECTION) {
            playerSelection.render(window);
        }
        else if (currentState == INPUT_PLAYER_INFO) {
            playerSelection.render(window);
        }
        else if (currentState == GAME_DEFAULT) {
            //logic game here
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                currentState = MAIN_MENU;
        }
        else if (currentState == LEADERBOARD) {
            leaderboard().displaySFML(window, font);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                currentState = MAIN_MENU;
        }
        //else if (currentState == CREDIT) {
        //    showCredit(window);
        //    currentState = MAIN_MENU;  // Quay lại menu chính
        //}
        else if (currentState == EXIT) {
            window.close();
        }
        if (currentState == MAIN_MENU || currentState == PLAY_MENU)
            window.draw(logoSprite); // draw the logo only at main and play menu
        window.display(); //tell app that window is done drawing
    }

    //end of application

    /*while (true){
        std::cout << "Welcome to poker!" << std::endl;
        std::cout << "Please choose what to do" << std::endl;
        std::cout << "1. Play poker" << std::endl;
        std::cout << "2. view Leaderboard" << std::endl;
        std::cout << "3. Exit program" << std::endl;
        int choice; std::cout << "Enter a number to choose what to do: ";  std::cin >> choice;

        if (choice == 1) Games();
        if (choice == 2) leaderboard().display();
        if (choice == 3) return 0;
    }  */ 
    return 0;
}
