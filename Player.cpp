#include "Player.h"

Player::Player() : direction(DIR_RIGHT), lives(3), alive(true), points(0) {
    initialize();
}

void Player::update(Map *map) {
    position_t head = body.front();
    position_t new_head = {head.x, head.y};
    
    // first calculate the snake's next position
    switch (direction) {
        case DIR_UP:
            new_head.y--;
            if (new_head.y == -1) new_head.y = MAP_HEIGHT - 1;
            break;
        
        case DIR_DOWN:
            new_head.y++;
            if (new_head.y == MAP_HEIGHT) new_head.y = 0;
            break;

        case DIR_LEFT:
            new_head.x--;
            if (new_head.x == -1) new_head.x = MAP_WIDTH - 1;
            break;

        case DIR_RIGHT:
            new_head.x++;
            if (new_head.x == MAP_WIDTH) new_head.x = 0;
            break;
    }

    // now check against obstacles or food
    if ((map->isWall(new_head)) || (isSnake(new_head))) {
        printf("CRASH! head(x,y): %d,%d\n", new_head.x, new_head.y);
        // the snake crashed into itself or against a wall
        alive = false;
        lives--;
        printf("YOU'RE DEAD, lives: %d\n", lives);
    }
    else {
        body.push_front(new_head);
        if ((map->isFood(new_head))) {
            points++;
            map->putFood();
        } else {
            body.pop_back();    // only remove tail if did not eat food
        }
    }

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
    map->initialize();
    alive = true;
}

void Player::initialize() {
    position_t p1 = {20, 20};
    position_t p2 = {20, 21};
    position_t p3 = {20, 22};
    body.push_back(p1);
    body.push_back(p2);
    body.push_back(p3);
}

bool Player::isSnake(position_t pos) {
    /*for (auto &p : body) {
        if (pos.x == p.x && pos.y && p.y) {
            printf("Crashed with itself\n");
            return true;
        }
    }*/
    return false;
}
