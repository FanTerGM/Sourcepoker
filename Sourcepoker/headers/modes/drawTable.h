#pragma once
#include "../core/Table.h"

class drawTable : public Table {
public:
	drawTable(int numberOfPlayers, int numberOfNPCs);

	void dealCardsToPlayers() override;
	std::string getModeName() const override;
	void startGame() override; 
};