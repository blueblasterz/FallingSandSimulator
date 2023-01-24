#include "TileSand.hpp"

using std::cout, std::endl;

TileSand::TileSand(int x, int y, int w, int h, TYPE_CELLMATRIX * cells, 
                   TYPE_CELLMATRIX * cells_future) :
Tile(x, y, w, h, cells, cells_future) {

    // cout << x << " " << y << endl;
    m_color = sf::Color::Yellow;
    m_rect->setFillColor( m_color );
}

TileSand::~TileSand() {}

int TileSand::update() {
    static int count = 0;
    count++;
    // cout << "update (" << m_x << "," << m_y << ") " << count << ": ";
    if(m_y <= 1) {
        m_cells_future->at(m_x).at(m_y) = m_cells->at(m_x).at(m_y);
        m_rect->setPosition(m_x, m_h - m_y);
        // cout << "1" << "> (" << m_x << "," << m_y << ")" << endl;
        return 0;
    }
    
    // printf("%p %p\n", m_cells, m_cells_future);
    if( m_cells->at(m_x).at(m_y-1) == nullptr
    &&  m_cells_future->at(m_x).at(m_y-1) == nullptr ) {
        // cout << m_x << " " << m_y <<endl;
        m_cells_future->at(m_x).at(m_y-1) = m_cells->at(m_x).at(m_y);
        m_cells_future->at(m_x).at(m_y) = nullptr;
        m_y -= 1;
        m_rect->setPosition(m_x, m_h - m_y);
        // cout << "2" << "> (" << m_x << "," << m_y << ")"<< endl;
    }
    else {
        int rd = (rand()%2)*2 -1;
        if( m_x+rd >= 0 && m_x+rd < m_w 
        &&         m_cells->at(m_x+rd).at(m_y-1) == nullptr 
        &&  m_cells_future->at(m_x+rd).at(m_y-1) == nullptr ) {
            // cout << "1" << endl;
            m_cells_future->at(m_x+rd).at(m_y-1) = m_cells->at(m_x).at(m_y);
            m_cells_future->at(m_x).at(m_y) = nullptr;
            m_y -= 1;
            m_x += rd;
            m_rect->setPosition(m_x, m_h - m_y);
            // cout << "3" << "> (" << m_x << "," << m_y << ")"<< endl;
        }
        else if( m_x-rd >= 0 && m_x-rd < m_w 
        &&         m_cells->at(m_x-rd).at(m_y-1) == nullptr
        &&  m_cells_future->at(m_x-rd).at(m_y-1) == nullptr ) {
            // cout << "0" << endl;
            m_cells_future->at(m_x-rd).at(m_y-1) = m_cells->at(m_x).at(m_y);
            m_cells_future->at(m_x).at(m_y) = nullptr;
            m_y -= 1;
            m_x -= rd;
            m_rect->setPosition(m_x, m_h - m_y);
            // cout << "4" << "> (" << m_x << "," << m_y << ")"<< endl;
        }
        else {
            m_cells_future->at(m_x).at(m_y) = m_cells->at(m_x).at(m_y);
            m_rect->setPosition(m_x, m_h - m_y);
            // cout << "5" << "> (" << m_x << "," << m_y << ")"<< endl;
        }
    }
    return 0;
}