#pragma once

#include <gameObject.h>
#include <iomanip>
#include <nlohmann/json.hpp>


//namespace fs = std::filesystem;
//using json = nlohmann::json;

class leaderboard {
public:
	leaderboard();
	void displaySFML(sf::RenderWindow& window, sf::Font& font);
private:
	std::vector<Player> playerLeaderboard; 
	
};
