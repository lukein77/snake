#include "Player.h"

Player::Player() : length(3), direction(DIR_RIGHT), lives(3), alive(true) {
    head->x = 10;
    head->y = 10;
}

void Player::update(Map *map) {
    // update map tiles for the head and tail, no need to update the rest of the body
    position_t tail = body[length-1];
    map->setTile(tail.x, tail.y, MAP_EMPTY);
    
    // first move the body
    for (int i = length-1; i > 0; i--) {
        body[i] = body[i-1]; 
    }
    // then move the head
    switch (direction) {
        case DIR_UP:
            head->y--;
            if (head->y == -1) head->y = MAP_HEIGHT - 1;
            break;
        
        case DIR_DOWN:
            head->y++;
            if (head->y == MAP_HEIGHT) head->y = 0;
            break;

        case DIR_LEFT:
            head->x--;
            if (head->x == -1) head->x = MAP_WIDTH - 1;
            break;

        case DIR_RIGHT:
            head->x++;
            if (head->x == MAP_WIDTH) head->x = 0;
            break;
    }
    // now check if the movement was actually valid
    if (map->getTile(head->x, head->y) != MAP_SNAKE) {
        if (map->getTile(head->x, head->y) == MAP_FOOD) {
            grow();
            map->putFood();
        }
        map->setTile(head->x, head->y, MAP_SNAKE);
    } else {
        // the snake crashed into itself
        alive = false;
        lives--;
        printf("YOU'RE DEAD, lives: %d\n", lives);
    }
}

position_t *Player::getPos(int i) {
    return (&body[i]);
}

void Player::grow() {
    if (length < MAX_LENGTH) length++;
    body[length-1] = body[length-2];
}

void Player::setDirection(const int dir) {
    if ((direction + 2) % 4 != dir) {
        direction = dir;
        /* this doesn't work
        for (int i = 0; i < length/2; i++) {
            std::swap(*head, body[length-i-1]);
        }
        */
    }
}

void Player::respawn(Map *map) {
    map->reset();
    length = INITIAL_LENGTH;
    *head = INITIAL_POS;
    alive = true;
}