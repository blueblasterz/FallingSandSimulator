#include "TileEmpty.hpp"

using std::cout, std::endl;

TileEmpty::TileEmpty(int x, int y, std::vector<std::vector<Tile *>> * cells) :
Tile(x, y, cells) {
    // cout << m_x << " " << m_y << endl;
    Tile * t = cells->at(m_x).at(m_y);
}

int TileEmpty::update() {
    return 0;
}