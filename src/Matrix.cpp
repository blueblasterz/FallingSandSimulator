#include "Matrix.hpp"

#include "Tile.hpp"

using std::vector;

std::ostream& operator<<(std::ostream& os, const Matrix& obj) {
    for (const auto& inner : obj.m_matrix) {
        for (const auto& value : inner) {
            os << value << ' ';
        }
        os << '\n';
    }
    return os;
}


Matrix::Matrix(int w, int h) :
    m_w(w),
    m_h(h)
{
    m_matrix.resize(m_h);
    for(int i = 0; i < m_h; i++) {
        m_matrix.at(i).resize(m_w);
        for(int j = 0; j < m_w; j++) {
            m_matrix.at(i).at(j) = 0;
        }
    }
    printf("created matrix of size (%i,%i)\n", m_w, m_h);
}

Matrix::~Matrix() {}


void Matrix::set_tile(int x, int y, Tile * tile) {
    if( x < 0 || x >= m_w || y < 0 || y >= m_h ) {
        std::cerr << "invalid set_title : at " << x << "," << y << std::endl;
        return;
    }
    m_matrix.at(y).at(x) = tile;
}

Tile * Matrix::get_tile(int x, int y) {
    if( x < 0 || x >= m_w || y < 0 || y >= m_h ) {
        return nullptr;
    }
    return m_matrix.at(y).at(x);
}

vector<vector<Tile *>> & Matrix::get_matrix() {
    return m_matrix;
}




