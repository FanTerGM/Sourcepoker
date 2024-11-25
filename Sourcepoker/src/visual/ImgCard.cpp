#include "../../headers/visual/ImgCard.h"
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