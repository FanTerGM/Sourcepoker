#include "../headers/visual/CheckPlayer.h"

CheckPlayer::CheckPlayer(const std::string& name) : username(name) {}

std::string CheckPlayer::getUsername() const {
    return username;
}

void CheckPlayer::saveProfile(const std::string& path) {
    std::ofstream file(path + username + ".txt");
    file << "Player Name: " << username << std::endl;
    file.close();
}

bool CheckPlayer::loadProfile(const std::string& name) {
    std::ifstream file(name + ".txt");
    return file.good();  // Kiểm tra xem file có tồn tại không
}