#include <gameObject.h>
#include <gameModes.h>

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

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Poker Game"); //can add ,sf::style::Titlebar | sf::Style::Close

    //Menu menu(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //game loop
    while (window.isOpen()) {
        //event polling
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                    //case sf::Event::
            }
        }
        //update

        //render
        window.clear(); // clear old frames

        //draw the game

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
