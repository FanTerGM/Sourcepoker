#include <gameObject.h>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Player::Player(string name) : username(name) {}

gameRecord::gameRecord(): gameMode("default5"), earning(0){}

gameRecord::gameRecord(string gameMode, int earning, vector<Card> hand) : gameMode(gameMode), earning(earning), hand(hand) {};

Player::Player(string name, double win, vector<gameRecord> gameHistory, double winrate, int money, int rank, vector<Card> favoriteHand)
	: username(name), gameWon(win), gameHistory(gameHistory), winrate(winrate), money(money), rank(rank), favoriteHand(favoriteHand){}


int Player::getPlayerRank() const { return rank; }
string Player::getPlayerUsername() const { return username; }
vector<Card> Player::getPlayerfavoriteHand() const { return favoriteHand; }
double Player::getPlayertWinrate() const { return winrate; }

void Player::updateGameHistoryAndWinrate(bool won, const vector<Card>& hand, string gameMode, int earning) {
	gameHistory.push_back(gameRecord(gameMode, earning, hand));
	if (won) gameWon++;
	money += earning;	
}

void Player::recordPlayer(const string & directory, const Player& player) const {
	json playerData;

	std::filesystem::create_directories(directory);

	std::ofstream outFile(directory + username + ".json");
	if (outFile.is_open()) {
		outFile << json(player).dump(4);
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

void to_json(nlohmann::json& j, const gameRecord& g) {
	j = nlohmann::json{
		{"gameMode", g.gameMode},
		{"earning", g.earning},
		{"hand", g.hand}
	};
}

void from_json(const nlohmann::json& j, gameRecord& g) {
	j.at("gameMode").get_to(g.gameMode);
	j.at("earning").get_to(g.earning);
	j.at("hand").get_to(g.hand);
}

void to_json(nlohmann::json& j, const Player& p){
	j = nlohmann::json{
		{"username", p.username},
		{"gameWon", p.gameWon},
		{"gameHistory", p.gameHistory},
		{"winrate", p.winrate},
		{"money", p.money},
		{"rank", p.rank},
		{"favoriteHand", p.favoriteHand}
	};
}

void from_json(const nlohmann::json& j, Player& p) {
	j.at("username").get_to(p.username);
	j.at("gameWon").get_to(p.gameWon);
	j.at("gameHistory").get_to(p.gameHistory);
	j.at("winrate").get_to(p.winrate);
	j.at("money").get_to(p.money);
	j.at("rank").get_to(p.rank);
	j.at("favoriteHand").get_to(p.favoriteHand);
}


