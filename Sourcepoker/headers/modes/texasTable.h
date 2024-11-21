#pragma once
#include <gameObject.h>

class texasTable : public Table{
public: 
	texasTable(int numberOfPlayers, int numberOfNPCs);
	
	void dealCardsToPlayers() override; 
	void dealFlop() override;
	std::string getModeName() const override;
};