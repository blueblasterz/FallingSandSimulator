#pragma once

#include <iostream>
#include <vector>
#include "TileSand.hpp"
#include "TileRock.hpp"

class Tile;

class Matrix {
public:

    using iterator = std::vector<int>::iterator;
    
    Matrix(int w, int h, int scale);
    ~Matrix();

    // returns the tile at x,y
    Tile * get_tile(int x, int y);

    // sets the tile at x,y (overwrites the previous one)
    void set_tile(int x, int y, Tile * tile);

    template<typename TileType, 
            typename = std::enable_if_t<std::is_base_of<Tile, TileType>::value>>
    void set_tile(int x, int y);

    // deletes tile at (x,y) (if there is one)
    // and sets (x,y) to nullptr
    void delete_tile(int x, int y);

    // deletes all the tiles
    void delete_all();

    // moves tile in (x,y) to (x_dest,y_dest)
    // the tile at dest (if there is one) is freed (deleted)
    // (x,y) is set to nullptr 
    // if dest is out of the display, then the tile is deleted
    void move_tile(int x, int y, int x_dest,int y_dest);

    // calls Tile::set_future_landed_state on tile at x,y
    // if there is no tile there, does nothing
    // 1 => updated to false
    // 2 => updated to true
    void set_tile_landed_state(int x, int y, int state);

    // returns true if the position is inbounds
    bool inbounds(int x, int y);

    // returns an editable reference to the matrix of tiles
    // TODO / possible improvement :
    // implement an iterator over a Matrix, to do a "for(Tile * t : matrix)"
    std::vector<std::vector<Tile *>> & get_matrix();

    // gives a vector of points between 2 positions
    std::vector<std::pair<int,int>> get_points_between(
        int x1, int y1, int x2, int y2,
        bool debug = false
    );

    friend std::ostream& operator<<(std::ostream& os, const Matrix& obj);

private:

    // contains all the tiles
    // we technically don't know the size yet, so vector
    std::vector<std::vector<Tile *>> m_matrix;

    // width and height of the grid of tile
    int m_w;
    int m_h;

    // size in pixels of the tiles
    int m_scale;

};


template<typename TileType, 
         typename = std::enable_if_t<std::is_base_of<Tile, TileType>::value>>
void Matrix::set_tile(int x, int y) {
    Tile * t = new TileType(x, y, m_scale, m_h);
    this->set_tile(x,y,t);
}