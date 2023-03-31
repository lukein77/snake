#ifndef _DEFS_H_DEFINED_
#define _DEFS_H_DEFINED_

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TILE_SIZE 16

#define MAP_WIDTH 40
#define MAP_HEIGHT 30

#define INITIAL_POS {10,10}
#define INITIAL_LENGTH 3
#define MAX_LENGTH 255

enum FontSize {
    FONTSIZE_DEFAULT,
    FONTSIZE_SMALL,
    FONTSIZE_LARGE
};

enum MapTile {
    MAP_EMPTY,
    MAP_SNAKE,
    MAP_FOOD,
    MAP_WALL
};

enum {
    DIR_UP,
    DIR_LEFT,
    DIR_DOWN,
    DIR_RIGHT
};

typedef struct position_t {
    int x;
    int y;
} position_t;

typedef struct Texture {
    SDL_Texture *image;
    SDL_Rect rect;
} Texture;

#endif