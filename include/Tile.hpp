#pragma once

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

#define TYPE_CELLMATRIX \
std::vector<std::vector<Tile *>>

class Tile {
public:
    Tile(int x, int y, int w, int h, TYPE_CELLMATRIX * cells, 
         TYPE_CELLMATRIX * cells_future);;

    void move(int new_x, int new_y);

    void dmove(int dx, int dy);

    std::array<int,2> get_pos();
    int get_y();
    int get_x();
    sf::Color get_color();

    virtual int update() = 0;

    // void set_rectangle(sf::RectangleShape * rect);
    sf::RectangleShape * get_rectangle();

    void draw(sf::RenderWindow * win);


    
    

protected:
    int m_x;
    int m_y;

    int m_w;
    int m_h;

    TYPE_CELLMATRIX * m_cells;
    TYPE_CELLMATRIX * m_cells_future;

    sf::Color m_color;
    sf::RectangleShape * m_rect;
};