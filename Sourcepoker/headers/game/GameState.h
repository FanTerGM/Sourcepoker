#pragma once

enum GameState { //quản lý trạng thái game
    MAIN_MENU,
    PLAYER_SELECTION,
    PLAY_MENU, //PLAY_MENU have 3 diffirents game mode
    GAME_DEFAULT,
    GAME_STUD,
    GAME_SUPER,
    //GAME_TEXAS,
    LEADERBOARD,
    CREDIT,
    EXIT
};