#ifndef _MAP_H_DEFINED_
#define _MAP_H_DEFINED_

#include "defs.h"

class Map {
    private:
        MapTile map[MAP_WIDTH][MAP_HEIGHT] = {MAP_EMPTY};
    public:
        Map() {}
        ~Map() {}
        MapTile getTile(const int x, const int y) { return map[x][y]; }
        bool setTile(int x, int y, MapTile val);
        void putFood();
        void reset();
};

#endif