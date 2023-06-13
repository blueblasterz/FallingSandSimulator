#include "Simulator.hpp"

#include "Matrix.hpp"

using std::cout, std::cin, std::endl;

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
m_w(w), m_h(h), m_scale(scale) {
    m_win_w = m_w * m_scale;
    m_win_h = m_h * m_scale;

    srand(time(NULL));
    // srand(0);


    m_nb_tiles = 0;
    m_window = nullptr;

    m_tiles = new Matrix(m_w,m_h);

}


void Simulator::start() {
    int framerate = 60;


    m_window = new sf::RenderWindow(
        sf::VideoMode(m_win_w, m_win_h),
        "Falling Sand Sim",
        sf::Style::Titlebar | sf::Style::Close);


    m_window->setVerticalSyncEnabled(false);
    m_window->setFramerateLimit(framerate);

    bool paused = false;
    int step = 0;
    int iter= 0;

    bool mouse_pressed_left = false;

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
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        mouse_pressed_left = true;
                    }

                    break;
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        mouse_pressed_left = false;
                    }
                    break;
                default:
                    break;
            }
        }
        if(mouse_pressed_left) {
            int x = sf::Mouse::getPosition(*m_window).x / m_scale;
            int y = sf::Mouse::getPosition(*m_window).y / m_scale;

            if( m_tiles->get_tile(x,y) == nullptr ) {
                // Tile * t = new TileSand(x,y,m_scale);
                // cout << "new tile : " 
                //      << *(t->get_rectangle()) << "\n"
                //      << t->get_color() << endl;
                m_tiles->set_tile(x,y,new TileSand(x,y,m_scale));
                // t = m_tiles->get_tile(x,y);
                // cout << "added tile at "<< x << "," << y << endl;
                // cout << m_tiles->get_tile(x,y)->get_color() << endl;
            }
        }
        this->clear();
        this->draw_tiles();
        m_window->display();

        iter++;
        if(iter%framerate == 0) {
            cout << "iter : " << iter << endl;
        }
    }
}

void Simulator::render_tile(int x, int y, Tile * t) {

}

void Simulator::clear() {
    m_window->clear();
}

void Simulator::draw_tiles() {
    for( auto line : m_tiles->get_matrix()) {
        for( Tile * t : line) {
            if( t != nullptr) {
                m_window->draw( *(t->get_rectangle()) );
                // cout << "drawing " << *(t->get_rectangle()) << endl;
            }
        }
    }
}


