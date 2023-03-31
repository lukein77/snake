#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"
#include "Player.h"
#include "Map.h"
#include "DrawingManager.h"
#include <string>

DrawingManager drawingManager;

int main(int argc, char *argv[]) {

    bool running = false;

    if (drawingManager.initialize()) {
        running = true;
    } else {
        return 1;
    }
    
    Player player;
    Map map;
    SDL_Event event;

    player.setTexture(drawingManager.loadTexture("white.png"));

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
            // update player if still alive
            if (SDL_GetTicks() - playerUpdateTime == 200) {
                player.update(&map);
                playerUpdateTime = SDL_GetTicks();
                if (!player.isAlive()) {
                    deadTime = SDL_GetTicks();
                }
            }
        } else {
            // freeze player before respawning
            if (SDL_GetTicks() - deadTime == 1500) {
                if (player.getLives() > 0) {
                    player.respawn(&map);
                    playerUpdateTime = SDL_GetTicks();
                } else {
                    running = false;
                }
            }
        }

        if (SDL_GetTicks() - drawTime == 50) {
            SDL_Color white = {255, 255, 255, 255};
            SDL_Color green = {128, 168, 50, 255};

            drawingManager.clearScene();

            drawingManager.drawMap(&map);

            std::string points = std::to_string(player.getPoints());
            drawingManager.renderText(points.c_str(), 0, SCREEN_HEIGHT - 15, FONTSIZE_SMALL, green);

            if (!player.isAlive()) {
                if (player.getLives() > 0) {
                    drawingManager.renderText("YOU DIED", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 15, FONTSIZE_LARGE, white, true);
                    std::string lives = "LIVES: " + std::to_string(player.getLives());
                    drawingManager.renderText(lives.c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 15, FONTSIZE_LARGE, white, true);
                } else {
                    drawingManager.renderText("GAME OVER", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, FONTSIZE_LARGE, white, true);
                }
            }

            drawingManager.renderScene();
            drawTime = SDL_GetTicks();
        }

    }

    
    SDL_Quit();
    return 0;
}