
#include "gameObject.h"



int main() {
    Table table;

    // Deal cards to the player's hand and table.
    table.dealCardtoPlayers();
    table.dealFlop();
    // Display the player's hand and the community card.
    cout << "Community cards:" << endl;
    table.showCards();
    cout << "Player hand:" << endl;
    table.showPlayersHand();
    
    return 0;
}
