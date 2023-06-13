#pragma once

#include <iostream>
#include <vector>
// #include <format>
#include "TileSand.hpp"

class Matrix;
namespace sf {
    class RenderWindow;
}

class Simulator {
public:
    Simulator(int w=800, int h=600, int scale=1);

    // starts the simulator
    // this function does not return until the window is closed
    void start();

    // renders a single tile, at position x,y
    void render_tile(int x, int y, Tile * t);

    // clear everything that is on screen
    // (only visually : it does not modify m_tiles)
    void clear();

    // draws every tiles
    void draw_tiles();


protected:
    Matrix * m_tiles;
    

    int m_w; // width of screen in tiles
    int m_h; // height of screen in tiles
    int m_scale; // tile size in pixel

    int m_win_w;
    int m_win_h;

    int m_nb_tiles; // number of tiles drawn on the screen

    sf::RenderWindow * m_window;
};
