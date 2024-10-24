#pragma once
#include "gameObject.h"

class studTable : public Table {
public:
	studTable(int numberOfPlayers, int numberOfNPCs);
	
	void dealFlop() override;
	void dealCardtoPlayers() override;
};