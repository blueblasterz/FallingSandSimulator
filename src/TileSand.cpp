#include "TileSand.hpp"

using std::cout, std::endl;

TileSand::TileSand(int x, int y, int scale) :
Tile(x, y, scale) {

    // cout << x << " " << y << endl;
    m_color = sf::Color::Yellow;
    m_rect->setFillColor( m_color );
}

TileSand::~TileSand() {}

int TileSand::update() {
    
    return 0;
}