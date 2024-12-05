#pragma once
#include "../core/Table.h"

class drawTable : public Table {
public:
	drawTable(sf::RenderWindow& window, int numberOfPlayers, int numberOfNPCs);
	drawTable(sf::RenderWindow& window, sf::Font& font);
	void dealCardsToPlayers(/*sf::RenderWindow& window*/) override;
	std::string getModeName() const override;
	void startGame() override; 
private:
	sf::RenderWindow& window;
	sf::Font& font;
};