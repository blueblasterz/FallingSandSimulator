#include "TileSand.hpp"
#include "Matrix.hpp"

using std::cout, std::endl;

TileSand::TileSand(int x, int y, int scale, int height) :
Tile(x, y, scale, height) {

    // cout << x << " " << y << endl;
    m_color = sf::Color::Yellow;
    m_rect->setFillColor( m_color );
}

TileSand::~TileSand() {
    cout << "deleted" << endl;
}

int TileSand::update(Matrix * matrix) {
    if(m_y == 0) {
        return 0;
    }
    if(matrix->get_tile(m_x,m_y-1) == nullptr) {
        matrix->move_tile(m_x,m_y,m_x,m_y-1);
        return 0;
    }
    int dx = rand()%2 ? 1 : -1;
    if( matrix->inbounds(m_x+dx,m_y-1)
     && matrix->get_tile(m_x+dx,m_y-1) == nullptr ) {
        matrix->move_tile(m_x,m_y,m_x+dx,m_y-1);
        return 0;
    }
    else if( matrix->inbounds(m_x-dx,m_y-1) 
          && matrix->get_tile(m_x-dx,m_y-1) == nullptr ) {
        matrix->move_tile(m_x,m_y,m_x-dx,m_y-1);
        return 0;
    }
    return 0;
}