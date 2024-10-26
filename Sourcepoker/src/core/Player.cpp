#include <gameObject.h>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

//Dùng để tạo người chơi mới với số liệu mặc định được định dạng trong header 
Player::Player(string name) : username(name) {}

//Dùng để tạo người chơi có thông tin được lưu lại
Player::Player(string name, double win, double played, double winrate, int favoriteHand)
	: username(name), gameWon(win), gamePlayed(played), winrate(winrate), favoriteHand(favoriteHand){}

//Lấy cái số liệu của người chơi
int Player::getPlayerRank() const { return rank; }
string Player::getPlayerUsername() const { return username; }
int Player::getPlayerfavoriteHand() const { return favoriteHand; }
double Player::getPlayertWinrate() { return winrate; }

void Player::updateGameHistoryAndWinrate(bool won) {
	
	gamePlayed++;
	if (won) gameWon++;
	winrate = gameWon * 100 / gamePlayed;
}

//Lưu hoặc tạo mới nếu cần lại thông tin người chơi trong file
void Player::recordPlayer(const string & directory) const {
	json playerData;
	playerData["username"] = username;
	playerData["gameWon"] = gameWon;
	playerData["gamePlayed"] = gamePlayed;
	playerData["winrate"] = winrate; 
	playerData["favoriteHand"] = favoriteHand;

	//Tạo file để đảm bảo file của người chơi tồn tại
	std::filesystem::create_directories(directory);

	//Mở file và lưu thông tin lại 
	std::ofstream outFile(directory + username + ".json");
	if (outFile.is_open()) {
		outFile << playerData.dump(4);
		outFile.close();
	}
}

/*Tìm và tải thông tin người chơi nếu có, trong trường hợp không thì tạo file người chơi mới */
Player Player::loadPlayer(const string& username, const string& directory) {
	string filename = directory + username + ".json";

	//Thông báo người dùng và đảm bảo là người chơi đang được tải 
	cout << "Loading player ..." << endl;
	
	//Kiểm tra trong thư mục Resources/playerInfo/ có tồn tại file người chơi không
	if (std::filesystem::exists(filename)) {
		
		//Nếu tồn tại thì mở file
		std::ifstream file(filename);
		if (file.is_open()) {
			json playerData;
			file >> playerData;
			file.close();

			//Thông báo đã tìm thành công file người chơi 
			cout << "Player found! Loading ..." << endl;
			
			//Trả về thông tin người chơi
			return Player(
				playerData["username"].get<string>(),
				playerData["gameWon"].get<double>(),
				playerData["gamePlayed"].get<double>(),
				playerData["winrate"].get<double>(),
				playerData["favoriteHand"].get<int>()
			);
		}
	}
	//Nếu không tồn tại thì thông báo
	cout << "Player not found...Creating new player..." << endl;
	
	//Tạo người chơi mới với thông tin mặc định
	Player newPlayer(username);
	newPlayer.recordPlayer();
	return newPlayer;
}