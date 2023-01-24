#include "Simulator.hpp"

using std::cout, std::cin, std::endl;

Simulator::Simulator(int w, int h, int tile_size): 
m_win_w(w), m_win_h(h), m_tile_size(tile_size) {
    m_w = m_win_w / tile_size;
    m_h = m_win_h / tile_size;

    srand(time(NULL));
    // srand(0);

    m_cells = new TYPE_CELLMATRIX();
    m_cells->resize(m_w);
    m_cells_future = new TYPE_CELLMATRIX();
    m_cells_future->resize(m_w);
    for(int i = 0; i < m_w; i++) {
        m_cells->at(i).resize(m_h);
        m_cells_future->at(i).resize(m_h);
        for(int j = 0; j < m_h; j++) {
            m_cells->at(i).at(j) = nullptr;
            m_cells_future->at(i).at(j) = nullptr;
        }
    }

    m_nb_tiles = 0;


}

int Simulator::mainloop() {

    m_window = new sf::RenderWindow(
        sf::VideoMode(m_win_w, m_win_h),
        "Falling Sand Sim");

    sf::Clock clock_logique = sf::Clock();
    sf::Clock clock_boucle = sf::Clock();
    sf::Clock clock_fps = sf::Clock();

    const float fps = 1000.;

    sf::Time requested_fps = sf::microseconds(1000000./fps);

    bool mouse_pressed = false;
    int frame_count=0;

    const int count_update = 1;

    bool paused = !true;
    int step = 0;

    char title[128] = {0};

    bool last_frame_added = false;

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
                        
                        // mouse_pressed = true;

                        int x = sf::Mouse::getPosition(*m_window).x;
                        int y = sf::Mouse::getPosition(*m_window).y;
                        int c = 0;
                        for(int dx=0;dx < 40 && x+dx < m_w; dx++) {
                            for(int dy=0; dy<20 && y+2*dy < m_h; dy++) {
                                c++;
                                add_tile<TileSand>(x+dx,m_h-(y+2*dy));
                                // add_tile<TileSand>(x+dx,m_h-(y+dy));
                            }
                        }
                    }

                    break;
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        // mouse_pressed = false;
                    }
                    break;
                default:
                    break;
            }
        }
        if(!paused || step > 0) {
            if(step > 0) step--;
            m_window->clear();

            // if(frame_count%(2*m_w) > m_w ) {
            //     add_tile<TileSand>( (m_w-frame_count%m_w -1 +20)%m_w, m_h-20);
            //     add_tile<TileSand>( (m_w-frame_count%m_w -1 +20)%m_w, m_h-18);
            //     add_tile<TileSand>( (m_w-frame_count%m_w -1 +20)%m_w, m_h-16);
            //     add_tile<TileSand>( (m_w-frame_count%m_w -1 +20)%m_w, m_h-14);
            //     add_tile<TileSand>( (m_w-frame_count%m_w -1 +20)%m_w, m_h-12);
            //     add_tile<TileSand>( (m_w-frame_count%m_w -1 +20)%m_w, m_h-10);
            // }
            // else {
            //     add_tile<TileSand>(frame_count%m_w, m_h-20);
            //     add_tile<TileSand>(frame_count%m_w, m_h-18);
            //     add_tile<TileSand>(frame_count%m_w, m_h-16);
            //     add_tile<TileSand>(frame_count%m_w, m_h-14);
            //     add_tile<TileSand>(frame_count%m_w, m_h-12);
            //     add_tile<TileSand>(frame_count%m_w, m_h-10);
            // }
            // if(true || frame_count%2 == 0) {
            //     add_tile<TileSand>(m_w/2, m_h-1);
            // }
            if(frame_count%70 == 0 ) {
                for(int i=0;i<20; i++)
                    for(int j=0; j<10;j++)
                        add_tile<TileSand>( m_w/2+i-10, m_h-1-2*j);
                        // add_tile<TileSand>( m_w/2+i-10, m_h-1-j);
            }

            if(mouse_pressed) {
                if( (last_frame_added = !last_frame_added) ) {

                    int x = sf::Mouse::getPosition(*m_window).x;
                    int y = sf::Mouse::getPosition(*m_window).y;
                    if(0 < x && x < m_win_w && 0 < y && y < m_win_h) {
                        // cout << m_nb_tiles << " : " << x << " " << y << endl;
                        m_nb_tiles++;
                        // if ( m_cells->at(x/m_tile_size).at(m_h - y/m_tile_size)
                        //     == nullptr ) {
                            // Tile * t = new TileSand(x/m_tile_size, 
                            //                 m_h - y/m_tile_size,
                            //                 m_w, m_h,
                            //                 m_cells, m_cells_future);
                            add_tile<TileSand>(x/m_tile_size, m_h - y/m_tile_size);
                        // }
                    }
                }
            }

            update_tiles();

            m_window->display();
            m_window->setTitle( title );

            sf::Time dt = clock_logique.getElapsedTime();
            sf::sleep(requested_fps-dt);

            if(frame_count%count_update == 0) {

                dt = clock_fps.getElapsedTime();
                snprintf(title, 128, "Falling Sand Sim : frame %i (%.1f fps)",
                        frame_count,
                        count_update*1e6/(double)dt.asMicroseconds() );
                clock_fps.restart();
            }

        // cout << "all tiles :" << endl;
        // Tile * t;
        // for(int x = 0; x < m_w; x++) {
        //     for(int y = 0; y < m_h; y++) {
        //         t = m_cells->at(x).at(y);
        //         if(t != nullptr) {
        //             cout << " at " << x << " " << y << endl;
        //         }
        //     }
        // }
        // cout << "----" << endl;
        // for(auto t : m_tiles) {
        //     cout << " at " << t->get_x() << " " << t->get_y() << endl;
        // }
        // cout << "----" << endl;

        frame_count++;
        if(frame_count == 275) {
            paused = true;
        }
        // if(frame_count == 2500) break;
        // if(frame_count%(int)(200) == 0)
        //     cout << "frame " << frame_count << " " 
        //     << m_nb_tiles << " tiles\n";
        clock_logique.restart();
        clock_boucle.restart();

        }
    }

    delete m_window;
    return 0;
}

