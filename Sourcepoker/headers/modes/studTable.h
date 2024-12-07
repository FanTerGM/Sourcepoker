#pragma once
#include "../core/Table.h"

class studTable : public Table {
public:
	studTable(int numberOfPlayers, int numberOfNPCs);
	
	studTable(sf::RenderWindow& window, sf::Font& font, int numberOfPlayers, int numberOfNPCs);

	void dealFlop() override;
	void dealCardsToPlayers() override;
	std::string getModeName() const override; 
	void startGame() override;
};