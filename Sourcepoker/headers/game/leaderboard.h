#pragma once

class leaderboard {
public:
	leaderboard();
	void display();
	
private:
	vector<pair<string, double>> playerLeaderboard; 
};