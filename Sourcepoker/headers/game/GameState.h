#pragma once

enum GameState { //quản lý trạng thái game
    MAIN_MENU,
    PLAYER_SELECTION,
    INPUT_PLAYER_INFO,
    PLAY_MENU, //PLAY_MENU have 2 diffirents game mode
    GAME_DEFAULT,
    GAME_STUD_5,
    GAME_STUD_7,
    GAME_DRAW,
    WAITING_FOR_INPUT,
    LEADERBOARD,
    EXIT
};

extern GameState currentState;
