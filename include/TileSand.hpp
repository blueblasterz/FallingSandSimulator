#pragma once

#include <vector>
#include <iostream>
#include "Tile.hpp"

class TileSand : public Tile {
public:

    TileSand(int x, int y, int w, int h, TYPE_CELLMATRIX * cells, 
             TYPE_CELLMATRIX * cells_future);

    ~TileSand();
    
    int update();

};