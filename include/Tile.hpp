#pragma once

#include <array>
#include <vector>

class Tile {
public:
    Tile(int x, int y, std::vector<std::vector<Tile *>> * cells);

    void move(int new_x, int new_y);

    void dmove(int dx, int dy);

    std::array<int,2> get_pos();
    int get_y();
    int get_x();

    virtual int update() = 0;



    
    

protected:
    int m_x;
    int m_y;
    std::vector<std::vector<Tile *>> * m_cells;
};