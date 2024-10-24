#pragma once
#include "gameObject.h"

class drawTable : public Table {
public:
	drawTable(int numberOfPlayers, int numberOfNPCs);

	void dealCardtoPlayers() override;
};