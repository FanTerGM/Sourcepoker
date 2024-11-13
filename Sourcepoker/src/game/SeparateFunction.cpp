#include "../../headers/game/SeparateFunction.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <gameObject.h>

namespace fs = std::filesystem;
using json = nlohmann::json;

void SeparateFunction::showListofPlayers(vector<string> files) const {
	cout << "Player list:\n";
	for (size_t i = 0; i < files.size(); ++i) {
		cout << i + 1 << ". " << files[i] << endl;
	}
}

void SeparateFunction::browsePlayers() const {
	vector<string> files;
	for (const auto& entry : fs::directory_iterator("Resources/playerInfo")) {
		if (entry.is_regular_file()) {
			files.push_back(entry.path().filename().string());
		}
	}

	while (true) {
		showListofPlayers(files);

		int choice = 0;
		cout << "\nEnter the player you want to view: "; cin >> choice;
		while (choice  < 1 || choice > files.size()) {
			cout << "Invalid choice, please try again";
			cout << "\nEnter the player you want to view: "; cin >> choice;
		}

		string filePath = "Resources/playerInfo/" + files[choice - 1];

		if (std::filesystem::exists(filePath)) {

			//Nếu tồn tại thì mở file
			std::ifstream file(filePath);
			if (file.is_open()) {
				json playerData;
				file >> playerData;
				file.close();

				//Thông báo đã tìm thành công file người chơi 
				cout << "Player found! Loading ..." << endl;

				//Trả về thông tin người chơi
				playerData.get<Player>().infoDisplay();
			}
		}
		cin.clear();
		cin.ignore(1000, '\n');

		cout << "Press 1 to return to player list\nPress anything else to exit player list\n"; 
		if (cin.get() != '1') break; 
	}
}
