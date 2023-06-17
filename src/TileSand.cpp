#include "TileSand.hpp"
#include "Matrix.hpp"

using std::cout, std::endl;



TileSand::TileSand(int x, int y, int scale, int height) :
Tile(x, y, scale, height) {

    // cout << x << " " << y << endl;
    m_color = create_color(sf::Color::Yellow, 20);
    m_rect->setFillColor( m_color );
}

TileSand::~TileSand() {
    // cout << "deleted" << endl;
}

int TileSand::update(Matrix * matrix) {
    // if(m_y == 0) {
    //     return 0;
    // }
    int prev_x = m_x;
    int prev_y = m_y;
    // cout << m_x << "," << m_y << " landed:" << m_landed << " future:" 
    // << m_future_landed_state << endl;
    bool moved = false;
    if(matrix->get_tile(m_x, m_y-1) == nullptr) {
        matrix->move_tile(m_x, m_y, m_x, m_y-1);
        moved = true;
    }
    else if(!m_landed /*|| rand()%100 >= 0*/){
        
        int dx = rand()%2 ? 1 : -1;
        if( matrix->get_tile(m_x+dx, m_y-1) == nullptr
        && matrix->get_tile(m_x+dx, m_y) == nullptr ) {
            matrix->move_tile(m_x, m_y, m_x+dx, m_y-1);
            moved = true;
            return 0;
        }
        else if( matrix->get_tile(m_x-dx, m_y-1) == nullptr 
            && matrix->get_tile(m_x-dx, m_y) == nullptr ) {
            matrix->move_tile(m_x, m_y, m_x-dx, m_y-1);
            moved = true;
            return 0;
        }
    }
    if(moved) {
        m_landed = false;
        // matrix->set_tile_landed_state(prev_x-1,prev_y, 1);
        // matrix->set_tile_landed_state(prev_x+1,prev_y, 1);
        matrix->set_tile_landed_state(m_x-1,m_y+1, 1);
        matrix->set_tile_landed_state(m_x+1,m_y+1, 1);
    }
    else {
        m_landed = true;
    }
    if(m_future_landed_state != 0) {
        if(m_future_landed_state > 2) {
            m_landed = m_future_landed_state == 4;
            m_future_landed_state = 0;
        }
        else {
            m_future_landed_state += 2;
        }
    }
    return 0;
}