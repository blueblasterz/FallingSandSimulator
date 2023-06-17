#include "Simulator.hpp"

#include "utils.hpp"

#include <ranges>

#define get_mouse_x(win) sf::Mouse::getPosition(*(win)).x / m_scale
#define get_mouse_y(win) (m_win_h - 1 - sf::Mouse::getPosition(*(win)).y) / m_scale

using std::cout, std::cin, std::endl, std::cerr, std::min, std::max;

// overload for sf::Color operator<<
std::ostream& operator<<(std::ostream& os, const sf::Color& obj) {
    os << "(" << (int)obj.r << "," << (int)obj.g << "," << (int)obj.b << "," 
       << (int)obj.a << ")";
    return os;
}


// overload for sf::Vector2f operator<<
std::ostream& operator<<(std::ostream& os, const sf::Vector2f& obj) {
    os << "(" << obj.x << "," << obj.y << ")";
    return os;
}


// overload for sf::RectangleShape operator<<
std::ostream& operator<<(std::ostream& os, const sf::RectangleShape& obj) {
    os << "@" << obj.getPosition() << " dim" << obj.getSize();
    return os;
}


Simulator::Simulator(int w, int h, int scale): 
m_w(w), m_h(h), m_scale(scale), m_n_tile_types(2) {
    m_win_w = m_w * m_scale;
    m_win_h = m_h * m_scale;

    srand(time(NULL));
    // srand(0);


    m_nb_tiles = 0;
    m_window = nullptr;

    m_tiles = new Matrix(m_w,m_h, m_scale);


    m_selected_tiletype = 0;

}


void Simulator::start() {
    int framerate = 60;


    m_window = new sf::RenderWindow(
        sf::VideoMode(m_win_w, m_win_h),
        "Falling Sand Sim",
        sf::Style::Titlebar | sf::Style::Close);

    cout << "true window size : " << m_win_w << "x" << m_win_h << endl;

    m_window->setVerticalSyncEnabled(false);
    m_window->setFramerateLimit(framerate);

    bool paused = false;
    int step = 0;
    int iter= 0;

    bool mouse_pressed_left = false;
    bool mouse_pressed_right = false;

    // number of frame during which mouse_pressed_left is ignored
    int ignore_mouse_pressed = 0;

    int creating_square = 0;

    int prev_x = -1;
    int prev_y = -1;
    int curr_x = -1;
    int curr_y = -1;

    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    m_window->close();
                    break;
                case sf::Event::KeyPressed:
                    // cout << "keypress" << endl;
                    if(event.key.code == sf::Keyboard::P) {
                        paused = !paused;
                    }
                    else if(event.key.code == sf::Keyboard::S) {
                        step++;
                    }
                    else if(event.key.code == sf::Keyboard::D) {
                        // debug
                        int x1 = 5;
                        int y1 = 5;
                        int x2 = 10;
                        int y2 = 20;
                        // m_tiles->set_tile(x1,y1, new TileSand(x1,y1, m_scale));
                        // m_tiles->set_tile(x2,y2, new TileSand(x2,y2, m_scale));
                        for(auto pos : m_tiles->get_points_between(x1,y1,x2,y2)) {
                            cout << pos << endl;
                        }
                    }
                    else if(event.key.code == sf::Keyboard::B) {
                        // cout << "pressed b" << endl;
                        creating_square = 2;
                    }
                    else if(event.key.code == sf::Keyboard::Tab) {
                        m_selected_tiletype = (m_selected_tiletype+1)%m_n_tile_types;
                    }
                    else if(event.key.code == sf::Keyboard::BackSpace) {
                        m_tiles->delete_all();
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        mouse_pressed_left = true;
                    }
                    else if(event.mouseButton.button == sf::Mouse::Right) {
                        mouse_pressed_right = true;
                    }
                    if(creating_square != 0) {
                        creating_square--;
                        if (creating_square == 1) {
                            // cout << "first step creating square" << endl;
                            prev_x = get_mouse_x(m_window);
                            prev_y = get_mouse_y(m_window);
                        }
                        else {
                            // cout << "2nd step creating square" << endl;
                            curr_x = get_mouse_x(m_window);
                            curr_y = get_mouse_y(m_window);
                            for (int x = min(prev_x,curr_x); x < max(prev_x,curr_x); x++) {
                                for (int y = min(prev_y,curr_y); y < max(prev_y,curr_y); y++) {
                                    // m_tiles->set_tile(x,y,
                                    //     new TileSand(x,y,m_scale,m_h)
                                    // );
                                    // m_tiles->set_tile<TileSand>(x,y);
                                    if(mouse_pressed_left) {
                                        this->add_tile(x,y);
                                    }
                                    else {
                                        m_tiles->delete_tile(x,y);
                                    }
                                }
                            }
                            ignore_mouse_pressed = 10;
                        }
                    }   
                    break;
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        mouse_pressed_left = false;
                    }
                    else if(event.mouseButton.button == sf::Mouse::Right) {
                        mouse_pressed_right = false;
                    }
                    curr_x = -1;
                    curr_y = -1;
                    break;
                default:
                    break;
            }
        }
        if(ignore_mouse_pressed != 0) {
            ignore_mouse_pressed--;
        }
        if(mouse_pressed_left && ignore_mouse_pressed == 0) {
            if(creating_square != 0) {
                ;
            }
            else {

                prev_x = curr_x != -1 ? curr_x : get_mouse_x(m_window);
                prev_y = curr_y != -1 ? curr_y : get_mouse_y(m_window);
                curr_x = get_mouse_x(m_window);
                curr_y = get_mouse_y(m_window);

                auto list_pts = m_tiles->get_points_between(prev_x,prev_y,curr_x,curr_y, false);
                for (auto pos : list_pts) {
                    
                    if( m_tiles->get_tile(pos.first,pos.second) == nullptr ) {
                        // m_tiles->set_tile(
                        //     pos.first,
                        //     pos.second,
                        //     new TileSand(pos.first,pos.second,m_scale,m_h));
                        // m_tiles->set_tile<TileSand>(
                        //     pos.first,
                        //     pos.second);
                        this->add_tile(pos.first, pos.second);
                    }
                }
            }
        }
        if(mouse_pressed_right) {
            curr_x = get_mouse_x(m_window);
            curr_y = get_mouse_y(m_window);
            m_tiles->delete_tile(curr_x,curr_y);
        }
        if(paused) {
            if (step != 0) {
                step--;
                this->iteration();
            }
        }
        else {
            this->iteration();
        }
        this->clear();
        this->draw_tiles();
        m_window->display();

        iter++;
        if(iter%framerate == 0) {
            int n_tiles = 0;
            for(auto line : m_tiles->get_matrix()) {
                for(auto tile : line) {
                    if (tile != nullptr) {
                        n_tiles++;
                    }
                }
            }
            // cout << "iter : " << iter << " nb_tiles : " << n_tiles << endl;
        }
    }
}



