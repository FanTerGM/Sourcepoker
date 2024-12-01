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

	sf::Text continueText;
	sf::Text continueButtonText;
	sf::RectangleShape continueButton;

	sf::RectangleShape playerTextBox;  // Text box cho số lượng người chơi
	sf::RectangleShape npcTextBox;     // Text box cho số lượng NPC
	
	std::string playerCount;
	std::string npcCount;


	bool isPlayerTextBoxSelected = false;
	bool isNpcTextBoxSelected = false;

	bool continueButtonPressed;

public:

	PlayerSelection(int width, int height);
	void render(sf::RenderWindow& window);
	void handleTextInput(sf::Event& event);
	void handleMouseClick(const sf::Vector2i& mousePosition, GameState& currentState);
	bool isContinueClicked(const sf::Vector2i& mousePosition);

	int getNumPlayers() const;
	int getNumNPCs() const;

	// Xử lý sự kiện bấm nút "Continue"
	void handleContinueButton(GameState& currentState);

	bool isContinueButtonPressed(const sf::Vector2i& mousePosition);
};