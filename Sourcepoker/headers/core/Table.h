#pragma once
#include <gameObject.h>
#include <vector>
#include <string>
#include <iostream>

/**
 * @class Table
 * @brief Manages a poker table, including players, deck, and game operations.
 *
 * Inherits from Hand and provides virtual functions to customize game modes.
 */
class Table : public Hand {

protected:
    int numberOfPlayers;      ///< Number of human players at the table.
    int numberOfNPCs;         ///< Number of AI (NPC) players at the table.
    int pot;
    Deck deck;                ///< Deck of cards used in the game.
    std::vector<Player> players; ///< Collection of players in the game (both human and AI).

public:
    /**
     * @brief Default constructor initializes the table with one human and one AI player.
     */
    Table();

    /**
     * @brief Constructor allowing custom number of players and AI participants.
     * @param playerCount Number of human players.
     * @param npcCount Number of AI players.
     */
    Table(int playerCount, int npcCount);

    /**
     * @brief Populates the table with human players and AI players.
     */
    void populateTable();

    /**
     * @brief Creates a new deck for the game.
     */
    void createDeck();

    /**
     * @brief Deals cards to all players at the table.
     */
    virtual void dealCardsToPlayers();

    /**
     * @brief Displays the hands of all players at the table.
     */
    void showPlayersHands() const;

    /**
     * @brief Deals the initial community cards ("flop") in the game.
     */
    virtual void dealFlop();

    /**
     * @brief Clears all players' hands to prepare for a new round.
     */
    void clearTable();


    /**
    * @brief Process the action of checking/calling, folding and raising
    * @param highestBet Take the current highest betting value
    * @param currentPlayerIndex The player who in play
    * @param raiseIndex Note the most recent raise
    */
    void processPlayerAction(int& highestBet, int currentPlayerIndex, int& raiseIndex);

    /**
     * @brief Handles the game start, manages rounds, and controls game flow.
     */
    virtual void startGame();

    /**
     * @brief Determines and displays the winner of the current round.
     */
    virtual void determineWinner();

    /**
     * @brief Gets the name of the current game mode.
     * @return A string representing the mode name.
     */
    virtual std::string getModeName() const;

    /**
     * @brief Virtual destructor for safe inheritance.
     */
    virtual ~Table() {}
};

