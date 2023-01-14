#include "Simulator.hpp"

using std::cout, std::cin, std::endl;

Simulator::Simulator(int w, int h, int tile_size): 
m_win_w(w), m_win_h(h), m_tile_size(tile_size) {
    m_w = m_win_w / tile_size;
    m_h = m_win_h / tile_size;

    m_cells = new std::vector<std::vector<Tile *>>();
    m_cells->resize(m_w);
    for(int i = 0; i < m_w; i++) {
        m_cells->at(i).resize(m_h);
        for(int j = 0; j < m_h; j++) {
            m_cells->at(i).at(j) = nullptr;
        }
    }

    if( m_cells->at(2).at(2) != nullptr ) {
        exit(3);
    }


}

int Simulator::mainloop() {

    m_window = new sf::RenderWindow(
        sf::VideoMode(m_win_w, m_win_h),
        "Falling Sand Simulator");

    sf::Clock clock_logique = sf::Clock();
    sf::Clock clock_boucle = sf::Clock();
    sf::Clock clock_fps = sf::Clock();

    const float fps = 600000000000000000.;

    sf::Time requested_fps = sf::microseconds(1000000./fps);

    bool mouse_pressed = false;
    int frame_count=0;
    int compteur_tile = 0;

    char title[128] = {0};

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
            if(0 < x && x < m_win_w && 0 < y && y < m_win_h) {
                // cout << compteur_tile << " : " << x << " " << y << endl;
                compteur_tile++;
                if ( m_cells->at(x/m_tile_size).at(m_h - y/m_tile_size) 
                    == nullptr ) {
                    Tile * t = new TileEmpty(x/m_tile_size, 
                                       m_h - y/m_tile_size,
                                       m_cells);
                    add_tile(t);
                }
            }
        }

        update_tiles();

        m_window->display();

        m_window->setTitle( title );

        sf::Time dt = clock_logique.getElapsedTime();
        sf::sleep(requested_fps-dt);

        if(frame_count%32 == 0) {

            dt = clock_fps.getElapsedTime();
            snprintf(title, 128, "Falling Sand Simulator : frame %i (%.1f fps)",
                    frame_count, 32e6/(double)dt.asMicroseconds() );
            clock_fps.restart();
        }



        frame_count++;
        // if(frame_count%(int)(200) == 0)
        //     cout << "frame " << frame_count << " " 
        //     << m_tiles.size() << " tiles\n";
        clock_logique.restart();
        clock_boucle.restart();
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
    std::pair<Tile *, sf::RectangleShape *> t;
    for(int i = 0; i < m_tiles.size(); i++) {
        t = m_tiles.at(i);
        // cout << t.first->get_x() << endl;
        if(t.first->get_x() < 0 || t.first->get_x() > m_win_w) {
            printf("AAAAAAAAAAAAAAAH : %i: %i : %p\n",
                   i, t.first->get_x(), t.first);
            exit(1);
        }
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






