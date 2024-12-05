#include "../headers/game/leaderboard.h"
#include <sstream> //using ostreamstring


namespace fs = std::filesystem;
using json = nlohmann::json;

leaderboard::leaderboard() { 
		for (const auto& info : fs::directory_iterator("Resources/playerInfo")) {
			if (std::filesystem::exists(info.path())) {
				std::ifstream file(info.path());
				if (file.is_open()) {
					json playerData;
					file >> playerData;
					file.close();

					std::cout <<"player found! Loading..." << std::endl;
					playerLeaderboard.push_back(playerData.get<Player>()); // Deserialize JSON to Player
				}
			}
		}
		//sort winRate player from biggest to lowest
		std::sort(playerLeaderboard.begin(), playerLeaderboard.end(), [](Player& left, Player& right) {
			return left.getWinRate() > right.getWinRate();
			});
};

void leaderboard::displaySFML(sf::RenderWindow& window, sf::Font& font) {
	//load date from leaderboard

	float yOffset = 50.0f; //start point to draw leaderboard
	for (size_t i = 0; i < playerLeaderboard.size(); ++i) {
		sf::Text text;

		//create player string
		std::ostringstream oss;
		oss << "Rank: " << (i + 1) 
			<< " | Name: " << playerLeaderboard[i].getUsername()
			<< " | Winrate " << std::fixed << std::setprecision(1) << playerLeaderboard[i].getWinRate() << "%";
	
		text.setFont(font);
		text.setString(oss.str());
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::White);
		text.setPosition(50.0f, yOffset);
		window.draw(text);
		yOffset += 30.0f; // Khoảng cách giữa các dòng
	}
}

		/*std::cout << "--------------------------------------" << std::endl;
	std::cout  << "| Rank |   Player's name   | winrate |" << std::endl;
	std::cout  << "--------------------------------------" << std::endl;
	int rank = 0;
	for (Player& player : playerLeaderboard) {
		std::cout << "| " << std::setw(4) << ++rank << " | " << std::setw(17) << player.getUsername() << " | ";
		std::cout << std::setw(7) << player.getWinRate() << std::fixed << std::setprecision(1) << " |" << std::endl;
		std::cout  << "--------------------------------------" << std::endl;
		player.updateRank(rank);
		player.saveProfile();
	}*/