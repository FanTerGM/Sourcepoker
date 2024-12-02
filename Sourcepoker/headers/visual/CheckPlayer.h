#pragma once
#include <string>
#include <fstream>

class CheckPlayer {
public:
    CheckPlayer(const std::string& name);
    std::string getUsername() const;
    void saveProfile(const std::string& path);
    static bool loadProfile(const std::string& name);

private:
    std::string username;
};

