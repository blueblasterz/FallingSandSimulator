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

    // deletes tile at (x,y) (if there is one)
    // and sets (x,y) to nullptr
    void delete_tile(int x, int y);

    // moves tile in (x,y) to (x_dest,y_dest)
    // the tile at dest (if there is one) is freed (deleted)
    // (x,y) is set to nullptr 
    // if dest is out of the display, then the tile is deleted
    void move_tile(int x, int y, int x_dest,int y_dest);

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
};