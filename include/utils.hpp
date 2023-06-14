#pragma once

#include <iostream>

template<typename T,typename U>
std::ostream& operator<< ( std::ostream& out, 
                const std::pair< T, U >& p )
{
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

