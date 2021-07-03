#ifndef _MAP_H_DEFINED_
#define _MAP_H_DEFINED_

#include "defs.h"

class Map {
    private:
        unsigned char map[MAP_WIDTH][MAP_HEIGHT];
    public:
        unsigned char getTile(const int x, const int y) { return map[x][y]; }
        bool setTile(int x, int y, MapTile val);
        void putFood();
};

#endif