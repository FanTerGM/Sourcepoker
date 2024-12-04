#include "../headers/visual/ImgCard.h"
#include <stdexcept> //for std::runtime_error

ImgCard::ImgCard(const std::string& suit, int rank, const std::string& imgPath)
	: suit(suit), rank(rank), imgPath(imgPath) {
	if (!texture.loadFromFile(imgPath)) {
		throw std::runtime_error("Couldn't load card image from path: " + imgPath);
	}
	sprite.setTexture(texture);
}

//get the rank of the card
int ImgCard::getRank() const {
	return rank;
}

//get the suit of the card
std::string ImgCard::getSuit() const {
	return suit;
}

//draw the card
void ImgCard::draw(sf::RenderWindow& window, int x, int y) {
	sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
	window.draw(sprite);
}

// Convert card information to string
std::string ImgCard::toString() const {
	return suit + " " + std::to_string(rank);
}

//void ImgCard::renderCards(sf::RenderWindow& window, const Player& player, int xPos, int yPos) {
//    int cardOffset = 0;
//
//    // Lặp qua từng lá bài trong tay người chơi và vẽ chúng
//    for (int i = 0; i < player.getHand().size(); ++i) {
//        sf::Texture cardTexture;
//        const std::string cardName = player.getHand()[i].toString(); // Lấy tên lá bài
//
//        // Tải ảnh của lá bài
//        if (!cardTexture.loadFromFile("Resources/cards/" + cardName + ".png")) {
//            std::cerr << "Error loading card image: " << cardName << std::endl;
//            continue;
//        }
//
//        sf::Sprite cardSprite(cardTexture);
//        cardSprite.setPosition(xPos + cardOffset, yPos);  // Điều chỉnh vị trí của bài
//        window.draw(cardSprite);  // Vẽ lá bài lên cửa sổ
//        cardOffset += 60;  // Tăng offset để vẽ các lá bài cách nhau
//    }
//}