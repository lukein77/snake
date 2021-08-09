#ifndef _PLAYER_H_DEFINED_
#define _PLAYER_H_DEFINED_

#include "SDL2/SDL.h"
#include "defs.h"
#include "Map.h"

class Player {
    private:
        int length;
        int direction;
        int lives;
        position_t body[MAX_LENGTH] = {0,0};
        position_t *head = body;
        bool alive;
        
        SDL_Texture *texture;
    public:
        Player();
        ~Player() {}
        int getX() { return head->x; }
        int getY() { return head->y; }
        int getLength() { return length; }
        int getLives() { return lives; }
        position_t* getPos(int i);
        void setX(const int x) { head->x = x; }
        void setY(const int y) { head->y = y; }
        void setDirection(const int dir);
        void update(Map *map);
        void grow();
        void respawn(Map *map);
        bool isAlive() { return alive; }
};

#endif