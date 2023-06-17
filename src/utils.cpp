#include "utils.hpp"

#define make_INBOUNDS(val,mini,maxi) \
    if((val) < (mini)) (val) = (mini); \
    if((val) >= (maxi)) (val) = (maxi)-1;

sf::Color create_color(int r, int g, int b, int a, int variation_max ) {
    if (variation_max == 0) {
        return sf::Color(r,g,b,a);
    }
    // int r_ = r != 0 ? r + rand()%(2*variation_max)-variation_max : 0;
    // int g_ = g != 0 ? g + rand()%(2*variation_max)-variation_max : 0;
    // int b_ = b != 0 ? b + rand()%(2*variation_max)-variation_max : 0;   

    int vari = rand()%(2*variation_max)-variation_max;
    int r_ = r != 0 ? r + vari : 0;
    int g_ = g != 0 ? g + vari : 0;
    int b_ = b != 0 ? b + vari : 0; 

    make_INBOUNDS(r_,0,256);
    make_INBOUNDS(g_,0,256);
    make_INBOUNDS(b_,0,256);

    return sf::Color(r_,g_,b_,a);
}


sf::Color create_color(sf::Color color, int variation_max ) {
    return create_color( color.r, color.g, color.b, color.a, variation_max );
}