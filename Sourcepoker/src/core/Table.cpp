#include <gameObject.h>
#include <iostream>
#include <algorithm> // For std::sort and std::greater
#include <numeric>   // For std::accumulate

DialogState currentDialogState = MAIN_DIALOG;


// Constructor
Table::Table(sf::RenderWindow& window, sf::Font& font, std::vector<Player> players) : window(window), font(font), players(players){}

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
    const int SCREEN_WIDTH = 1080;
    const int SCREEN_HEIGHT = 720;

    // Xử lý nhập liệu
    std::string raiseAmountStr = "";  // String để chứa số tiền raise
    bool validInput = false;
    while (!validInput) {
        window.clear();
        sf::Event event;
        players[currentPlayerIndex].showCards(window, xOffset, yOffset);
        if (currentDialogState == MAIN_DIALOG) {
            // Tạo một thông điệp trong hộp thoại
            sf::RectangleShape dialogBox(sf::Vector2f(400.f, 200.f));
            dialogBox.setFillColor(sf::Color(0, 0, 0, 180)); // Màu nền hộp thoại bán trong suốt
            dialogBox.setPosition(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100);
            window.draw(dialogBox);

            // Chữ hiển thị tên người chơi và các lựa chọn
            sf::Text playerTurnText;
            playerTurnText.setFont(font);
            playerTurnText.setString(players[currentPlayerIndex].getUsername() + "'s turn");
            playerTurnText.setCharacterSize(24);
            playerTurnText.setFillColor(sf::Color::White);
            playerTurnText.setPosition(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 80);
            window.draw(playerTurnText);

            // Các thông tin về tiền cược
            sf::Text currentBetText;
            currentBetText.setFont(font);
            currentBetText.setString("Current Blind: " + std::to_string(highestBet));
            currentBetText.setCharacterSize(18);
            currentBetText.setFillColor(sf::Color::White);
            currentBetText.setPosition(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 50);
            window.draw(currentBetText);

            sf::Text playerBetText;
            playerBetText.setFont(font);
            playerBetText.setString("Your Bet: " + std::to_string(players[currentPlayerIndex].bet));
            playerBetText.setCharacterSize(18);
            playerBetText.setFillColor(sf::Color::White);
            playerBetText.setPosition(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 20);
            window.draw(playerBetText);

            // Các lựa chọn hành động
            sf::Text actionsText;
            actionsText.setFont(font);
            actionsText.setString("Press 1 to Check/Call\nPress 2 to Fold\nPress 3 to Raise");
            actionsText.setCharacterSize(18);
            actionsText.setFillColor(sf::Color::White);
            actionsText.setPosition(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 + 20);
            window.draw(actionsText);

            // Hiển thị cửa sổ
            window.display();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Num1) {
                        // Check/Call: Đặt cược để match với highestBet
                        if (players[currentPlayerIndex].bet < highestBet) {
                            players[currentPlayerIndex].bet = highestBet;  // Player calls
                        }
                        std::cout << "Check" << std::endl;
                        validInput = true;
                        break;
                    }
                    else if (event.key.code == sf::Keyboard::Num2) {
                        // Fold: Người chơi bỏ cuộc
                        players[currentPlayerIndex].folded = true;
                        validInput = true;
                        std::cout << "dddddd" << std::endl;
                        break;
                    }
                    else if (event.key.code == sf::Keyboard::Num3) {
                        currentDialogState = RAISE_DIALOG;
                        std::cout << "efafa" << std::endl;
                        break;
                    }
                }
            }
            window.clear();
        }
        else if (currentDialogState == RAISE_DIALOG) {

            //hiển thị hộp thoại raise bet
            sf::RectangleShape raiseDialogBox(sf::Vector2f(400.f, 150.f));
            raiseDialogBox.setFillColor(sf::Color(0, 0, 0, 180));
            raiseDialogBox.setPosition(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 150);
            window.draw(raiseDialogBox);

            // Hiển thị hộp thoại yêu cầu nhập tiền cược
            sf::Text raisePrompt;
            raisePrompt.setFont(font);
            raisePrompt.setString("Enter raise amount: ");
            raisePrompt.setCharacterSize(18);
            raisePrompt.setFillColor(sf::Color::White);
            raisePrompt.setPosition(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 + 80);
            window.draw(raisePrompt);

            sf::Text inputText;
            inputText.setFont(font);
            inputText.setString(raiseAmountStr);  // Hiển thị số tiền raise nhập vào
            inputText.setCharacterSize(18);
            inputText.setFillColor(sf::Color::White);
            inputText.setPosition(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 + 110);
            window.draw(inputText);

            players[currentPlayerIndex].showCards(window, xOffset, yOffset);
            window.display();

            bool validRaise = false;
            while (!validRaise) {
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode == 13) { // == pressed enter
                            if (!raiseAmountStr.empty()) {
                                int raiseAmount = std::stoi(raiseAmountStr);
                                if (raiseAmount > highestBet) {
                                    players[currentPlayerIndex].bet += raiseAmount;  // Player raises
                                    highestBet = players[currentPlayerIndex].bet;// Update the highest bet
                                    raiseIndex = currentPlayerIndex;// Also note where the most recent raise to know when to stop the round
                                    validRaise = true;
                                    validInput = true;
                                    break;
                                }
                            }
                            else {
                                std::cout << "Raise amount must be higher than the current bet.\n";
                            }
                        }
                        else if (event.text.unicode == 8) { // ==pressed backspace
                            if (!raiseAmountStr.empty()) {
                                raiseAmountStr.pop_back(); // delete the last digit
                            }
                        }
                        else if (event.text.unicode >= 48 && event.text.unicode <= 57) { // enter 0 -> 9
                            raiseAmountStr += static_cast<char>(event.text.unicode);
                        }
                    }
                }
                inputText.setString(raiseAmountStr);
                window.clear();
                window.draw(raiseDialogBox);
                window.draw(raisePrompt);
                window.draw(inputText);
                players[currentPlayerIndex].showCards(window, xOffset, yOffset);
                window.display();
            }
            currentDialogState = MAIN_DIALOG;
        }
    }
    window.clear();
}
    //int choice;
    //std::cout << "Player " << players[currentPlayerIndex].getUsername() << ", choose your action (1=Check/Call, 2=Fold, 3=Raise): ";
    //std::cin >> choice;

    //std::cout << "Current blind: " << highestBet << std::endl;
    //std::cout << "Your current bet: " << players[currentPlayerIndex].bet << std::endl;

    //switch (choice) {
    //case 1: // Check/Call
    //    // Matches the player's bet to the current highestBet (Blind)
    //    if (players[currentPlayerIndex].bet < highestBet) {
    //        players[currentPlayerIndex].bet = highestBet;  // Player calls
    //    }
    //    break;

    //case 2: // Fold
    //    // Exclude players from future action round
    //    players[currentPlayerIndex].folded = true; // Player folds
    //    break;

    //case 3: // Raise
    //    // Increase player's bet to higherBet and change highest bet accordingly
    //    
    //    int raiseAmount;
    //    std::cout << "Enter raise amount: " << std::endl;
    //    std::cin >> raiseAmount;
    //    if (raiseAmount > highestBet) {
    //        players[currentPlayerIndex].bet += raiseAmount;  // Player raises
    //        highestBet = players[currentPlayerIndex].bet;// Update the highest bet
    //        raiseIndex = currentPlayerIndex;// Also note where the most recent raise to know when to stop the round
    //    }
    //    else {
    //        std::cout << "Raise amount must be higher than the current bet.\n";
    //    }
    //    break;

    //default:
    //    // Handle invalid input
    //    std::cout << "Invalid choice. Try again.\n";
    //    processPlayerAction(highestBet, currentPlayerIndex, raiseIndex);  // Retry on invalid input
    //    break;
    //}