template<class TileType>
void Simulator::add_tile(int x, int y) {
    if ( m_cells->at(x).at(y) != nullptr )
        return;
    Tile * t = new TileType(x,y,m_w,m_h, m_cells, m_cells_future);
    m_tiles.push_back(t);
    t->get_rectangle()->setSize(sf::Vector2f(m_tile_size, m_tile_size));
}


void Simulator::add_tile(Tile * tile) {
    m_tiles.push_back(tile);
    tile->get_rectangle()->setSize(sf::Vector2f(m_tile_size, m_tile_size));
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
    Tile * t;
    // printf("%p %p\n", m_cells, m_cells_future);
    // cout << "all tiles :" << endl;
    // for(int x = 0; x < m_w; x++) {
    //     for(int y = 0; y < m_h; y++) {
    //         t = m_cells->at(x).at(y);
    //         if(t != nullptr) {
    //             cout << " at " << x << " " << y << endl;
    //         }
    //     }
    // }
    // cout << "----" << endl;

    for(unsigned int i = 0; i < m_tiles.size(); i++) {
        t = m_tiles.at(i);
        // cout << t->get_y() << endl;
        // if(t.first->get_y() > 1) {
        //     t.first->dmove(0,-1);

        //     t.second->setPosition(t.first->get_x(), m_h-t.first->get_y());
        // }    
        t->update();

        // sf::RectangleShape r = *t->get_rectangle();
        // cout << r.getPosition().x << " " << r.getPosition().y << endl;
        // cout << r.getFillColor().r << " " << r.getFillColor().g << " "
        //      << r.getFillColor().b << endl;
    }
    // for(int x = 0; x < m_w; x++) {
    //     for(int y = 0; y < m_h; y++) {
    //         t = m_cells_future->at(x).at(y);
    //         m_cells->at(x).at(y) = t;
    //         if(t != nullptr)
    //             m_window->draw( *t->get_rectangle() );
    //     }
    // }


    int x=0; int y=0;
    for(auto& col : *m_cells_future) {
        for( auto& t : col) {
            m_cells->at(x).at(y) = t;
            if(t != nullptr)
                m_window->draw( *t->get_rectangle() );
            // m_cells_future->at(x).at(y) = nullptr;
            // t = nullptr;
            y++;
        }
        x++;
        y=0;
    }
    

    // std::pair<Tile *, sf::RectangleShape *> t;
    // for(int x = 0; x < m_w; x++) {
    //     for(int y = 0; y < m_h; y++) {
    //         t = m_cells->at(x).at(y);
    //         if(t.first != nullptr)
    //             t.first->update(); // modifies cell_future
    //     }
    // }

    // for(int x = 0; x < m_w; x++) {
    //     for(int y = 0; y < m_h; y++) {
    //         t = m_cells_future->at(x).at(y);
    //         m_cells->at(x).at(y) = t;
    //         if(t.first != nullptr) {
    //             m_window->draw(*t.second);
    //         }
            
    //     }
    // }

    return 0;
}



TYPE_CELLMATRIX * Simulator::get_cells() {
    return m_cells;
}

TYPE_CELLMATRIX * Simulator::get_cells_future() {
    return m_cells_future;
}






