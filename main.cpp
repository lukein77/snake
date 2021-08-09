#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "Player.h"
#include "Map.h"


SDL_Renderer *renderer;
SDL_Window *window;


bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to open window: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
		return false;
	}

    return true;
}

int main(int argc, char *argv[]) {

    bool running = false;

    if (initSDL()) {
        running = true;
    }
    
    Player player;
    Map map;
    SDL_Event event;

    map.setTile(player.getX(), player.getY(), MAP_SNAKE);
    map.putFood();

    long playerUpdateTime = SDL_GetTicks();
    long drawTime = SDL_GetTicks();
    long deadTime = SDL_GetTicks();

    while (running) {

        // events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            running = false;
                            break;
                        case SDL_SCANCODE_UP:
                            player.setDirection(DIR_UP);
                            break;
                        case SDL_SCANCODE_DOWN:
                            player.setDirection(DIR_DOWN);
                            break;
                        case SDL_SCANCODE_LEFT:
                            player.setDirection(DIR_LEFT);
                            break;
                        case SDL_SCANCODE_RIGHT:
                            player.setDirection(DIR_RIGHT);
                            break;
                        case SDL_SCANCODE_LCTRL:
                            player.grow();
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        if (player.isAlive()) {
            if (SDL_GetTicks() - playerUpdateTime == 250) {
                player.update(&map);
                playerUpdateTime = SDL_GetTicks();
                if (!player.isAlive()) {
                    deadTime = SDL_GetTicks();
                }
            }
        } else {
            if (player.getLives() > 0) {
                if (SDL_GetTicks() - deadTime == 1500) {
                    player.respawn(&map);
                    playerUpdateTime = SDL_GetTicks();
                }
            } else {
                running = false;    // game over
            }
        }

        if (SDL_GetTicks() - drawTime == 50) {
            
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            // drawing
            SDL_RenderClear(renderer);

            // draw the map
            SDL_Rect r;
            r.w = TILE_SIZE;
            r.h = TILE_SIZE;
            for (int i = 0; i < MAP_WIDTH; i++) {
                for (int j = 0; j < MAP_HEIGHT; j++) {
                    MapTile tile = map.getTile(i, j);
                    if (tile != MAP_EMPTY) {
                        r.x = i * TILE_SIZE;
                        r.y = j * TILE_SIZE;
                        if (tile == MAP_SNAKE) {
                            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
                        } else if (tile == MAP_FOOD) {
                            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
                        }
                        SDL_RenderFillRect(renderer, &r);
                    }
                }
            }

            // render everything
            SDL_RenderPresent(renderer);

            drawTime = SDL_GetTicks();
        }

    }

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}