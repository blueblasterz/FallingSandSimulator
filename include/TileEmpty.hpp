#pragma once

#include <vector>
#include <iostream>
#include "Tile.hpp"

class TileEmpty : public Tile {
public:

    TileEmpty(int x, int y, int w, int h, TYPE_CELLMATRIX * cells, 
              TYPE_CELLMATRIX * cells_future);

    ~TileEmpty();

    int update();

};