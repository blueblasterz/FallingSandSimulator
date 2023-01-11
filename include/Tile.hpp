#pragma once

#include <array>

class Tile {
public:
    Tile(int x, int y);

    void move(int new_x, int new_y);

    void dmove(int dx, int dy);

    std::array<int,2> get_pos();
    int get_y();
    int get_x();
    

protected:
    int m_x;
    int m_y;
};