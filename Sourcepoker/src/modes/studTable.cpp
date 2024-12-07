#include <gameObject.h>
#include <gameModes.h>

studTable::studTable(sf::RenderWindow& window, sf::Font& font, std::vector<Player> players) : Table(window, font, players) {}

void studTable::dealFlop() {
	for (Player& player : players) {
		player.cardToHand(deck, 2, false);
	}
}

void studTable::dealCardsToPlayers() {
	for (Player& player : players) {
		player.cardToHand(deck, 3, true);
	}
}

std::string studTable::getModeName() const{
	return "stud";
}

void studTable::startGame() {
	//window.clear(sf::Color::Green)
	createDeck();// Prepare a new deck
	clearTable();// Clear previous hands
	dealFlop();
	dealCardsToPlayers();// Deal new hand

	int highestBet = 10;

	bettingRound(highestBet);

	// Draw each player's hand
	std::cout << "Players' hands:" << std::endl;
	showPlayersHands();

	// Determine and display the winner
	determineWinner();
	dialogBox();
	window.display();
}