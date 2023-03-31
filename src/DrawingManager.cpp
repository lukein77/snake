#include "DrawingManager.h"

DrawingManager::DrawingManager() {}

DrawingManager::~DrawingManager() {
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

bool DrawingManager::initialize() {
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
    
    if (TTF_Init() == -1) { 
		printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
		return false;
	} else {
		fonts[FONTSIZE_DEFAULT] = TTF_OpenFont("data/PressStart2P.ttf", 15);
        fonts[FONTSIZE_SMALL] = TTF_OpenFont("data/PressStart2P.ttf", 12);
        fonts[FONTSIZE_LARGE] = TTF_OpenFont("data/PressStart2P.ttf", 18);
	}
    
    return true;
}

void DrawingManager::drawMap(Map *map) {
    SDL_Rect r;
    r.w = TILE_SIZE;
    r.h = TILE_SIZE;

    // draw walls
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0x00);
    std::vector<position_t> &obstacles = map->getObstacles();
    for (auto &p : obstacles) {
        r.x = p.x * TILE_SIZE;
        r.y = p.y * TILE_SIZE;
        SDL_RenderFillRect(renderer, &r);
    }

    // draw food
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    position_t &food = map->getFood();
    r.x = food.x * TILE_SIZE;
    r.y = food.y * TILE_SIZE;
    SDL_RenderFillRect(renderer, &r);
}

void DrawingManager::drawPlayer(std::list<position_t> &body) {
    // draw snake
    SDL_Rect r;
    r.w = TILE_SIZE;
    r.h = TILE_SIZE;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
    for (auto &p : body) {
        r.x = p.x * TILE_SIZE;
        r.y = p.y * TILE_SIZE;
        SDL_RenderFillRect(renderer, &r);
    }
}

void DrawingManager::clearScene() {
    // clear everything
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
}

void DrawingManager::renderScene() {
    // render everything
    SDL_RenderPresent(renderer);
}

void DrawingManager::blit(Texture *texture, int x, int y) {
	
	texture->rect.x = x;
	texture->rect.y = y;
	
	SDL_RenderCopy(renderer, texture->image, NULL, &(texture->rect));
}

void DrawingManager::renderText(const char *text, int x, int y, int size, SDL_Color color, bool centered) {

	SDL_Surface *surface = TTF_RenderText_Solid(fonts[size], text, color);

	if (surface) {
		Texture texture;
		texture.image = SDL_CreateTextureFromSurface(renderer, surface);
		texture.rect.w = surface->w;
		texture.rect.h = surface->h;

		if (centered) {
			x = x - surface->w / 2;
			y = y - surface->h / 2;
		}

		blit(&texture, x, y);
	} else {
		printf("Error rendering text: %s\n", TTF_GetError());
	}
}