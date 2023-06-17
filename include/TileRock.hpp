#pragma once

#include "Tile.hpp"

class TileRock: public Tile {
public:
    TileRock(int x, int y, int scale, int height);
    ~TileRock();


    int update(Matrix * matrix);

private:


};