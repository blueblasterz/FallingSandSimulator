#include <iostream>

// #include "Simulator.hpp"

#include "Simulator.hpp"

using std::cout, std::endl;

int main() {
    // Simulator sim(100,50,16);

    // double ratio = 4./3.;
    double ratio = 16./9.;

    double real_height = 720;

    double scale = 10;

    Simulator sim((int)(real_height*ratio/scale), (int)(real_height/scale) , scale);

    sim.start();

}