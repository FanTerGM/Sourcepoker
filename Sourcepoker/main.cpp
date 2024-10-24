
#include "gameObject.h"
#include "gameModes.h"

int main() {
    cout << "Welcome to poker!" << endl;
    cout << "Please choose your mode" << endl; 
    cout << "1. Texas Hold 'em" << endl;
    cout << "2. Draw 5 Poker" << endl;
    cout << "3. Stud Poker" << endl;
    int choice; cin >> choice;
    int numberOfPlayer, numberOfNPCs; cin >> numberOfPlayer >> numberOfNPCs;
    House house(new Table(numberOfPlayer, numberOfNPCs));
    if (choice == 3) house.setTable(new studTable(numberOfPlayer, numberOfNPCs));
    if (choice == 2) house.setTable(new drawTable(numberOfPlayer, numberOfNPCs));


    // Deal cards to the player's hand and table.
    house.dealCardtoPlayers();
    house.dealFlop();
    // Display the player's hand and the community card.
    cout << "Community cards:" << endl;
    house.showCards();
    cout << "Player hand:" << endl;
    house.showPlayersHand();
    
    return 0;
}
