#pragma once
#include <gameObject.h>

class superTable : public Table{
public:
	superTable(int numberOfPlayers, int numberOfNPCs);

	std::string getModeName() const override; 
};

