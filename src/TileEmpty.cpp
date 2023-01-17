#include "TileEmpty.hpp"

using std::cout, std::endl;

TileEmpty::TileEmpty(int x, int y, int w, int h, TYPE_CELLMATRIX * cells, 
                     TYPE_CELLMATRIX * cells_future):
Tile(x, y, w, h, cells, cells_future) {

}

int TileEmpty::update() {
    return 0;
}