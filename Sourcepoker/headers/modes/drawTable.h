#pragma once
#include "../core/Table.h"

class drawTable : public Table {
public:
	drawTable(int numberOfPlayers, int numberOfNPCs);

	void dealCardtoPlayers() override;
	string getModeName() override;
};