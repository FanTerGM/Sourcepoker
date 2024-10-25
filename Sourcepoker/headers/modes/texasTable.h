#pragma once
#include "../core/Table.h"

class texasTable : public Table{
public: 
	texasTable(int numberOfPlayers, int numberOfNPCs);
	
	void dealCardtoPlayers() override; 
	void dealFlop() override;
};