#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"


class Simulator {
public:
    Simulator(int w=800, int h=600, int tile_size=1);


    int mainloop();

    void add_tile(Tile * tile);
    void remove_tile(int i);

    int update_display();

    int update_tiles();


protected:
    std::vector<std::pair<Tile *,sf::RectangleShape>> m_tiles;
    // std::vector<std::pair<Tile *,sf::RectangleShape>> m_tiles;
    int m_win_w; // width of screen in px
    int m_win_h; // height of screen in px

    int m_tile_size; // tile size in pixel
    int m_w; // width of screen in tiles
    int m_h; // height of screen in tiles

    sf::RenderWindow m_window;

    sf::RectangleShape shape;

};
