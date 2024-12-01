#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <filesystem>
#include <fstream>


#include "../headers/core/Card.h"
#include "../headers/core/Deck.h"
#include "../headers/core/Player.h"
#include "../headers/core/Table.h"
#include "../headers/core/Hand.h"
#include "../headers/game/leaderboard.h"
#include "../headers/visual/Menu.h"
#include "../headers/visual/ImgCard.h"
#include "../headers/game/GameState.h"
#include "../headers/visual/PlayerSelection.h"
#include "../headers/visual/PlayerInfoInput.h"

//extern GameState currentState;