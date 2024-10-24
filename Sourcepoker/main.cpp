
#include "gameObject.h"
#include "gameModes.h"

int main() {
    cout << "Welcome to poker!" << endl;
    cout << "Please choose your mode" << endl; 
    cout << "0. Default 5 cards" << endl;
    cout << "1. Texas Hold 'em" << endl;
    cout << "2. Draw 5 Poker" << endl;
    cout << "3. Stud Poker" << endl;
    int choice; cout <<"Enter a number to choose your mode: ";  cin >> choice;

    int numberOfPlayers, numberOfNPCs;
    cout << "Enter the number of players: "; cin >> numberOfPlayers;
    cout << "Enter the amount of NPC: "; cin >> numberOfNPCs;

    House house(new Table(numberOfPlayers, numberOfNPCs));

    if (choice == 3) house.setTable(new studTable(numberOfPlayers, numberOfNPCs));
    if (choice == 2) house.setTable(new drawTable(numberOfPlayers, numberOfNPCs));
    if (choice == 1) house.setTable(new texasTable(numberOfPlayers, numberOfNPCs));
    house.populateTable();

    // Deal cards to the player's hand and table.
    house.dealCardtoPlayers();

    // Display the player's hand and the community card.
    cout << "Community cards:" << endl;
    house.showCards();
    cout << "Player hand:" << endl;
    house.showPlayersHand();
    
    return 0;
}
