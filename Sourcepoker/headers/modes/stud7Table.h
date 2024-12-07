#pragma once
#include "../core/Table.h"

class stud7Table : public Table {
public:

	stud7Table(sf::RenderWindow& window, sf::Font& font, std::vector<Player> players);

	void dealFlop() override;
	void dealCardsToPlayers() override;
	std::string getModeName() const override;
	void startGame() override;
};