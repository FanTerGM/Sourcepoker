#include "../../headers/game/SeparateFunction.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <gameObject.h>

namespace fs = std::filesystem;
using json = nlohmann::json;

void showListofPlayers(std::vector<std::string> files) {
	std::cout << "Player list:\n";
	// Display all players that is in database with numbering for easy choosing
	for (size_t i = 0; i < files.size(); ++i) {
		std::cout << i + 1 << ". " << files[i] << std::endl;
	}
}

void browsePlayers() {
	// Get all player's info and store them in a array.
	std::vector<std::string> files;
	for (const auto& entry : fs::directory_iterator("Resources/playerInfo")) {
		if (entry.is_regular_file()) {
			files.push_back(entry.path().filename().string());
		}
	}

	while (true) {

		showListofPlayers(files);

		int choice = 0;
		std::cout << "\nEnter the player you want to view: "; std::cin  >> choice;
		// Prevent invalid choice
		while (choice  < 1 || choice > files.size()) {
			std::cout << "Invalid choice, please try again";
			std::cout << "\nEnter the player you want to view: "; std::cin  >> choice;
		}

		std::string filePath = "Resources/playerInfo/" + files[choice - 1];

		if (std::filesystem::exists(filePath)) {

			//Nếu tồn tại thì mở file
			std::ifstream file(filePath);
			if (file.is_open()) {
				json playerData;
				file >> playerData;
				file.close();

				//Thông báo đã tìm thành công file người chơi 
				std::cout << "Player found! Loading ..." << std::endl;

				//Trả về thông tin người chơi
				playerData.get<Player>().displayInfo();
			}
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		std::cout << "Press 1 to return to player list\nPress anything else to exit player list\n"; 
		if (std::cin.get() != '1') break; 
	}
}

void removeTrailingSpaces(std::string& str) {
	// Find the position of the last non-whitespace character
	size_t end = str.find_last_not_of(" \t\n\r\f\v");

	if (end != std::string::npos) {
		// If found, erase everything after the last non-whitespace character
		str.erase(end + 1);
	}
	else {
		// If no non-whitespace characters are found, clear the string
		str.clear();
	}
}