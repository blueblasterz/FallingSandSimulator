#include "Tile.hpp"
#include <iostream>

#include "Matrix.hpp"

using std::cout, std::endl;

Tile::Tile(int x, int y, int scale, int height)
: m_x(x), m_y(y), m_scale(scale), m_height(height) {

    m_color = sf::Color::White;

    m_rect = new sf::RectangleShape();

    this->update_rectangle(true,true,true);
    
    // printf("created Tile at %i,%i scale %i\n", m_x, m_y, m_scale);
    // cout << m_rect->getPosition().x << endl;
}

Tile::~Tile() {}

void Tile::move(int new_x, int new_y) {

    m_x = new_x;
    m_y = new_y;

    this->update_rectangle(true,false,false);
    // if(m_cells->at(m_x).at(m_y) != nullptr) {
    //     delete m_cells->at(m_x).at(m_y); // if new cell is not empty
    // }
    // m_cells->at(m_x).at(m_y) = this;
}

void Tile::dmove(int dx, int dy) {
    m_x += dx;
    m_y += dy;
    this->update_rectangle(true,false,false);
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

void Tile::update_rectangle(
    bool update_pos,
    bool update_color,
    bool update_scale
    ) {
    if(update_pos) {
        m_rect->setPosition( m_x*m_scale, (m_height-m_y-1)*m_scale );
    }
    if(update_color) {
        m_rect->setFillColor(m_color);
    }
    if(update_scale) {
        m_rect->setSize(sf::Vector2f(m_scale, m_scale));
    }
}