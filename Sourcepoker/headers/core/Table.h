#pragma once
#include <gameObject.h>


enum DialogState {
    NO_DIALOG,        // Không có hộp thoại
    MAIN_DIALOG,      // Hộp thoại chính với lựa chọn "Check/Call", "Fold", "Raise"
    RAISE_DIALOG      // Hộp thoại nhập số tiền raise
};

/**
 * @class Table
 * @brief Manages a poker table, including players, deck, and game operations.
 *
 * Inherits from Hand and provides virtual functions to customize game modes.
 */
class Table : public Hand {
protected:
    Deck deck;                ///< Deck of cards used in the game.
    std::vector<Player>& players; ///< Collection of players in the game (both human and AI).
    sf::RenderWindow& window;
    sf::Font& font;
    std::string winnerHandRank;
public:
    /**
     * @brief Constructor allowing custom number of players and AI participants.
     */
    Table(sf::RenderWindow& window, sf::Font& font, std::vector<Player> players);

    /**
     * @brief Creates a new deck for the game.
     */
    void createDeck();

    /**
     * @brief Deals cards to all players at the table.
     */
    virtual void dealCardsToPlayers();//sf::RenderWindow& window) = 0;

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
     * @brief Handles the game start, manages rounds, and controls game flow.
     */
    virtual void startGame();

    /**
     * @brief Determines and displays the winner of the current round.
     */
    void determineWinner();

    /**
    * @brief Provide and process action of the player according to the game
    */
    void processPlayerAction(int& highestBet, int currentPlayerIndex, int& raiseIndex);

    /**
    * @brief Initiate a betting round, making changes to the current round highest be and player's bet.
    */
    void bettingRound(int& highestBet);

    /**
     * @brief Gets the name of the current game mode.
     * @return A string representing the mode name.
     */
    virtual std::string getModeName() const;

    /**
     * @brief Virtual destructor for safe inheritance.
     */
    virtual ~Table() {}

    void addPlayer(const std::string& playerName);

    void goToMainMenu();

    void dialogBox();

    void drawTable(sf::RenderWindow& window);
};

