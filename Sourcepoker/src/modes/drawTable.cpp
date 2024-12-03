#include <gameObject.h>
#include <gameModes.h>

drawTable::drawTable(int numberOfPlayers, int numberOfNPCs) : Table(numberOfPlayers,numberOfNPCs) {}

void drawTable::dealCardsToPlayers() {//sf::RenderWindow& window) {
	//float xOffset = 50.0f;
	//float yOffset = 50.0f;
	for (Player& player : players) {

		//	// Vẽ tay bài lên cửa sổ
		//	for (size_t i = 0; i < player.getHand().size(); ++i) {
		//		std::string suit = player.getHand()[i].getSuit();
		//		int rank = player.getHand()[i].getRank();

		//		// Tạo đường dẫn đến hình ảnh của lá bài
		//		std::string imgPath = "Resources/images/cards/" + std::to_string(rank) + "_of_" + suit + ".png";
		//		ImgCard imgCard(suit, rank, imgPath);  // Tạo đối tượng ImgCard cho mỗi lá bài
		//		imgCard.draw(window, xOffset + (i * 100), yOffset);  // Vẽ lá bài lên cửa sổ
		//	}
		player.cardToHand(deck, 5, true);
	}
}

std::string drawTable::getModeName() const{
	return "draw";
}

void drawTable::startGame(){
	do {
		createDeck();
		clearTable();
		dealCardsToPlayers();
		// Display the player's hand and the community card.
		std::cout << "Player hand:\n";
		for (Player& player : players) {
			std::cout << player.getUsername() << std::endl;
			player.showCards();
			if (player.getUsername().find("AI_") != std::string::npos) continue;
			std::cout << "Choose cards to replace: " << std::endl;
			player.replaceCard(deck);
			std::cout << "After replacement: " << std::endl;
			player.showCards();
		}
		determineWinner();
		std::cout << "Another round? (Press 1 to continue)" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

	} while (std::cin.get() == '1');
}

