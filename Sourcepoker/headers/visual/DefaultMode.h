#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <gameObject.h>

class DefaultMode {
private:
	int numPlayers;
	int numNPCs;
	sf::Font font;
	std::vector<Player> players;
public:
	DefaultMode(int numPlayers, int numNPCs);
	void renderGame(sf::RenderWindow& window); 
	void drawTable(sf::RenderWindow& window); //draw table
	void drawPlayer(sf::RenderWindow& window); //draw player around the table
	void drawCard(sf::RenderWindow& window); //draw cards at each player's hand
	void renderResultDialog(sf::RenderWindow& window, const std::string& winner);


};