#pragma once
#include <gameObject.h>

class Table;

class House {
public:
	House(Table* table);

    /**
    * @A pointer to a table that is assigned a Gamemode 
    * Ex: house.setTable(new studTable(numberOfPlayers, numberOfNPCs));
    */
    void setTable(Table* table);

    /**
    * @brief Populates the table with human players and AI players.
    */
    void populateTable();

    /**
     * @brief Displays the hands of all players at the table.
     */
    void showPlayersHand();

    /**
    * @brief Displays community cards.
    */
    void showCards(sf::RenderWindow& window);

    /**
     * @brief Clears all players' hands to prepare for a new round.
     */
    void clearTable();
    /**
     * @brief Deals the initial community cards ("flop") in the game.
     */
    void dealFlop();
    /**
     * @brief Handles the game start, manages rounds, and controls game flow.
     */
    void StartGame();
    /**
    * @brief Determines and displays the winner of the current round.
    */
    void determineWinner();
    /**
    * @brief Deals cards to all players at the table.
    */
    void dealCardtoPlayers();

    /**
    * @brief Gets the name of the current game mode.
    * @return A string representing the mode name.
    */
    std::string getModeName();
    
    ~House();
private:
    Table* currentTable;
    //sf::RenderWindow& window;
};