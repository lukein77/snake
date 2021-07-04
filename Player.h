#ifndef _PLAYER_H_DEFINED_
#define _PLAYER_H_DEFINED_

#include "SDL2/SDL.h"
#include "defs.h"
#include "Map.h"

class Player {
    private:
        int x;
        int y;
        
        position_t body[MAX_LENGTH] = {0,0};
        position_t *head = body;
        int length = 3;
        int direction=0;
        SDL_Texture *texture;
    public:
        Player();
        ~Player() {}
        int getX() { return head->x; }
        int getY() { return head->y; }
        int getLength() { return length; }
        position_t* getPos(int i);
        void setX(const int x) { this->x = x; }
        void setY(const int y) { this->y = y; }
        void setDirection(const int dir);
        void update(Map *map);
        void grow();
};

#endif