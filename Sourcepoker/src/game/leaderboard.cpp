#include <gameObject.h>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>


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

				std::cout << "Player found! Loading..." << std::endl;
				playerLeaderboard.push_back(playerData.get<Player>()); // Deserialize JSON to Player
			}
		}
	}
	std::sort(playerLeaderboard.begin(), playerLeaderboard.end(), [](Player& left, Player& right) {
		return left.getWinRate() > right.getWinRate(); 
		});
};

void leaderboard::display() {
	std::cout  << "--------------------------------------" << std::endl;
	std::cout  << "| Rank |   Player's name   | winrate |" << std::endl;
	std::cout  << "--------------------------------------" << std::endl;
	int rank = 0;
	for (Player& player : playerLeaderboard) {
		std::cout << "| " << std::setw(4) << ++rank << " | " << std::setw(17) << player.getUsername() << " | ";
		std::cout << std::setw(7) << player.getWinRate() << std::fixed << std::setprecision(1) << " |" << std::endl;
		std::cout  << "--------------------------------------" << std::endl;
		player.updateRank(rank);
		player.saveProfile();
	}
}