void Simulator::add_tile(int x, int y) {
    switch(m_selected_tiletype) {
        case 0:
            m_tiles->set_tile<TileSand>(x,y);
            break;
        case 1:
            m_tiles->set_tile<TileRock>(x,y);
            break;
        default:
            cerr << "invalid value for m_selected_tiletype : "
            << m_selected_tiletype  << endl;
            // m_selected_tiletype = 0;
    }
}

void Simulator::render_tile(int x, int y, Tile * t) {
    (void)x;
    (void)y;
    (void)t;
    cerr << "not implemented : Simulator::render_tile" << endl;
}

void Simulator::clear() {
    m_window->clear();
}

void Simulator::draw_tiles() {
    for( auto line : m_tiles->get_matrix()) {
        for( Tile * t : line ) {
            if( t != nullptr) {
                m_window->draw( *(t->get_rectangle()) );
                // cout << "drawing " << *(t->get_rectangle()) << endl;
            }
        }
    }
}


void Simulator::iteration() {
    // if(rand()%2 == 0) {
    //     for( auto line : m_tiles->get_matrix()) {
    //         for( Tile * t : line ) {
    //             if( t != nullptr) {
    //                 t->update(m_tiles);
    //             }
    //         }
    //     }
    // }
    // else {
    //     for( auto line : m_tiles->get_matrix()) {
    //         for( Tile * t : line | std::views::reverse) {
    //             if( t != nullptr) {
    //                 t->update(m_tiles);
    //             }
    //         }
    //     }

    // }
    for( auto line : m_tiles->get_matrix()) {
        if(rand()%2 == 0) {
            for( Tile * t : line ) {
                if( t != nullptr) {
                    t->update(m_tiles);
                }
            }
        }
        else {
            for( Tile * t : line | std::views::reverse) {
                if( t != nullptr) {
                    t->update(m_tiles);
                }
            }
        }
    }
}