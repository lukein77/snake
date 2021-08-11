#ifndef _DRAW_H_INCLUDED_
#define _DRAW_H_INCLUDED_

#include "defs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Map.h"

class DrawingManager {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        TTF_Font *fonts[3];
    public:
        DrawingManager();
        ~DrawingManager();
        bool initialize();
        void drawMap(Map *map);
        void clearScene();
        void renderScene();
        void blit(Texture *texture, int x, int y);
        void renderText(const char *text, int x, int y, int size, SDL_Color color, bool centered=false);
};

#endif