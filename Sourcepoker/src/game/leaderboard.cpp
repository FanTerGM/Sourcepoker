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

			playerLeaderboard.push_back(pair(
				playerData["username"].get<string>(),
				playerData["winrate"].get<double>()
			));

			std::sort(playerLeaderboard.begin(), playerLeaderboard.end(), [](pair <string, double> & left, pair<string, double>& right) {
				return left.second >= right.second;
				});
		}
	}
};

void leaderboard::display() {
	cout << "--------------------------------------" << endl;
	cout << "| Rank |   Player's name   | winrate |" << endl;
	cout << "--------------------------------------" << endl;
	int rank = 0;
	for (const pair<string, double>& player : playerLeaderboard) {
		cout << "| "<< setw(4) << ++rank << " | " << setw(17) << player.first << " | " << setw(7) << player.second << " |" << endl;
		cout << "--------------------------------------" << endl;
	}
}

