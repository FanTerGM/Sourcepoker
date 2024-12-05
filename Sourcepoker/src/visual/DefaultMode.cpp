#include "../headers/visual/DefaultMode.h"

//constructor
DefaultMode::DefaultMode(int numPlayers, int numNPCs)
: numPlayers(numPlayers), numNPCs(numNPCs){
    if (!font.loadFromFile("Pangolin-Regular.ttf.ttf")) {
        std::cerr << "Error loading font for DefaultMode" << std::endl;
    }
}

//render all 
void DefaultMode::renderGame(sf::RenderWindow& window) {
	drawTable(window);	//draw table
	drawPlayer(window);	//draw player
	drawCard(window);	//draw player's cards
}

//draw table
void DefaultMode::drawTable(sf::RenderWindow& window) {
	sf::Texture tableTexture;
	if (!tableTexture.loadFromFile("Resources/images/table.jpg")) {
		std::cerr << "Error loading table image" << std::endl;
		return;
	}
	sf::Sprite tableSprite(tableTexture);
	tableSprite.setPosition(0, 0); //position of table

	window.draw(tableSprite);
}

////draw player ( location + name)
//void DefaultMode::drawPlayer(sf::RenderWindow& window) {
//
//    int numTotalPlayers = numPlayers + numNPCs;
//
//    // Vẽ người chơi xung quanh bàn theo các vị trí cố định (ví dụ: 4 góc và các vị trí giữa)
//    float angleStep = 360.f / numTotalPlayers;
//
//    for (int i = 0; i < numTotalPlayers; ++i) {
//        // Tính toán vị trí của mỗi người chơi
//        float angle = i * angleStep;
//        float x = 500 + 250 * cos(angle * 3.14159f / 180.f);  // Xác định tọa độ X theo góc
//        float y = 350 + 250 * sin(angle * 3.14159f / 180.f);  // Xác định tọa độ Y theo góc
//
//        // Tạo sprite và vẽ người chơi
//        sf::CircleShape playerShape(30);  // Hình tròn đại diện cho người chơi
//        playerShape.setFillColor(sf::Color::Red);  // Màu của người chơi
//        playerShape.setPosition(x - playerShape.getRadius(), y - playerShape.getRadius());  // Điều chỉnh vị trí
//
//        window.draw(playerShape);  // Vẽ người chơi lên màn hình
//
//        // Vẽ tên người chơi (sử dụng tên từ PlayerInfoInput)
//        sf::Text playerNameText(playerInfo.getPlayerNames()[i], playerInfo.getFont(), 20);
//        playerNameText.setFillColor(sf::Color::White);
//        playerNameText.setPosition(x - playerNameText.getLocalBounds().width / 2, y + 35);  // Vị trí của tên
//
//        window.draw(playerNameText);  // Vẽ tên người chơi lên màn hình
//    }
//}

////draw player's cards
//void DefaultMode::drawCard(sf::RenderWindow& window) {
//    for (int i = 0; i < numPlayers + numNPCs; ++i) {
//        const Player& player = playerInfo.getPlayers()[i];
//        int cardOffset = 0; //to move card on the window
//        
//        for (int j = 0; j < player.getHand().size(); ++j) {
//            std::string cardName = player.getHand()[i].toString();
//            sf::Texture cardTexture;
//            if (!cardTexture.loadFromFile("Resources/cards/" + cardName + ".png")) {
//                std::cerr << "Error loading card image: " << cardName << std::endl;
//                continue;
//            }
//
//            sf::Sprite cardSprite(cardTexture);
//            cardSprite.setPosition(50 + cardOffset, 200 + i * 150); // position of card;
//
//            window.draw(cardSprite);
//            cardOffset += 60;
//        }
//    }
//}

//render result dialog
void DefaultMode::renderResultDialog(sf::RenderWindow& window, const std::string& winner) {
    // Tạo hộp thoại có viền trắng và nền đen
    sf::RectangleShape box(sf::Vector2f(400, 200));
    box.setFillColor(sf::Color::Black);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(5);
    box.setPosition(200, 150); // Vị trí hộp thoại giữa màn hình

    // Tạo text hiển thị kết quả chiến thắng
    sf::Text resultText("Winner: " + winner, font, 24);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(250, 180); // Vị trí của kết quả

    // Tạo nút "Tiếp tục"
    sf::RectangleShape continueButton(sf::Vector2f(150, 50));
    continueButton.setFillColor(sf::Color::Green);
    continueButton.setPosition(250, 230); // Vị trí nút "Tiếp tục"

    sf::Text continueText("Next Round", font, 20);
    continueText.setFillColor(sf::Color::White);
    continueText.setPosition(275, 240); // Vị trí text trong nút "Tiếp tục"

    // Tạo nút "Thoát"
    sf::RectangleShape exitButton(sf::Vector2f(150, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(250, 300); // Vị trí nút "Thoát"

    sf::Text exitText("Exit", font, 20);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(290, 310); // Vị trí text trong nút "Thoát"

    // Vẽ tất cả các thành phần lên cửa sổ
    window.draw(box);
    window.draw(resultText);
    window.draw(continueButton);
    window.draw(continueText);
    window.draw(exitButton);
    window.draw(exitText);
}