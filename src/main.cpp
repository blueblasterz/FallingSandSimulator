#include <iostream>

#include "Simulator.hpp"

using std::cout, std::endl;

int main() {
    Simulator s = Simulator();

    Tile t = Tile(50,500);

    std::array<int,2> pos = t.get_pos();
    // cout << pos[0] << " " << pos[1] << endl;

    s.add_tile(&t);

    s.mainloop();

    // cout << pos[0] << " " << pos[1] << endl;
    // cout << t.get_x() << " " << t.get_y() << endl;
    return 0;
}