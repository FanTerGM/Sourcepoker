#include <gameObject.h>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/*Defenition for class Player, used to represent the user*/

Player::Player() {}

Player::Player(string name) : username(name) {}


Player::Player(string name, double win, double winrate, int money, int rank, array<int, 10>& handPlayed) 
	: username(name), gameWon(win), winrate(winrate), money(money), rank(rank), handPlayed(handPlayed) {}

bool Player::operator > (const Player& other) const {
	return Evaluator(getHand()) > Evaluator(other.getHand());
}

bool Player::operator == (const Player& other) const {
	return Evaluator(getHand()) == Evaluator(other.getHand());
}


int Player::getPlayerRank() const { return rank; }
string Player::getPlayerUsername() const { return username; }
double Player::getPlayertWinrate() const { return winrate; }
int Player::getGamePlayed() const {
	int res = 0;
	for (const int& i : handPlayed) res += i;
	return res; 
}

void Player::updateGameHistoryAndWinrate(bool won, int earning) {
	int index = static_cast<int>(Evaluator(getHand()).strengthRank());
	handPlayed[index]++;
	if (won) gameWon++;
	winrate = gameWon * 100/ getGamePlayed();
	money += earning;
	recordPlayer();
}

void Player::getFavoriteHand() const {
	int HandId = distance(handPlayed.begin(), max_element(handPlayed.begin(), handPlayed.end()));
	cout << Evaluator().IntToEnumName(HandId) << endl;
}

void Player::updateRanking(int newRank) { rank = newRank; }

void Player::recordPlayer(const string & directory) const {

	if (username.find("AI_") != string::npos) return;
	std::filesystem::create_directories(directory);

	std::ofstream outFile(directory + username + ".json");
	if (outFile.is_open()) {
		outFile << json(*this).dump(4);
		outFile.close();
	}
}


Player Player::loadPlayer(const string& username, const string& directory) {
	string filename = directory + username + ".json";


	cout << "Loading player ..." << endl;
	

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
			return playerData.get<Player>();
		}
	}
	//Nếu không tồn tại thì thông báo
	cout << "Player not found...Creating new player..." << endl;
	
	//Tạo người chơi mới với thông tin mặc định
	Player newPlayer(username);
	newPlayer.recordPlayer();
	return newPlayer;
}



void to_json(nlohmann::json& j, const Player& p){
	 j = nlohmann::json {
		{"username", p.username},
		{"gameWon", p.gameWon},
		{"winrate", p.winrate},
		{"money", p.money},
		{"rank", p.rank},
		{"handPlayed", p.handPlayed}
	};
}

void from_json(const nlohmann::json& j, Player& p) {
	j.at("username").get_to(p.username);
	j.at("gameWon").get_to(p.gameWon);
	j.at("winrate").get_to(p.winrate);
	j.at("money").get_to(p.money);
	j.at("rank").get_to(p.rank);
	j.at("handPlayed").get_to(p.handPlayed);
}
