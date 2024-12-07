#include "../headers/visual/PlayerInfoInput.h"
#include "../headers/game/GameState.h"
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <algorithm> //for std::max_element


GameState currentState = INPUT_PLAYER_INFO;

PlayerInfoInput::PlayerInfoInput() : numPlayers(1), numNPCs(1), activePlayerIndex(-1) {}

void PlayerInfoInput::setPlayerNPCs(int _numPlayers, int _numNPCs){
    this->numPlayers = _numPlayers;
    this->numNPCs = _numNPCs;

    font.loadFromFile("Pangolin-Regular.ttf");

    //Khởi tạo văn bản yêu cầu nhập tên người chơi
    playerNameText.setFont(font);
    playerNameText.setString("Enter Player Names:");
    playerNameText.setCharacterSize(30);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(50.f, 50.f);

    // Tạo các ô nhập tên người chơi
    playerNameBoxes.push_back(sf::RectangleShape(sf::Vector2f(200.f, 40.f)));
    initializePlayerList();
    

    // Khởi tạo nút "Continue"
    continueButton.setSize(sf::Vector2f(200.f, 50.f));
    continueButton.setPosition(550.f, 300.f);
    continueButton.setFillColor(sf::Color::Green);

    // Nút "Continue" - Văn bản
    continueText.setFont(font);
    continueText.setString("Play Menu");
    continueText.setCharacterSize(24);
    continueText.setFillColor(sf::Color::White);
    continueText.setPosition(610.f, 310.f);

    // Khởi tạo thông báo lỗi (nếu có)
    errorText.setFont(font);
    errorText.setCharacterSize(24);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(50.f, 250.f);

    // Căn giữa chữ "Play Menu" trong nút
    sf::FloatRect textRect = continueText.getLocalBounds();
    continueText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    continueText.setPosition(continueButton.getPosition().x + continueButton.getSize().x / 2.0f,
    continueButton.getPosition().y + continueButton.getSize().y / 2.0f);
}

void PlayerInfoInput::loadPlayerListFromFile(const std::string& directory) {
    std::filesystem::create_directory(directory);
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".json") {
            std::string playerName = entry.path().stem().string();
            playerList.push_back(playerName); // Lưu các tên người chơi vào danh sách
        }
    }
}

void PlayerInfoInput::savePlayerNameToFile(const std::string& playerName, const std::string& directory) {
    Player newPlayer(playerName);
    newPlayer.saveProfile(directory);  // Lưu profile người chơi vào file
}

void PlayerInfoInput::initializePlayerList() {
    // Khi bắt đầu, yêu cầu người dùng nhập tên người chơi
    for (int i = 0; i < numPlayers; ++i) {
        playerInputs.push_back("");  // Khởi tạo một ô nhập tên cho mỗi người chơi
        playerNameBoxes.push_back(sf::RectangleShape(sf::Vector2f(200.f, 40.f))); // Tạo thêm ô nhập tên cho người chơi
        playerNameBoxes[i].setPosition(70.f, 100.f + i * 60.f);  // Cập nhật vị trí của các ô nhập tên
        playerNameBoxes[i].setFillColor(sf::Color::White);
        playerNameBoxes[i].setOutlineThickness(2.f);
        playerNameBoxes[i].setOutlineColor(sf::Color::White);
    }
}

void PlayerInfoInput::render(sf::RenderWindow& window) {
    // Hiển thị tên người chơi, thông báo lỗi nếu cần
    for (int i = 0; i < numPlayers; ++i) {
        // Vẽ Text cho tên người chơi
        playerNameText.setString("Player " + std::to_string(i + 1) + ": ");
        playerNameText.setPosition(100, 100 + i * 80);
        window.draw(playerNameText);

        // Vẽ Text Box để nhập tên
        playerNameBoxes[i].setPosition(260, 100 + i * 80);
        window.draw(playerNameBoxes[i]);

        // Hiển thị tên người chơi đã nhập (hoặc ô trống nếu chưa nhập)
        sf::Text playerNameDisplay(playerInputs[i], font, 30);
        playerNameDisplay.setFillColor(sf::Color::Black);
        playerNameDisplay.setPosition(260, 100 + i * 80);
        window.draw(playerNameDisplay);
    }

    window.draw(continueButton);
    window.draw(continueText);

    if (!errorText.getString().isEmpty()) {
        window.draw(errorText);
    }
}


void PlayerInfoInput::handleMouseClick(const sf::Vector2i& mousePosition, GameState &currentState) {
    for (int i = 0; i < playerNameBoxes.size(); ++i) {
        if (playerNameBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
            isPlayerNameTextBoxSelected = true;  // Đánh dấu là chọn ô nhập liệu
            activePlayerIndex = i;  // Lưu lại chỉ mục của người chơi được chọn
        }
    }
    if (continueButton.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
        // Kiểm tra xem tất cả người chơi đã nhập tên chưa
        if (areAllPlayersNamesEntered()) {
                std::cout << "Game started!" << std::endl;
                for (const auto& player : players) {
                    // Ví dụ: Lưu player vào một tệp tin hoặc cập nhật thông tin người chơi.
                    player.saveProfile("player_data/"); // Nếu muốn lưu vào thư mục player_data
                }
                currentState = PLAY_MENU;  // Chuyển đến menu chọn chế độ chơi
                std::cout << "in handleclick : " << currentState << std::endl;
            }
        else {
            errorText.setString("Please enter names for all players.");
            errorText.setPosition(100, 200 + numPlayers * 60);  // Hiển thị thông báo lỗi
        }
    }
}

bool PlayerInfoInput::areAllPlayersNamesEntered() {
    for (int i = 0; i < numPlayers; ++i) {
        std::cout << "player " << i << ": " << playerInputs[i] << std::endl;
        if (playerInputs[i].empty()) {
            return false;
        }
    }
    return true;
}
void PlayerInfoInput::handleTextInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {  // Kiểm tra xem ký tự có hợp lệ không
            // Kiểm tra nếu là phím Backspace (mã 8)
            if (event.text.unicode == 8) {
                if (isPlayerNameTextBoxSelected && !playerInputs[activePlayerIndex].empty()) {
                    playerInputs[activePlayerIndex].pop_back();  // Xóa ký tự cuối cùng
                }
            }
            // Chỉ chấp nhận ký tự chữ 
            else {
                char inputChar = static_cast<char>(event.text.unicode);
                if (isPlayerNameTextBoxSelected) {
                    playerInputs[activePlayerIndex] += inputChar;  // Thêm ký tự vào tên của người chơi đã chọn
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            std::cout << "pressed Enter~" << std::endl;
            // Kiểm tra xem tên đã tồn tại chưa khi bấm enter
            std::string playerName = playerInputs[activePlayerIndex];
            std::cout << playerName << std::endl;
            removeTrailingSpaces(playerName);
            Player player = Player::loadProfile(playerName, "Resources/playerInfo/");

            // Nếu profile người chơi đã tồn tại, sẽ không tạo thêm player mới
            if (player.getUsername() == playerName) {
                std::cout << "Active Player Index Rightnow = " << activePlayerIndex << std::endl;
            }
            else {
                std::cout << "add " + playerName << std::endl;
                player = Player(playerName);
                players.push_back(player);  // Lưu người chơi vào danh sách
                activePlayerIndex++;  // Chuyển đến người chơi tiếp theo
            }
        }
    }
}

