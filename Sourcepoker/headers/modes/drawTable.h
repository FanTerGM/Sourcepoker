#pragma once
#include "../core/Table.h"

class drawTable : public Table {
public:
	drawTable(sf::RenderWindow& window,sf::Font& font, std::vector<Player> players);
	
	void dealCardsToPlayers() override;
	std::string getModeName() const override;
	void startGame() override; 
};