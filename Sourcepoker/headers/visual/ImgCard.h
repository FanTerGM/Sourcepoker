#pragma once
#include "string"
#include "SFML/Graphics.hpp"

class ImgCard {
private:
	std::string suit;
	int rank;
	std::string imgPath; //path link to images
	sf::Texture texture; //load cards images
	sf::Sprite sprite;   //show card
public:
	ImgCard(const std::string& suit, int rank, const std::string& imgPath);

	int getRank() const;
	std::string getSuit() const;

	void draw(sf::RenderWindow& window, int x, int y); //draw a method to render card

	std::string toString() const; // convert card information to a string
};

