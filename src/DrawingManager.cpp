#include "DrawingManager.h"

DrawingManager::DrawingManager() {}

DrawingManager::~DrawingManager() {
    clearTextureCache();
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
		fonts[FONTSIZE_DEFAULT] = TTF_OpenFont("PressStart2P.ttf", 15);
        fonts[FONTSIZE_SMALL] = TTF_OpenFont("PressStart2P.ttf", 12);
        fonts[FONTSIZE_LARGE] = TTF_OpenFont("PressStart2P.ttf", 18);
	}
    
    return true;
}

void DrawingManager::drawMap(Map *map) {
    // draw the map
    SDL_Rect r;
    r.w = TILE_SIZE;
    r.h = TILE_SIZE;
    Texture *playerTexture = loadTexture("white.png");
    Texture *foodTexture = loadTexture("yellow.png");
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            MapTile tile = map->getTile(i, j);
            if (tile != MAP_EMPTY) {
                r.x = i * TILE_SIZE;
                r.y = j * TILE_SIZE;
                if (tile == MAP_SNAKE) {
                    //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
                    blit(playerTexture, r.x, r.y);
                } else if (tile == MAP_FOOD) {
                    //SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
                    blit(foodTexture, r.x, r.y);
                }
                //SDL_RenderFillRect(renderer, &r);
            }
        }
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



void DrawingManager::clearTextureCache() {
	std::map <std::string, SDL_Texture*> :: iterator it;
	for (it = textureCache.begin(); it != textureCache.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
	textureCache.clear();
}

SDL_Texture *DrawingManager::addTextureToCache(std::string filename) {

	SDL_Texture *texture = IMG_LoadTexture(renderer, ("graphics/"+filename).c_str());
	if (!texture) {
		printf("Error: %s\n", IMG_GetError());
	} else {
		printf("Done\n");
	}

	textureCache.insert(std::pair<std::string, SDL_Texture*>(filename, texture));

	return texture;
}

Texture *DrawingManager::loadTexture(const char *filename) {

	// searches for texture in cache, if not found loads from disk
	
	Texture *texture = new Texture;

	std::string strFilename;
	strFilename.assign(filename);

	std::map <std::string, SDL_Texture*> :: iterator it;
	it = textureCache.find(strFilename);

	if (it != textureCache.end()) {
		texture->image = it->second;
	} else {
		printf("Loading %s from disk... ", filename);
		texture->image = addTextureToCache(strFilename);
	}

	// get image width and height and store it in SDL_Rect
	SDL_QueryTexture(texture->image, NULL, NULL, &(texture->rect.w), &(texture->rect.h));
	
	return texture;
}

void DrawingManager::blit(Texture *texture, SDL_Rect *clip) {
	if (clip != NULL) {
		texture->rect.w = clip->w;
		texture->rect.h = clip->h;
	}
	SDL_RenderCopy(renderer, texture->image, clip, &(texture->rect));
}

void DrawingManager::blit(Texture *texture, int x, int y, SDL_Rect *clip) {
	
	texture->rect.x = x;
	texture->rect.y = y;

	if (clip != NULL) {
		texture->rect.w = clip->w;
		texture->rect.h = clip->h;
	}
	
	SDL_RenderCopy(renderer, texture->image, clip, &(texture->rect));
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