#include "Map.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>

Map::Map() {
    initialize();
}

void Map::initialize() {
    putFood();
}

bool Map::isWall(position_t pos) {
    int length = obstacles.size();
    for (int i = 0; i < length; i++) {
        if (pos.x == obstacles.at(i).x && pos.y == obstacles.at(i).y) {
            return true;
        } 
    }
    return false;
}

bool Map::isFood(position_t pos)
{
    return (pos.x == food.x && pos.y == food.y);
}

void Map::putFood()
{
    srand(time(NULL));
    position_t new_food;
    do {
        new_food.x = rand() % MAP_WIDTH;
        new_food.y = rand() % MAP_HEIGHT;
    } while (isWall(new_food));
    this->food = new_food;
}