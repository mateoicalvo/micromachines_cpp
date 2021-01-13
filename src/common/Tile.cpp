#include "includes/common/Tile.h"

Tile::Tile(int x, int y) :
    x_(x),
    y_(y) {
}

bool Tile::operator<(const Tile& otro) const {
    if (this->x_ < otro.x_) {
        return true;
    } else if (this->x_ == otro.x_) {
        if (this->y_ < otro.y_) {
            return true;
        }
    }
    return false;
}
