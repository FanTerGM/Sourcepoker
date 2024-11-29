#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <sstream>
#include "../headers/game/GameState.h"


class PlayerSelection {
private:

	sf::Font font;
	sf::Text playerCountText;
	sf::Text npcCountText;


	sf::Text continueButtonText;
	sf::RectangleShape playerTextBox;
	sf::RectangleShape npcTextBox;
	sf::RectangleShape continueButton;

	
	std::string playerCount;
	std::string npcCount;

	bool isPlayerTextBoxSelected = false;
	bool isNpcTextBoxSelected = false;

public:

	PlayerSelection(int width, int height);
	void render(sf::RenderWindow& window);
	void handleTextInput(sf::Event& event);
	void handleMouseClick(const sf::Vector2i& mousePosition, GameState& currentState);
	bool isContinueClicked(const sf::Vector2i& mousePosition);

	int getNumPlayers() const;
	int getNumNPCs() const;

	
};