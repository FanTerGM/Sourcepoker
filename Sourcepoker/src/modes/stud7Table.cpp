#include <gameObject.h>
#include <gameModes.h>

stud7Table::stud7Table(sf::RenderWindow& window, sf::Font& font, std::vector<Player> players) : Table(window, font, players) {}

void stud7Table::dealFlop() {
	for (Player& player : players) {
		player.cardToHand(deck, 2, false);
	}
}

void stud7Table::dealCardsToPlayers() {
	for (Player& player : players) {
		player.cardToHand(deck, 5, true);
	}
}

std::string stud7Table::getModeName() const {
	return "stud";
}

void stud7Table::startGame() {
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