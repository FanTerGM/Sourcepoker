#include <gameObject.h>
#include <iostream>
#include <algorithm> // For std::sort and std::greater
#include <numeric>   // For std::accumulate

/* --- Table Class Definitions ---
   Manages the poker table, players, and game operations. */

   // Default constructor initializes table with one player and one NPC
Table::Table(sf::RenderWindow& window, sf::Font& font) : numberOfPlayers(0), numberOfNPCs(1), window(window){
    populateTable();

}

// Constructor allowing specification of player and NPC counts
Table::Table(sf::RenderWindow& window, int playerCount, int npcCount) : numberOfPlayers(playerCount), numberOfNPCs(npcCount), window(window) {
    populateTable();
}

// Adds players and NPCs to the table
void Table::populateTable() {
    // Populate human players
    for (int i = 0; i < numberOfPlayers; i++) {
        std::string playerName;
        std::cout << "Enter Player " << (i + 1) << "'s name: ";
        std::cin >> playerName;
        Player player = player.loadProfile(playerName);  // Load or create player profile
        players.push_back(player);
    }

    // Populate AI players
    for (int i = 0; i < numberOfNPCs; i++) {
        std::string aiName = "AI_" + std::to_string(i + 1);
        players.emplace_back(aiName);  // Automatically creates an AI player
    }
}

// Deals five cards to each player
void Table::dealCardsToPlayers() {
    for (Player& player : players) {
        player.cardToHand(deck, 5, true);  // Deal 5 cards per player
    }
}

// Gets the current game mode name
std::string Table::getModeName() const {
    return "Default5";
}

// Deals the "flop" (first three community cards)
void Table::dealFlop() {
    cardToHand(deck, 3, true);  // Deal 3 cards to the table
}

// Displays each player's hand
void Table::showPlayersHands() const {
    for (const Player& player : players) {
        std::cout << player.getUsername() << "'s hand:" << std::endl;
        player.showCards(window);
    }
}

// Initializes a new deck
void Table::createDeck() {
    deck = Deck();
}

// Determines the winner among players and updates game history
void Table::determineWinner() {
    // Sort players by hand strength in descending order
    std::sort(players.begin(), players.end(), std::greater<Player>());

    int count = players.size();
    int pot = 0;

    std::vector<int> winnersIndexes;
    std::vector<int> losersIndexes;

    for (int i = 0; i < count; ++i) {
        pot += players[i].bet;
        if (players[i].folded) losersIndexes.push_back(i);
        else {
            winnersIndexes.push_back(i);
            for (int j = i + 1; j < count; ++j) {
                pot += players[j].bet;
                if (!players[j].folded && players[j] == players[i]) winnersIndexes.push_back(j);
                else losersIndexes.push_back(j);
            }
            break;
        }
    }
    std::cout << "Loser: " << std::endl;
    // Update game history for non-winning players
    for (const int& i : losersIndexes) {
        std::cout << players[i].getUsername() << std::endl;
        players[i].updateGameHistory();
    }

    std::string winnerNames;
    std::cout << "Winner: " << std::endl;
    for (const int& i : winnersIndexes) {
        std::cout << players[i].getUsername() << std::endl;
        winnerNames += players[i].getUsername() + "\n";
        // Create the dialog box to show the winner
        sf::RectangleShape dialogBox(sf::Vector2f(400, 200));  // Hộp thoại có kích thước 400x200
        dialogBox.setFillColor(sf::Color(0, 0, 0, 200));  // Nền đen với độ trong suốt
        dialogBox.setOutlineColor(sf::Color::White);  // Viền trắng
        dialogBox.setOutlineThickness(5);  // Độ dày viền
        dialogBox.setPosition(150, 100);  // Vị trí hộp thoại

        // Tạo đối tượng sf::Text để hiển thị tên người chiến thắng
        sf::Text winnerText;
        winnerText.setFont(*font);
        winnerText.setString("Winner: \n" + winnerNames);  // Dùng tên người chiến thắng
        winnerText.setCharacterSize(24);
        winnerText.setFillColor(sf::Color::White);
        winnerText.setPosition(160, 120);  // Vị trí của văn bản trong hộp thoại

        // create "another round " and "exit to main menu"
        sf::Text anotherRoundText;
        anotherRoundText.setFont(*font);
        anotherRoundText.setString("Another Round");
        anotherRoundText.setCharacterSize(20);
        anotherRoundText.setFillColor(sf::Color::White);
        anotherRoundText.setPosition(160, 180);  // Vị trí của "Another Round" trong hộp thoại

        sf::Text exitText;
        exitText.setFont(*font);
        exitText.setString("Exit (Back to Main Menu)");
        exitText.setCharacterSize(20);
        exitText.setFillColor(sf::Color::White);
        exitText.setPosition(160, 220);  // Vị trí của "Exit" trong hộp thoại

        // Vẽ hộp thoại lên cửa sổ
        window.draw(dialogBox);
        window.draw(winnerText);
        window.draw(anotherRoundText);
        window.draw(exitText);

        // Cập nhật lại màn hình
        window.display();

        while (!continuePlaying) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    // Xử lý click chuột
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Kiểm tra xem người chơi click vào "Another Round"
                    if (anotherRoundText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        continuePlaying = true;  // Người chơi chọn "Another Round"
                    }
                    // Kiểm tra xem người chơi click vào "Exit"
                    if (exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        continuePlaying = false;  // Người chơi chọn "Exit"
                    }
                }
            }
        }
        players[i].updateGameHistory(true, pot / winnersIndexes.size());
        if (!continuePlaying) {
            //goToMainMenu();// viết hàm chuyển tới mainmenu
        }
    }

    // Announce the winner
    int handRank = Evaluator(players[0].getHand()).evaluateHandRank();
    std::cout << "Winning hand rank: "
        << Evaluator().rankToString(handRank) << std::endl;
}

