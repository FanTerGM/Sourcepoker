#include <gameObject.h>
#include <gameModes.h>


void Games() {
    cout << "0. Default 5 cards" << endl;
    cout << "1. Texas Hold 'em" << endl;
    cout << "2. Draw 5 Poker" << endl;
    cout << "3. Stud Poker" << endl;
    int choice; cout << "Enter a number to choose what to do: ";  cin >> choice;

    int numberOfPlayers, numberOfNPCs;
    cout << "Enter the number of humnan players: "; cin >> numberOfPlayers;
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
}

int main() {
    while (true){
        cout << "Welcome to poker!" << endl;
        cout << "Please choose what to do" << endl;
        cout << "1. Play poker" << endl;
        cout << "2. view Leaderboard" << endl;
        cout << "3. Exit program" << endl;
        int choice; cout << "Enter a number to choose what to do: ";  cin >> choice;

        if (choice == 1) Games();
        if (choice == 2) leaderboard().display();
        if (choice == 3) return 0;
    }   
}
