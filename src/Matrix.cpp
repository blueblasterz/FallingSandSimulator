#include "Matrix.hpp"

#include "utils.hpp"
#include "Tile.hpp"

#include <cmath>
#define BOOST_STACKTRACE_LINK
#include <boost/stacktrace.hpp>

#define min(a,b) ( (a)<(b) ? (a) : (b) )
#define max(a,b) ( (a)>(b) ? (a) : (a) )

// changes the value in val to be between min (included) and max(excluded)
#define make_INBOUNDS(val,mini,maxi) \
    if((val) < (mini)) (val) = (mini); \
    if((val) >= (maxi)) (val) = (maxi)-1;

// true if val is INBOUNDS (mini included, maxi excluded)
#define INBOUNDS(val,mini,maxi) ((val) >= (mini) && (val) < (maxi))

using std::vector, std::pair, std::round, std::cout, std::endl;


std::ostream& operator<<(std::ostream& os, const Matrix& obj) {
    for (const auto& inner : obj.m_matrix) {
        for (const auto& value : inner) {
            os << value << ' ';
        }
        os << '\n';
    }
    return os;
}


Matrix::Matrix(int w, int h) :
    m_w(w),
    m_h(h)
{
    m_matrix.resize(m_h);
    for(int i = 0; i < m_h; i++) {
        m_matrix.at(i).resize(m_w);
        for(int j = 0; j < m_w; j++) {
            m_matrix.at(i).at(j) = 0;
        }
    }
    printf("created matrix of size (%i,%i)\n", m_w, m_h);
}

Matrix::~Matrix() {}


void Matrix::set_tile(int x, int y, Tile * tile) {
    if( x < 0 || x >= m_w || y < 0 || y >= m_h ) {
        std::cerr << "invalid set_tile : at " << x << "," << y << std::endl;
        std::cerr << boost::stacktrace::stacktrace();
        return;
    }
    m_matrix.at(y).at(x) = tile;
}

Tile * Matrix::get_tile(int x, int y) {
    if( x < 0 || x >= m_w || y < 0 || y >= m_h ) {
        std::cerr << "invalid get_tile : at " << x << "," << y << std::endl;
        std::cerr << boost::stacktrace::stacktrace();
        return nullptr;
    }
    return m_matrix.at(y).at(x);
}

void Matrix::delete_tile(int x, int y) {
    if(INBOUNDS(x,0,m_w) && INBOUNDS(y,0,m_h)) {
        delete this->get_tile(x,y);
        this->set_tile(x,y,nullptr);
    }
}

void Matrix::move_tile(int x, int y, int x_dest,int y_dest) {
    if ( INBOUNDS(x_dest,0,m_w) && INBOUNDS(y_dest,0,m_h) ) {
        if (this->get_tile(x_dest,y_dest) != nullptr ) {
            this->delete_tile(x_dest,y_dest);
        }
    }
    else {
        this->delete_tile(x,y);
        return;
    }
    // cout << x_dest << "," << y_dest << endl;
    Tile * t = this->get_tile(x,y);
    t->move(x_dest,y_dest);
    this->set_tile(x_dest,y_dest, t);
    this->set_tile(x,y,nullptr);
}

bool Matrix::inbounds(int x, int y) {
    return 0 <= x && x < m_w && 0 <= y && y < m_h;
}

vector<vector<Tile *>> & Matrix::get_matrix() {
    return m_matrix;
}


vector<pair<int,int>> Matrix::get_points_between(
    int x1, int y1, int x2, int y2,
    bool debug
) {
    if(debug) {
        cout << "from : " << x1 << "," << y1 
        << " to " << x2 << "," << y2 << endl;
    }
    make_INBOUNDS(x1,0,m_w);
    make_INBOUNDS(x2,0,m_w);
    make_INBOUNDS(y1,0,m_h);
    make_INBOUNDS(y2,0,m_h);

    vector<pair<int,int>> values;
    if(x1 == x2 && y1 == y2) {
        values.push_back(pair<int,int>(x1,y1));
        return values;
    }

    int delta_x = x2-x1;
    if(debug) cout << "delta_x = " << delta_x << endl; 
    // line is vertical
    if (delta_x == 0) {
        int dy = y1 < y2 ? 1 : -1;
        for(int y = y1; y != y2 ; y += dy) {
            values.push_back(pair<int,int>(x1,y));
        }
        return values;
    }

    int delta_y = y2-y1;
    if(debug) cout << "delta_y = " << delta_y << endl; 
    // line is horizontal
    if (delta_y == 0) {
        int dx = x1 < x2 ? 1 : -1;
        for(int x = x1; x != x2 ; x += dx) {
            values.push_back(pair<int,int>(x,y1));
        }
        return values;
    }

    double slope = (double)delta_y / (double)delta_x;
    // double slope = (double)std::abs(delta_y) / (double)std::abs(delta_x);
    if(debug) cout << "slope = " << slope << endl; 
    double slope_inv = 1/slope;
    // std::cout << delta_x << "," << delta_y << "," << slope << std::endl;

    // use the y as a "guide"
    if( std::abs(slope) > 1 ) {
        if(debug) cout << "using y" << endl;
        int dir_y = y1 < y2 ? 1 : -1;
        int dir_x = x1*slope < x2*slope ? 1 : -1;

        // for(int y = y1; y != y2 ; y += dy) {
        for(int i = 0; i <= std::abs(delta_y) ; i++) {
            values.push_back( pair<int,int>( round(x1 + i*slope_inv*dir_x), y1+i*dir_y ) );
        }
    }
    else { // use the x as a "guide"
        if(debug) cout << "using x" << endl;
        int dir_y = y1*slope < y2*slope ? 1 : -1;
        int dir_x = x1 < x2 ? 1 : -1;

        // for(int y = y1; y != y2 ; y += dy) {
        for(int i = 0; i <= std::abs(delta_x) ; i++) {
            values.push_back( pair<int,int>( x1+i*dir_x, round(y1 + i*slope*dir_y) ) );
        }
    }
    if(debug) {
        cout << "values : --" << endl;
        for(auto pos : values) {
            cout << " " << pos << endl;
        }
        cout << " --" << endl;
    }
    return values;
}
