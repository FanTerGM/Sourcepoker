#pragma once
#include "../core/Table.h"

class studTable : public Table {
public:
	studTable(int numberOfPlayers, int numberOfNPCs);
	
	void dealFlop() override;
	void dealCardtoPlayers() override;
};