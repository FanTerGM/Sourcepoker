#include <gameObject.h>
#include <gameModes.h>

superTable::superTable(int numberOfPlayers, int numberOfNPCs) : Table (numberOfPlayers, numberOfNPCs){}

string superTable::getModeName(){
    return "super";
}
