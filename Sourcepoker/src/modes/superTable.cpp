#include <gameObject.h>
#include <gameModes.h>

superTable::superTable(int numberOfPlayers, int numberOfNPCs) : Table (numberOfPlayers, numberOfNPCs){}

std::string superTable::getModeName() const{
    return "super";
}
