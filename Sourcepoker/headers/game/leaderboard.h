#pragma once

class leaderboard {
public:
	leaderboard();
	void display();
	
private:
	std::vector<Player> playerLeaderboard; 
};