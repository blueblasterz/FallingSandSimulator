#pragma once

#include <iostream>
#include <vector>
// #include <format>
#include <SFML/Graphics.hpp>
#include "TileEmpty.hpp"
#include "TileSand.hpp"


class Simulator {
public:
    Simulator(int w=800, int h=600, int tile_size=1);


    int mainloop();

    void add_tile(Tile * tile);

    template<class TileType>
    void add_tile(int x, int y);
    
    void remove_tile(int i);

    // int update_display();

    int update_tiles();

    
    TYPE_CELLMATRIX * get_cells();
    TYPE_CELLMATRIX * get_cells_future();

protected:
    std::vector<Tile *> m_tiles;

    TYPE_CELLMATRIX * m_cells;
    TYPE_CELLMATRIX * m_cells_future;
    
    int m_win_w; // width of screen in px
    int m_win_h; // height of screen in px

    int m_tile_size; // tile size in pixel
    int m_w; // width of screen in tiles
    int m_h; // height of screen in tiles

    int m_nb_tiles; // number of tiles drawn on the screen

    sf::RenderWindow * m_window;

};
