#pragma once

#include <iostream>
#include <vector>

class Tile;

class Matrix {
public:

    using iterator = std::vector<int>::iterator;
    
    Matrix(int w, int h);
    ~Matrix();

    // returns the tile at x,y
    Tile * get_tile(int x, int y);

    // sets the tile at x,y (overwrites the previous one)
    void set_tile(int x, int y, Tile * tile);

    std::vector<std::vector<Tile *>> & get_matrix();


    friend std::ostream& operator<<(std::ostream& os, const Matrix& obj);

private:

    // contains all the tiles
    // we technically don't know the size yet, so vector
    std::vector<std::vector<Tile *>> m_matrix;

    // width and height of the grid of tile
    int m_w;
    int m_h;
};