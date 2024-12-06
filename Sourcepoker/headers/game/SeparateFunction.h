#pragma once
#include <gameObject.h>


/**
* @brief Check and display all the avablable players in resources allowing user to choose
*/
void showListofPlayers(std::vector<std::string> files);
	
/**
* @brief Browse and view player infomation of user' choosing.
*/
void browsePlayers();

void removeTrailingSpaces(std::string& str);
