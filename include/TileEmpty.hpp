#pragma once

#include <vector>
#include <iostream>
#include "Tile.hpp"

class TileEmpty : public Tile {
public:

    TileEmpty(int x, int y, std::vector<std::vector<Tile *>> * cells);

    int update();

};