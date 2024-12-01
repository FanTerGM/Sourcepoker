#include "../headers/visual/PlayerInfoInput.h"

//PlayerInfoInput::PlayerInfoInput(int screenWidth, int screenHeight, int playerCount)
//    : screenWidth(screenWidth), screenHeight(screenHeight), playerCount(playerCount) {


//    // Khởi tạo prompt text
//    promptText.setFont(font);
//    promptText.setString("Enter names for " + std::to_string(playerCount) + " players:");
//    promptText.setCharacterSize(24);
//    promptText.setFillColor(sf::Color::White);
//    promptText.setPosition(50, 50);
//
//    // Khởi tạo các ô nhập liệu cho tên người chơi
//    createInputFields();
//}
//
//void PlayerInfoInput::createInputFields() {
//    // Tạo các ô nhập liệu cho mỗi người chơi
//    for (int i = 0; i < playerCount; ++i) {
//        sf::RectangleShape inputField(sf::Vector2f(300, 40));
//        inputField.setFillColor(sf::Color::White);
//        inputField.setPosition(50, 100 + i * 60);  // Khoảng cách giữa các ô nhập liệu
//
//        inputFields.push_back(inputField);
//
//        sf::Text text;
//        text.setFont(font);
//        text.setCharacterSize(20);
//        text.setFillColor(sf::Color::Black);
//        text.setPosition(50, 100 + i * 60);
//        playerNamesText.push_back(text);
//
//        playerNames.push_back("");  // Mảng lưu tên người chơi
//        isTextBoxSelected.push_back(false);
//    }
//}
//
//void PlayerInfoInput::handleMouseClick(const sf::Vector2i& mousePosition) {
//    for (int i = 0; i < inputFields.size(); ++i) {
//        if (inputFields[i].getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
//            isTextBoxSelected[i] = true;  // Chọn ô nhập liệu này
//        }
//        else {
//            isTextBoxSelected[i] = false;  // Bỏ chọn các ô còn lại
//        }
//    }
//}
//
//void PlayerInfoInput::handleTextInput(const sf::Event& event) {
//    for (int i = 0; i < playerCount; ++i) {
//        if (isTextBoxSelected[i] && event.type == sf::Event::TextEntered) {
//            if (event.text.unicode < 128 && event.text.unicode != 8) {  // Nếu là ký tự hợp lệ
//                playerNames[i] += static_cast<char>(event.text.unicode);
//            }
//            else if (event.text.unicode == 8 && playerNames[i].length() > 0) {  // Xóa ký tự
//                playerNames[i].pop_back();
//            }
//        }
//    }
//}
//
//void PlayerInfoInput::render(sf::RenderWindow& window) {
//    // Vẽ hướng dẫn nhập tên người chơi
//    window.draw(promptText);
//
//    // Vẽ các ô nhập liệu và tên người chơi
//    for (int i = 0; i < playerCount; ++i) {
//        window.draw(inputFields[i]);
//
//        // Cập nhật văn bản tên người chơi
//        playerNamesText[i].setString(playerNames[i]);
//        playerNamesText[i].setPosition(55, 105 + i * 60);  // Vị trí của tên người chơi
//        window.draw(playerNamesText[i]);
//    }
//}
//
//std::vector<std::string> PlayerInfoInput::getPlayerNames() const {
//    return playerNames;
//}

