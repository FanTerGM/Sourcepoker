#pragma once
#include <gameObject.h>

class superTable : public Table{
public:
	superTable(int numberOfPlayers, int numberOfNPCs);

	string getModeName() override;
};