void Table::clearTable() {
    for (Player& player : players) {
        player.clearHand();
    }
}

void Table::processPlayerAction(int& highestBet, int currentPlayerIndex, int& raiseIndex) {
    players[currentPlayerIndex].showCards(window);

    int choice;
    std::cout << "Player " << players[currentPlayerIndex].getUsername() << ", choose your action (1=Check/Call, 2=Fold, 3=Raise): ";
    std::cin >> choice;

    std::cout << "Current blind: " << highestBet << std::endl;
    std::cout << "Your current bet: " << players[currentPlayerIndex].bet << std::endl;

    switch (choice) {
    case 1: // Check/Call
        if (players[currentPlayerIndex].bet < highestBet) {
            players[currentPlayerIndex].bet = highestBet;  // Player calls
        }
        break;

    case 2: // Fold
        players[currentPlayerIndex].folded = true; // Player folds
        break;

    case 3: // Raise
        int raiseAmount;
        std::cout << "Enter raise amount: " << std::endl;
        std::cin >> raiseAmount;
        if (raiseAmount > highestBet) {
            players[currentPlayerIndex].bet += raiseAmount;  // Player raises
            highestBet = players[currentPlayerIndex].bet;
            raiseIndex = currentPlayerIndex;// Update the highest bet
        }
        else {
            std::cout << "Raise amount must be higher than the current bet.\n";
        }
        break;

    default:
        std::cout << "Invalid choice. Try again.\n";
        processPlayerAction(highestBet, currentPlayerIndex, raiseIndex);  // Retry on invalid input
        break;
    }
}


// Runs the game loop, dealing cards, displaying hands, and determining the winner
void Table::startGame() {
    continuePlaying = false;
    do {
        createDeck();           // Prepare a new deck
        clearTable();           // Clear previous hands
        dealCardsToPlayers(); // Deal new hands


        int index = 0, raiseAt = 0;
        int highestBet = 10;

        for (Player& player : players) {
            player.bet = highestBet;
        }

        do {
            while (players[index].folded)
                index = (index + 1) % players.size();

            processPlayerAction(highestBet, index, raiseAt);

            index = (index + 1) % players.size();

        } while (index != raiseAt);

        //draw the table
        sf::Texture tableTexture;
        if (!tableTexture.loadFromFile("Resources/images/table.jpg")) {
            std::cerr << "Error loading table image" << std::endl;
            return;
        }
        sf::Sprite tableSprite(tableTexture);
        tableSprite.setPosition(0, 0); //position of table

        window.draw(tableSprite);
        // Draw each player's hand
        std::cout << "Players' hands:" << std::endl;
        showPlayersHands();

        // Determine and display the winner
        determineWinner();
        
    } while (continuePlaying);
}

void Table::addPlayer(const std::string& playerName) {
    players.push_back(Player(playerName));  // Giả sử Player có constructor nhận tên người chơi
}