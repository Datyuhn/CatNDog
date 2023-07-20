#include "Collision.h"

Collision::Collision() {

}
Collision::~Collision() {}

bool Collision::checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
    // Check for collision
    if (rect1.x + rect1.w >= rect2.x && 
        rect1.x <= rect2.x + rect2.w &&
        rect1.y + rect1.h >= rect2.y &&
        rect1.y <= rect2.y + rect2.h) {
        return true;
    }
    return false;
}

