#ifndef _TILE_H_
#define _TILE_H_

class Tile {
public:
    int x_;
    int y_;

    Tile(int x, int y);
    bool operator <(const Tile& otroTile) const;
};

#endif
