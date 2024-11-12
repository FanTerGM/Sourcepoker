#include <gameObject.h>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>


namespace fs = std::filesystem;
using json = nlohmann::json;

leaderboard::leaderboard() {
	for (const auto& info : fs::directory_iterator("Resources/playerInfo")) {
		std::ifstream file(info.path());
		if (file.is_open()) {
			json playerData;
			file >> playerData;
			file.close();

			playerLeaderboard.push_back(playerData.get<Player>());

			std::sort(playerLeaderboard.begin(), playerLeaderboard.end(), [](Player& left, Player& right) {
				return left.getPlayertWinrate() > right.getPlayertWinrate();	
				});
		}
	}
};

void leaderboard::display() {
	cout << "--------------------------------------" << endl;
	cout << "| Rank |   Player's name   | winrate |" << endl;
	cout << "--------------------------------------" << endl;
	int rank = 0;
	for (Player& player : playerLeaderboard) {
		cout << "| "<< setw(4) << ++rank << " | " << setw(17) << player.getPlayerUsername() << " | " << setw(7) << player.getPlayertWinrate() << fixed << setprecision(1)<< " |" << endl;
		cout << "--------------------------------------" << endl;
		player.updateRanking(rank);
		player.recordPlayer();
	}
}

