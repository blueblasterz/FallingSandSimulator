#include "TileRock.hpp"
#include "Matrix.hpp"

TileRock::TileRock(int x, int y, int scale, int height) :
Tile(x,y,scale,height) {
    m_color = create_color(120,120,150,255,40);
    m_rect->setFillColor( m_color );
}

TileRock::~TileRock() {}


int TileRock::update(Matrix * matrix) {
    (void)matrix;
    return 0;
}