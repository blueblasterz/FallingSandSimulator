#pragma once

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

// #include "Matrix.hpp"
class Matrix;
#include "utils.hpp"

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

    virtual int update(Matrix * matrix) =0;

    // void set_rectangle(sf::RectangleShape * rect);
    sf::RectangleShape * get_rectangle();

    // get/set for m_landed
    bool is_landed();
    void set_landed_state(bool state);

    int get_future_landed_state();
    void set_future_landed_state(int state);

protected:

    void update_rectangle(
        bool update_pos = true,
        bool update_color = false,
        bool update_scale = false);

    int m_x;
    int m_y;

    int m_scale;

    int m_height;

    // tracks if the particle was landed on the previous frame
    bool m_landed;

    // tracks if during the last frame, the particle was updated
    // 0 => not updated
    // 1 => updated to false
    // 2 => updated to true
    int m_future_landed_state;

    sf::Color m_color;
    sf::RectangleShape * m_rect;
};