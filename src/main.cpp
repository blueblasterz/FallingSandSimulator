#include <iostream>

#include "Simulator.hpp"

using std::cout, std::endl;

int main() {
    // Simulator s = Simulator(160,90);
    // Simulator s = Simulator(800,600);
    Simulator s = Simulator(400,300);

    
    // printf("from main:\n%p %p\n", s.get_cells(), s.get_cells_future());
    // TileSand t = TileSand(50, 500, 800,600, 
    //              s.get_cells(), s.get_cells_future());
    // TileSand t2 = TileSand(50, 300, 800,600, 
    //              s.get_cells(), s.get_cells_future());

    // std::array<int,2> pos = t.get_pos();
    // cout << "1: " << pos[0] << " " << pos[1] << endl;
    // pos = t2.get_pos();
    // cout << "2: " << pos[0] << " " << pos[1] << endl;

    // s.add_tile(&t);
    // s.add_tile(&t2);

    sf::Clock start = sf::Clock();
    s.mainloop();

    sf::Time dt = start.getElapsedTime();
    printf("took %ims\n", dt.asMilliseconds());

    // pos = t.get_pos();
    // cout << "1: " << pos[0] << " " << pos[1] << endl;
    // pos = t2.get_pos();
    // cout << "2: " << pos[0] << " " << pos[1] << endl;
    return 0;
}