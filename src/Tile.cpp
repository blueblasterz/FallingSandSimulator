#include "Tile.hpp"
#include <iostream>

using std::cout, std::endl;

Tile::Tile(int x, int y,  std::vector<std::vector<Tile *>> * cells) 
: m_x(x), m_y(y), m_cells(cells) {
    if((*m_cells)[m_x][m_y] != nullptr) {
        delete (*m_cells)[m_x][m_y];
    }
    (*m_cells)[x][y] = this;
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
    // std::array<int,2> res;
    // res[0] = m_x;
    // res[1] = m_y;
    // // cout << "in get_pos :" << endl
    // // << m_x << " " << m_y << endl
    // // << res[0] << " " << res[1] << endl;
    // return res;
    return {m_x,m_y};
}

int Tile::get_x() {
    return m_x;
}
int Tile::get_y() {
    return m_y;
}