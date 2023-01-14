#include "TileEmpty.hpp"


TileEmpty::TileEmpty(int x, int y, std::vector<std::vector<Tile *>> * cells) :
Tile(x, y, cells) {

}

int TileEmpty::update() {
    return 0;
}