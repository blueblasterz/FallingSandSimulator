#include "Simulator.hpp"

using std::cout, std::cin, std::endl;

Simulator::Simulator(int w, int h, int tile_size): 
m_win_w(w), m_win_h(h), m_tile_size(tile_size) {
    m_w = m_win_w / tile_size;
    m_h = m_win_h / tile_size;

    m_cells = new std::vector<std::vector<Tile *>>();
    m_cells->resize(m_w);
    for(int i = 0; i < m_w; i++) {
        (*m_cells)[i].resize(m_h);
    }


}

int Simulator::mainloop() {

    m_window = new sf::RenderWindow(
        sf::VideoMode(m_win_w, m_win_h),
        "Falling Sand Simulator");

    sf::Clock clock = sf::Clock();

    float fps = 120.;

    sf::Time requested_fps = sf::microseconds(1000000./fps);

    bool mouse_pressed = false;
    int frame_count=0;
    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    m_window->close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left)
                        mouse_pressed = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Left)
                        mouse_pressed = false;
                    break;
            }
        }
        m_window->clear();

        if(mouse_pressed) {
            int x = sf::Mouse::getPosition(*m_window).x;
            int y = sf::Mouse::getPosition(*m_window).y;
            if(0 < x && x < m_w && 0 < y && y < m_h)
                add_tile(new TileEmpty(x/m_tile_size, 
                                       m_h - y/m_tile_size,
                                       m_cells));
        }

        update_tiles();

        m_window->display();

        sf::Time dt = clock.getElapsedTime();
        sf::sleep(requested_fps-dt);
        clock.restart();
        frame_count++;
        if(frame_count%(int)(200) == 0)
            cout << "frame " << frame_count << " " 
            << m_tiles.size() << " tiles\n";
    }

    delete m_window;
    return 0;
}


void Simulator::add_tile(Tile * tile) {
    sf::RectangleShape * newr = new sf::RectangleShape();
    // sf::RectangleShape newr;
    newr->setSize(sf::Vector2f(m_tile_size,m_tile_size));
    newr->setFillColor(sf::Color(255,255,255));
    newr->setPosition(tile->get_x(), m_h-tile->get_y());
    m_tiles.push_back(std::pair(tile,newr));
}
void Simulator::remove_tile(int i) {
    m_tiles.erase(m_tiles.begin()+i);
}

// int Simulator::update_display() {
//     // m_window.clear();
//     // // int t = update_tiles();
//     // m_window.display();
//     return 0;
// }

int Simulator::update_tiles() {
    for(auto t : m_tiles) {
        if(t.first->get_y() > 1) {
            t.first->dmove(0,-1);

            t.second->setPosition(t.first->get_x(), m_h-t.first->get_y());
        }         
        m_window->draw(*t.second);
    }

    return 0;
}



std::vector<std::vector<Tile *>> * Simulator::get_cells() {
    return m_cells;
}






