#ifndef _MAP_H_DEFINED_
#define _MAP_H_DEFINED_

#include "defs.h"
#include <vector>

class Map {
    private:
        std::vector<position_t> obstacles;
        position_t food;

    public:
        Map();
        ~Map() {}
        bool isWall(position_t pos);
        bool isFood(position_t pos);
        void putFood();
        void initialize();
        std::vector<position_t> &getObstacles() { return obstacles; }
        position_t &getFood() { return food; }
};

#endif