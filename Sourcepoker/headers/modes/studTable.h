#pragma once
#include "../core/Table.h"

class studTable : public Table {
public:
	
	studTable(sf::RenderWindow& window, sf::Font& font, std::vector<Player>& players);

	void dealFlop() override;
	void dealCardsToPlayers() override;
	std::string getModeName() const override; 
	void startGame() override;
};