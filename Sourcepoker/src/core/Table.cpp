#include <gameObject.h>
#include <iostream>
#include <algorithm> // For std::sort and std::greater
#include <numeric>   // For std::accumulate

// Constructor
Table::Table(sf::RenderWindow& window, sf::Font& font, std::vector<Player>& players) : window(window), font(font), players(players){}

// Deals five cards to each player
void Table::dealCardsToPlayers() {
    for (Player& player : players) {
        player.cardToHand(deck, 5, true);  // Deal 5 cards per player
    }
}

// Gets the current game mode name
std::string Table::getModeName() const {
    return "Default 5";
}

// Deals the "flop" (first three community cards)
void Table::dealFlop() {
    cardToHand(deck, 3, true);  // Deal 3 cards to the table
}

// Displays each player's hand
void Table::showPlayersHands() const {
    int numPlayers = players.size();
    int xOffset = 200;
    std::cout << "showing card..." << numPlayers << std::endl;
    int yOffset = 200;

    sf::Font font;
    if (!font.loadFromFile("Pangolin-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;  // Dừng chương trình nếu không load được font
    }

    // Vẽ bộ bài cho mỗi người chơi
    for (int i = 0; i < numPlayers; ++i) {
        // Vẽ bộ bài của người chơi
        players[i].showCards(window, xOffset, yOffset);

        // Vẽ tên người chơi
        sf::Text playerNameText;
        playerNameText.setFont(font);
        playerNameText.setString(players[i].getUsername());
        playerNameText.setCharacterSize(24);
        playerNameText.setFillColor(sf::Color::Black);
        playerNameText.setPosition(xOffset, yOffset - 30);  // Vị trí tên người chơi

        // Vẽ tên người chơi
        window.draw(playerNameText);

        // Cập nhật xOffset để vẽ bộ bài cho người chơi tiếp theo
        yOffset += 130; // Khoảng cách giữa các người chơi, có thể điều chỉnh nếu cần
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
        //Add players bet to pot
        pot += players[i].bet;
        // Folded players loses by default. 
        if (players[i].folded) losersIndexes.push_back(i);
        else {
            winnersIndexes.push_back(i);
            for (int j = i + 1; j < count; ++j) {
                //Add players bet to pot
                pot += players[j].bet;

                // Handle ties when player not folded and have a hand as strong as the first detected winner
                if (!players[j].folded && players[j] == players[i]) winnersIndexes.push_back(j);
                else losersIndexes.push_back(j); // Add to losers index 
            }
            break;
        }
    }
    std::cout << "Loser: " << std::endl;
    // Update game history and display non-winning players
    for (const int& i : losersIndexes) {
        std::cout << players[i].getUsername() << std::endl;
        players[i].updateGameHistory();
    }

    // Update game history and display winning players
    std::string winnerNames;
    std::cout << "Winner: " << std::endl;
    for (const int& i : winnersIndexes) {
        std::cout << players[i].getUsername() << std::endl;
        winnerNames += players[i].getUsername() + "\n";

        players[i].updateGameHistory(true, pot / winnersIndexes.size());
    }

    // Announce the winner
    int handRank = Evaluator(players[winnersIndexes[0]].getHand()).evaluateHandRank();
    std::cout << "Winning hand rank: "
        << Evaluator().rankToString(handRank) << std::endl;
    winnerHandRank = Evaluator().rankToString(handRank);
}

void Table::clearTable() {
    for (Player& player : players) {
        player.clearHand();
    }
}

void Table::processPlayerAction(int& highestBet, int currentPlayerIndex, int& raiseIndex) {
    int yOffset = 100;
    int xOffset = 100;
    players[currentPlayerIndex].showCards(window, xOffset, yOffset);

    int choice;
    std::cout << "Player " << players[currentPlayerIndex].getUsername() << ", choose your action (1=Check/Call, 2=Fold, 3=Raise): ";
    std::cin >> choice;

    std::cout << "Current blind: " << highestBet << std::endl;
    std::cout << "Your current bet: " << players[currentPlayerIndex].bet << std::endl;

    switch (choice) {
    case 1: // Check/Call
        // Matches the player's bet to the current highestBet (Blind)
        if (players[currentPlayerIndex].bet < highestBet) {
            players[currentPlayerIndex].bet = highestBet;  // Player calls
        }
        break;

    case 2: // Fold
        // Exclude players from future action round
        players[currentPlayerIndex].folded = true; // Player folds
        break;

    case 3: // Raise
        // Increase player's bet to higherBet and change highest bet accordingly
        
        int raiseAmount;
        std::cout << "Enter raise amount: " << std::endl;
        std::cin >> raiseAmount;
        if (raiseAmount > highestBet) {
            players[currentPlayerIndex].bet += raiseAmount;  // Player raises
            highestBet = players[currentPlayerIndex].bet;// Update the highest bet
            raiseIndex = currentPlayerIndex;// Also note where the most recent raise to know when to stop the round
        }
        else {
            std::cout << "Raise amount must be higher than the current bet.\n";
        }
        break;

    default:
        // Handle invalid input
        std::cout << "Invalid choice. Try again.\n";
        processPlayerAction(highestBet, currentPlayerIndex, raiseIndex);  // Retry on invalid input
        break;
    }
}

void Table::bettingRound(int& highestBet) {
    // A circular loop that only stop when all players have either call or folded
    int index = 0, raiseIndex = 0;
    do {
        while (players[index].folded)
            index = (index + 1) % players.size();

        processPlayerAction(highestBet, index, raiseIndex);

        index = (index + 1) % players.size();

    } while (index != raiseIndex);
}


// Runs the game loop, dealing cards, displaying hands, and determining the winner
void Table::startGame() {
    //window.clear(sf::Color::Green);
        createDeck();           // Prepare a new deck
        clearTable();           // Clear previous hands
        dealCardsToPlayers();  // Deal new hands
        drawTable(window);
        drawCard(window);
       
        int highestBet = 10;

        bettingRound(highestBet);

        // Draw each player's hand
        std::cout << "Players' hands:" << std::endl;
        showPlayersHands();

        // Determine and display the winner
        determineWinner();
        dialogBox();
        
        window.display();
}

void Table::addPlayer(const std::string& playerName) {
    players.push_back(Player(playerName));  // Giả sử Player có constructor nhận tên người chơi
}

void Table::goToMainMenu() {
    currentState = MAIN_MENU;
}
void Table::dialogBox() {
    // Create the dialog box to show the winner
    sf::Font font;
    if (!font.loadFromFile("Pangolin-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;  // Dừng chương trình nếu không load được font
    }
    sf::RectangleShape dialogBox(sf::Vector2f(400, 200));  // Hộp thoại có kích thước 400x200
    dialogBox.setFillColor(sf::Color(0, 0, 0, 200));  // Nền đen với độ trong suốt
    dialogBox.setOutlineColor(sf::Color::White);  // Viền trắng
    dialogBox.setOutlineThickness(5);  // Độ dày viền
    dialogBox.setPosition(150, 10);  // Vị trí hộp thoại

    // Tạo đối tượng sf::Text để hiển thị tên người chiến thắng
    sf::Text winnerText;
    winnerText.setFont(font);
    winnerText.setString("Winner: " + players[0].getUsername());  // Dùng tên người chiến thắng
    winnerText.setCharacterSize(20);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setPosition(160, 20);  // Vị trí của văn bản trong hộp thoại

    std::cout << "winner: " + players[0].getUsername() << std::endl;

    sf::Text handRankText;
    handRankText.setFont(font);
    handRankText.setString("Winning hand rank: " + winnerHandRank);
    handRankText.setCharacterSize(20);
    handRankText.setFillColor(sf::Color::White);
    handRankText.setPosition(160, 40);

    std::cout << "wining hand rank: " + winnerHandRank << std::endl;
    // create "another round " and "exit to main menu"
    sf::Text anotherRoundText;
    anotherRoundText.setFont(font);
    anotherRoundText.setString("Another Round? (Press Enter)");
    anotherRoundText.setCharacterSize(20);
    anotherRoundText.setFillColor(sf::Color::Yellow);
    anotherRoundText.setPosition(160, 100);  // Vị trí của "Another Round" trong hộp thoại

    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("Exit! (Press ESC)");
    exitText.setCharacterSize(20);
    exitText.setFillColor(sf::Color::Yellow);
    exitText.setPosition(160, 150);  // Vị trí của "Exit" trong hộp thoại

    // Vẽ hộp thoại lên cửa sổ
    window.draw(dialogBox);
    window.draw(winnerText);
    window.draw(handRankText);
    window.draw(anotherRoundText);
    window.draw(exitText);

    window.display();
}

//draw table
void Table::drawTable(sf::RenderWindow& window) {
    sf::Texture tableTexture;
    if (!tableTexture.loadFromFile("Resources/images/table.jpg")) {
        std::cerr << "Error loading table image" << std::endl;
        return;
    }
    sf::Sprite tableSprite(tableTexture);
    tableSprite.setScale(2.0f, 2.0f);

    // Tính toán vị trí để ảnh ở chính giữa cửa sổ
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    // Lấy kích thước ảnh sau khi phóng to
    float textureWidth = tableTexture.getSize().x * 2.0f;
    float textureHeight = tableTexture.getSize().y * 2.0f;

    // Đặt ảnh vào chính giữa cửa sổ
    tableSprite.setPosition((windowWidth - textureWidth) / 2.0f, (windowHeight - textureHeight) / 2.0f);
    window.draw(tableSprite);
}

//draw player's cards
void Table::drawCard(sf::RenderWindow& window) {

    if (players.empty()) {
        std::cerr << "Error: Player list is empty!" << std::endl;
        return; // Hoặc xử lý lỗi
    }

    std::cout << "Player list size: " << players.size() << std::endl;

    for (int i = 0; i < players.size(); ++i) {
        const Player& player = players[i];

        std::cout << "Player " << players[i].getUsername() << "'s hand size: " << players[i].getHand().size() << std::endl;

        int cardOffset = 0; //to move card on the window

        for (int j = 0; j < players[i].getHand().size(); ++j) {
            std::string cardName = players[i].getHand()[j].toString();
            sf::Texture cardTexture;
            if (!cardTexture.loadFromFile("Resources/cards/" + cardName + ".png")) {
                std::cerr << "Error loading card image: " << cardName << std::endl;
                continue;
            }

            sf::Sprite cardSprite(cardTexture);
            cardSprite.setPosition(50 + cardOffset, 200 + i * 150); // position of card;

            window.draw(cardSprite);
            cardOffset += 60;
        }
    }
}