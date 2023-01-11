#include "Tile.hpp"

Tile::Tile(int x, int y) : m_x(x), m_y(y) {

}

void Tile::move(int new_x, int new_y) {
    m_x = new_x;
    m_y = new_y;
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