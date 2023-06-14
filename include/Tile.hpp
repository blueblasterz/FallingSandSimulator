#pragma once

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

class Matrix;

class Tile {
public:
    Tile(int x, int y, int scale, int height);

    virtual ~Tile();
    
    void move(int new_x, int new_y);

    void dmove(int dx, int dy);

    std::array<int,2> get_pos();
    int get_y();
    int get_x();
    sf::Color get_color();

    virtual int update(Matrix * matrix) = 0;

    // void set_rectangle(sf::RectangleShape * rect);
    sf::RectangleShape * get_rectangle();

protected:

    void update_rectangle(
        bool update_pos = true,
        bool update_color = false,
        bool update_scale = false);

    int m_x;
    int m_y;

    int m_scale;

    int m_height;

    sf::Color m_color;
    sf::RectangleShape * m_rect;
};