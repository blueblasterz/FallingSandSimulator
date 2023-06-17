#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


template<typename T,typename U>
std::ostream& operator<< ( std::ostream& out, 
                const std::pair< T, U >& p )
{
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

/*
    creates a color with the given r,g,b,a values (0-255)
    if variation_max != 0, then each of the non-zero channels will vary
    between <channel-value>-variation_max and <channel-value> + variation_max
    (staying between 0 and 255)

    returns an sf::Color
*/
sf::Color create_color(int r, int g, int b, int a=255, int variation_max=0 );

// overload to work from an existing sf::Color
sf::Color create_color(sf::Color color, int variation_max=0 );
