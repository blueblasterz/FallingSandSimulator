#pragma once

#include <vector>
#include <iostream>
#include "Tile.hpp"

class TileSand : public Tile {
public:

    TileSand(int x, int y, int scale, int height );

    ~TileSand();
    
    int update(Matrix * matrix);

};