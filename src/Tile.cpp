#include "Tile.hpp"
#include <iostream>

using std::cout, std::endl;

Tile::Tile(int x, int y, int w, int h, TYPE_CELLMATRIX * cells, 
           TYPE_CELLMATRIX * cells_future)
: m_x(x), m_y(y), m_w(w), m_h(h), m_cells(cells),
  m_cells_future(cells_future) {

    if(m_cells->at(m_x).at(m_y) != nullptr) {
        delete m_cells->at(m_x).at(m_y);
    }
    m_cells->at(m_x).at(m_y) = this;

    m_color = sf::Color::White;

    m_rect = new sf::RectangleShape();
    m_rect->setFillColor( m_color );
    m_rect->setPosition(m_x, m_y);
    
    // printf("created Tile with\n%p %p\n", m_cells, m_cells_future);
}

void Tile::move(int new_x, int new_y) {
    // m_cells->at(m_x).at(m_y) = nullptr; // empty current cell

    m_x = new_x;
    m_y = new_y;

    // if(m_cells->at(m_x).at(m_y) != nullptr) {
    //     delete m_cells->at(m_x).at(m_y); // if new cell is not empty
    // }
    // m_cells->at(m_x).at(m_y) = this;
}

void Tile::dmove(int dx, int dy) {
    m_x += dx;
    m_y += dy;
}

std::array<int,2> Tile::get_pos() {
    return {m_x,m_y};
}

int Tile::get_x() {
    return m_x;
}
int Tile::get_y() {
    return m_y;
}

sf::Color Tile::get_color() {
    return m_color;
}

sf::RectangleShape * Tile::get_rectangle() {
    return m_rect;
}

void Tile::draw(sf::RenderWindow * win) {
    win->draw(*m_rect);
}