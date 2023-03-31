#ifndef _PLAYER_H_DEFINED_
#define _PLAYER_H_DEFINED_

#include "SDL2/SDL.h"
#include "defs.h"
#include <list>
#include "Map.h"

class Player {
    private:
        int direction;
        int lives;
        
        std::list<position_t> body;
        bool alive;
        unsigned int points;
        
        SDL_Texture *texture;
    public:
        Player();
        ~Player() {}
        int getLength() { return body.size(); }
        int getLives() { return lives; }
        int getPoints() { return points; }
        void setDirection(const int dir);
        void update(Map *map);
        void respawn(Map *map);
        void initialize();
        bool isAlive() { return alive; }
        bool isSnake(position_t pos);
        std::list<position_t> &getBody() { return body; }
};

#endif