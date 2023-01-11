#include "Simulator.hpp"

using std::cout, std::cin, std::endl;

Simulator::Simulator(int w, int h, int tile_size): 
m_win_w(w), m_win_h(h), m_tile_size(tile_size) {
    m_w = m_win_w / tile_size;
    m_h = m_win_h / tile_size;
}

int Simulator::mainloop() {

    sf::RenderWindow m_window(
        sf::VideoMode(m_win_w, m_win_h),
        "Falling Sand Simulator");
    
    sf::Clock clock = sf::Clock();

    float fps = 120.;

    sf::Time requested_fps = sf::microseconds(1000000./fps);

    // sf::RectangleShape shape(sf::Vector2f(100,100));
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color(255,0,0));


    bool mouse_pressed = false;
    int frame_count=0;
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    // std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    // std::cout << "mouse y: " << m_win_h - event.mouseButton.y << std::endl;
                    if(event.mouseButton.button == sf::Mouse::Left)
                        mouse_pressed = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Left)
                        mouse_pressed = false;
                    break;
            }
        }
        m_window.clear();

        if(mouse_pressed) {
            // int x = event.mouseButton.x;
            // int y = event.mouseButton.y;
            int x = sf::Mouse::getPosition(m_window).x;
            int y = sf::Mouse::getPosition(m_window).y;
            // cout << x << " " << y << endl;
            add_tile(new Tile(x/m_tile_size, 
                              m_h - y/m_tile_size));
        }

        int i=0;
        for(auto t : m_tiles) {
            // std::cout << t->get_y() << std::endl;
            if(t.first->get_y() > 1) {
                t.first->dmove(0,-1);

                t.second.setPosition(t.first->get_x(), m_h-t.first->get_y());
                // cout << t.second.getPosition().x << " " << t.second.getPosition().y << endl;  
                i++;
            }
            m_window.draw(t.second);
        }

        
        m_window.display();
        sf::Time dt = clock.getElapsedTime();
        sf::sleep(requested_fps-dt);
        clock.restart();
        // cout << "endofframe\n";
        frame_count++;
        if(frame_count%(int)(fps/2) == 0)
            cout << "frame " << frame_count << " " 
            << m_tiles.size() << " tiles\n";
    }

    return 0;
}


void Simulator::add_tile(Tile * tile) {
    // sf::RectangleShape newr = new sf::RectangleShape(sf::Vector2f(100,100));
    sf::RectangleShape newr;
    newr.setSize(sf::Vector2f(m_tile_size,m_tile_size));
    newr.setFillColor(sf::Color(255,255,255));
    newr.setPosition(tile->get_x(), m_h-tile->get_y());
    m_tiles.push_back(std::pair(tile,newr));
}
void Simulator::remove_tile(int i) {
    m_tiles.erase(m_tiles.begin()+i);
}

int Simulator::update_display() {
    // m_window.clear();
    // // int t = update_tiles();
    // m_window.display();
    return 0;
}

int Simulator::update_tiles() {
    // m_window.draw(shape);
    return 0;
}







