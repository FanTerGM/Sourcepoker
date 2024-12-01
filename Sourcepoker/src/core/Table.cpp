#include <gameObject.h>
#include <iostream>
#include <algorithm> // For std::sort and std::greater
#include <numeric>   // For std::accumulate

/* --- Table Class Definitions ---
   Manages the poker table, players, and game operations. */

   // Default constructor initializes table with one player and one NPC
Table::Table() : numberOfPlayers(0), numberOfNPCs(1) {
    populateTable();
}

// Constructor allowing specification of player and NPC counts
Table::Table(int playerCount, int npcCount) : numberOfPlayers(playerCount), numberOfNPCs(npcCount) {
    populateTable();
}

// Adds players and NPCs to the table
void Table::populateTable() {
    // Populate human players
    for (int i = 0; i < numberOfPlayers; i++) {
        std::string playerName;
        std::cout << "Enter Player " << (i + 1) << "'s name: ";
        std::cin >> playerName;
        Player player = player.loadProfile(playerName);  // Load or create player profile
        players.push_back(player);
    }

    // Populate AI players
    for (int i = 0; i < numberOfNPCs; i++) {
        std::string aiName = "AI_" + std::to_string(i + 1);
        players.emplace_back(aiName);  // Automatically creates an AI player
    }
}

// Deals five cards to each player
void Table::dealCardsToPlayers() {
    for (Player& player : players) {
        player.cardToHand(deck, 5, true);  // Deal 5 cards per player
    }
}

// Gets the current game mode name
std::string Table::getModeName() const {
    return "Default5";
}

// Deals the "flop" (first three community cards)
void Table::dealFlop() {
    cardToHand(deck, 3, true);  // Deal 3 cards to the table
}

// Displays each player's hand
void Table::showPlayersHands() const {
    for (const Player& player : players) {
        std::cout << player.getUsername() << "'s hand:" << std::endl;
        player.showCards();
    }
}

// Initializes a new deck
void Table::createDeck() {
    deck = Deck();
}

// Handles a tie situation, updating game history for tied players
int Table::handleTie() {
    int i = 0;
    while (players[0] == players[++i]) {  // Increment through tied players
        players[i].updateGameHistory(true, 1);  // Update game history for tied players
        std::cout << players[i].getUsername() << " tied!" << std::endl;
    }
    return i;
}

// Determines the winner among players and updates game history
void Table::determineWinner() {
    // Sort players by hand strength in descending order
    std::sort(players.begin(), players.end(), std::greater<Player>());

    // Handle ties if there are multiple players
    int i = (players.size() > 1) ? handleTie() : 0;

    // Update game history for non-winning players
    for (; i < players.size(); i++) {
        players[i].updateGameHistory(false, 1);
    }

    // Announce the winner
    std::cout << "Winner: " << players[0].getUsername() << std::endl;
    players[0].updateGameHistory(true, 1);
    int handRank = Evaluator(players[0].getHand()).evaluateHandRank();
    std::cout << "Winning hand rank: "
        << Evaluator().rankToString(handRank) << std::endl;
}

// Clears all players' hands for a new round
void Table::clearTable() {
    for (Player& player : players) {
        player.clearHand();
    }
}

void Table::processPlayerAction(int& highestBet, int currentPlayerIndex){
    int choice;
    std::cout << "Player " << currentPlayerIndex + 1 << ", choose your action (1=Check/Call, 2=Fold, 3=Raise): ";
    std::cin >> choice;

    switch (choice) {
    case 1: // Check/Call
        if (players[currentPlayerIndex].bet < highestBet) {
            players[currentPlayerIndex].bet = highestBet;  // Player calls
        }
        break;

    case 2: // Fold
        players[currentPlayerIndex].folded = true; // Player folds
        break;

    case 3: // Raise
        int raiseAmount;
        std::cout << "Enter raise amount: ";
        std::cin >> raiseAmount;
        if (raiseAmount > highestBet) {
            players[currentPlayerIndex].bet = highestBet + raiseAmount;  // Player raises
            highestBet = players[currentPlayerIndex].bet;  // Update the highest bet
        }
        else {
            std::cout << "Raise amount must be higher than the current bet.\n";
        }
        break;

    default:
        std::cout << "Invalid choice. Try again.\n";
        processPlayerAction(highestBet, currentPlayerIndex);  // Retry on invalid input
        break;
    }
}

// Runs the game loop, dealing cards, displaying hands, and determining the winner
void Table::startGame() {
    do {
        createDeck();           // Prepare a new deck
        clearTable();           // Clear previous hands
        dealCardsToPlayers();    // Deal new hand

        int index = 0, folded = 0, highestBet = 10, raisedIndex = 0;
        bool allCalled = false;
        do {
            if (players[index].folded) {
                index = (index + 1) % (players.size());
                continue; // Skip the current player if they have folded
            }
            players[index].showCards(); 

            // Move to the next player
            index = (index + 1) % (players.size());

            // End loop when all players have folded or if everyone except one player has folded
        } while (allCalled && raisedIndex == index); // This condition will stop when only one active player remains

        // Display each player's hand
        std::cout << "Players' hands:" << std::endl;
        showPlayersHands();

        // Determine and display the winner
        determineWinner();

        // Prompt for a new round
        std::cout << "Play another round? (Press 1 to continue): ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');

    } while (std::cin.get() == '1');
}

// Placeholder for a betting feature
void Table::raiseBet() {
    std::cout << "Betting feature is currently unavailable." << std::endl;
}