PlayerInfoInput::PlayerInfoInput(float width, float height, int numPlayers) : numPlayers(numPlayers) {
    font.loadFromFile("Pangolin-Regular.ttf");

    for (int i = 0; i < numPlayers; ++i) {
        sf::RectangleShape inputBox(sf::Vector2f(200, 50));
        inputBox.setPosition(width / 2 + 100, height / 2 + (i * 60));  // Cách nhau 40px cho mỗi ô nhập
        nameInputBoxes.push_back(inputBox);

        sf::Text inputText;
        inputText.setFont(font);
        inputText.setString("Player " + std::to_string(i + 1) + ": ");
        inputText.setCharacterSize(20);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(width / 2 - 120, height / 2 + (i * 60) - 20);  // Vị trí text cho mỗi người chơi
        playerNames.push_back(inputText);
        //sf::Text nameText;
        //nameText.setFont(font);
        //nameText.setPosition(50, 50 + (i * 40));
        //playerNames.push_back(nameText);
        isActive.push_back(false); // Ban đầu không có ô nào đang được chọn
        playerInputs.push_back(""); // Mảng lưu trữ tên người chơi, ban đầu trống

        continueButton.setSize(sf::Vector2f(200, 50));  // Kích thước của nút
        continueButton.setPosition(100, 300);  // Vị trí của nút
        continueButton.setFillColor(sf::Color::Green);  // Màu nền của nút
    }
}

void PlayerInfoInput::render(sf::RenderWindow& window) {
    //render input box and lable player's name
    for (int i = 0; i < numPlayers; ++i) {
        window.draw(nameInputBoxes[i]);
        window.draw(playerNames[i]);

        // Nếu ô đang được chọn, hiển thị màu khác
        if (isActive[i]) {
            nameInputBoxes[i].setFillColor(sf::Color(100, 100, 255));  // Màu nền ô được chọn
        }
        else {
            nameInputBoxes[i].setFillColor(sf::Color(200, 200, 200));  // Màu nền ô chưa được chọn
        }

        // Hiển thị tên người chơi đã nhập
        sf::Text playerInputText;
        playerInputText.setFont(font);
        playerInputText.setString(playerInputs[i]);
        playerInputText.setCharacterSize(20);
        playerInputText.setFillColor(sf::Color::Black);
        playerInputText.setPosition(nameInputBoxes[i].getPosition().x + 10, nameInputBoxes[i].getPosition().y + 10);
        window.draw(playerInputText);
    }
    window.draw(continueButton);
}

void PlayerInfoInput::handleMouseClick(const sf::Vector2i& mousePosition) {
    // Xác định xem người dùng có nhấn vào ô nào không
    for (int i = 0; i < numPlayers; ++i) {
        if (nameInputBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
            activePlayerIndex = i;  // Cập nhật chỉ số người chơi đang nhập
            isActive[i] = true;  // Đánh dấu ô này là đang nhập
        }
        else {
            isActive[i] = false;  // Nếu không phải ô này, đánh dấu là không nhập
        }
        if (continueButton.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
            // Lấy tên người chơi từ text box (ví dụ playerCountTextField)
            std::string playerName = playerInputs[activePlayerIndex];  // Giả sử bạn lấy tên từ text box

            if (!playerName.empty()) {
                // Tạo đối tượng Player mới
                Player newPlayer(playerName);

                // Lưu lại thông tin người chơi (có thể lưu trong một danh sách hoặc cơ sở dữ liệu)
                // Ví dụ: players.push_back(newPlayer);

                // Lưu profile vào file (nếu cần)
                newPlayer.saveProfile("playerProfiles/");

                // Cập nhật trạng thái trò chơi
                currentState = INPUT_PLAYER_INFO;  // Chuyển sang màn hình nhập thông tin người chơi
            }
        }
    }
}

void PlayerInfoInput::handleTextInput(sf::Event& event) {
    if (activePlayerIndex >= 0 && activePlayerIndex < numPlayers) {
        // Chỉ xử lý nhập liệu khi có một ô đang được chọn
        if (event.text.unicode == '\b' && playerInputs[activePlayerIndex].size() > 0) {
            // Nếu nhấn phím backspace, xóa ký tự cuối cùng
            playerInputs[activePlayerIndex].pop_back();
        }
        else if (event.text.unicode < 128) {
            // Nếu là ký tự hợp lệ, thêm vào chuỗi nhập
            playerInputs[activePlayerIndex] += static_cast<char>(event.text.unicode);
        }
    }
}