void Table::bettingRound(int& highestBet) {
    // A circular loop that only stop when all players have either call or folded
    int index = 0, raiseIndex = 0;
    do {
        while (players[index].folded) {
            index = (index + 1) % (players.size());
        }
        
        processPlayerAction(highestBet, index, raiseIndex);

        index = (index + 1) % players.size();

    } while (index != raiseIndex);
}


// Runs the game loop, dealing cards, displaying hands, and determining the winner
void Table::startGame() {
    //window.clear(sf::Color::Green)
    createDeck();// Prepare a new deck
    clearTable();// Clear previous hands
    dealCardsToPlayers();// Deal new hand

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
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("Pangolin-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;  // Dừng chương trình nếu không load được font
    }
    sf::RectangleShape dialogBox(sf::Vector2f(400, 100));  // Hộp thoại có kích thước 400x200
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
    handRankText.setPosition(160, 45);

    std::cout << "wining hand rank: " + winnerHandRank << std::endl;
    // create "another round " and "exit to main menu"
    sf::Text anotherRoundText;
    anotherRoundText.setFont(font);
    anotherRoundText.setString("Press Any Key to back to Play Menu...");
    anotherRoundText.setCharacterSize(20);
    anotherRoundText.setFillColor(sf::Color::Yellow);
    anotherRoundText.setPosition(160, 80);  // Vị trí của "Another Round" trong hộp thoại


    // Vẽ hộp thoại lên cửa sổ
    window.draw(dialogBox);
    window.draw(winnerText);
    window.draw(handRankText);
    window.draw(anotherRoundText);
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