#include <iostream>

#include "Simulator.hpp"

using std::cout, std::endl;

int main() {
    Simulator s = Simulator();

    TileEmpty t = TileEmpty(50, 500, s.get_cells());

    // std::array<int,2> pos = t.get_pos();
    // cout << pos[0] << " " << pos[1] << endl;

    s.add_tile(&t);

    s.mainloop();

    // pos = t.get_pos();
    // cout << pos[0] << " " << pos[1] << endl;
    return 0;
}