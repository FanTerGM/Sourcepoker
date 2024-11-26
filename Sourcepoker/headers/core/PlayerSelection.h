#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../headers/game/GameState.h"

class PlayerSelection {
private:
	sf::Font font;
	sf::Text playerCountText, npcCountText, labelText;	  //hiển thị số lượng người chơi, npc
	std::string playerCountInput, npcCountInput;
	int playerCount, npcCount;
	bool isInputtingPlayerCount, isInputtingNpcCount;

public:
	PlayerSelection(float width, float height);
	void handleTextInput(sf::Event& event);
	void handleMouseClick(sf::Vector2i mousePosition, GameState& currentState);
	void render(sf::RenderWindow& window);
	int getPlayerCount() const { return playerCount; }
	int getNpcCount() const { return npcCount; }
	bool isReadyToStart() const {
		return (playerCount >= 1 && npcCount >= 0);
	};
};