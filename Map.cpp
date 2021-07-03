#include "Map.h"
#include <cstdlib>
#include <ctime>

bool Map::setTile(int x, int y, MapTile val) {
    if ((x >= 0 && x < MAP_WIDTH) && (y >= 0 && y < MAP_HEIGHT)) {
        map[x][y] = val;
        return true;
    }
    return false;
}

void Map::putFood() {
    srand(time(NULL));
    int x, y;
    do {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
    } while (map[x][y] != MAP_EMPTY);
    map[x][y] = MAP_FOOD;
}