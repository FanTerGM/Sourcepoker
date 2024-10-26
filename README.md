# Sourcepoker

This is a project that aim to make a poker game that can host various variants of poker

## File Structure

The project has the following file structure:

```
- headers/
    - Card.h
    - Deck.h
    - Hand.h
    - Player.h
    - Table.h
- game/
    - House.h
    - leaderboard.h
- modes/
    - drawTable.h
    - studTable.h
    - superTable.h
    - texasTable.h
- include/
    - nlohmann/
        - gameModes.h
        - gameObject.h
- Resources/
    - playerinfo
- src/
    - core/
        - Card.cpp
        - Deck.cpp
        - Hand.cpp
        - Player.cpp
        - Table.cpp
    - game/
        - House.cpp
        - leaderboard.cpp
    - modes/
        - drawTable.cpp
        - studTable.cpp
        - superTable.cpp
        - texasTable.cpp
```
## Description

This project is a game that includes various game modes, such as Draw Table, Stud Table, Super Table, and Texas Table. The project uses header files and source files to define the different components of the game, including Card, Deck, Hand, Player, and Table.

The file structure is organized into different directories, such as `headers`, `game`, `modes`, `include`, `Resources`, and `src`, to separate the different components of the project.

## Dependencies

This project depends on the following external libraries:

- `nlohmann/json`: A JSON library used for game modes and game objects.

## Building and Running

To build and run this project, you will need to have a C++17 compiler installed on your system. You can then use the appropriate build tool (e.g., Make, CMake, etc.) to compile the project and run the game.

## Contributing

If you would like to contribute to this project, please feel free to submit a pull request or create an issue on the project's repository.
