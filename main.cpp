#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "defs.h"
#include "Player.h"



SDL_Renderer *renderer;
SDL_Window *window;

uint8_t map[40][30] = {0};

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
    Player player;
    if (initSDL()) {
        running = true;
    }
    
    SDL_Event event;

    // throw some food
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        int x = rand() % MAP_WIDTH;
        int y = rand() % MAP_HEIGHT;
        map[x][y] = MAP_FOOD;
    }
    map[player.getX()][player.getY()] = MAP_SNAKE;

    long playerUpdateTime = SDL_GetTicks();
    long drawTime = SDL_GetTicks();

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

        if (SDL_GetTicks() - playerUpdateTime == 300) {
            player.update(map);
            playerUpdateTime = SDL_GetTicks();
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
                    if (map[i][j] != MAP_EMPTY) {
                        r.x = i * TILE_SIZE;
                        r.y = j * TILE_SIZE;
                        if (map[i][j] == MAP_SNAKE) {
                            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
                        } else if (map[i][j] == MAP_FOOD) {
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