#pragma once
#include <gameObject.h>

class SeparateFunction {
public:
	/**
	* @brief Check and display all the avablable players in resources allowing user to choose
	*/
	void showListofPlayers(std::vector<std::string> files) const;
	
	/**
	* @brief Browse and view player infomation of user' choosing.
	*/
	void browsePlayers() const;
};