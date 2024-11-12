#pragma once
#include "../core/Table.h"

class drawTable : public Table {
public:
	drawTable(int numberOfPlayers, int numberOfNPCs);

	void draw(int playerSeat) override;
	void dealCardtoPlayers() override;
	string getModeName() override;
};