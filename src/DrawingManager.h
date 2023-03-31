#ifndef _DRAW_H_INCLUDED_
#define _DRAW_H_INCLUDED_

#include "defs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Map.h"
#include <map>
#include <string>

class DrawingManager {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        TTF_Font *fonts[3];

        std::map <std::string, SDL_Texture*> textureCache;

        void clearTextureCache();
        SDL_Texture *addTextureToCache(std::string filename);
    public:
        DrawingManager();
        ~DrawingManager();
        bool initialize();
        void drawMap(Map *map);
        void clearScene();
        void renderScene();
        Texture *loadTexture(const char *filename);
        void blit(Texture *texture, SDL_Rect *clip = NULL);
        void blit(Texture *texture, int x, int y, SDL_Rect *clip = NULL);
        void renderText(const char *text, int x, int y, int size, SDL_Color color, bool centered=false);
};

#endif