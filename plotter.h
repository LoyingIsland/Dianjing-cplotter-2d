/*
 * @Author       : Chivier Humber
 * @Date         : 2021-08-19 06:38:23
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-08-19 17:01:25
 * @Description  : file content
 */
#include "common.h"

// Color type
class color_tp {
    public:
    short r;
    short g;
    short b;

    color_tp(short __r, short __g, short __b) : r(__r), g(__g), b(__b) {}
    ~color_tp(){}

    bool operator==(color_tp const& other) const {
        return (r == other.r && g == other.g && b == other.b);
    }

    bool operator!=(color_tp const& other) const {
        return (r != other.r || g != other.g || b != other.b);
    }

    color_tp operator+(color_tp const& other) const {
        return color_tp(r + other.r, g + other.g, b + other.b);
    }

    color_tp operator-(color_tp const& other) const {
        return color_tp(r - other.r, g - other.g, b - other.b);
    }

    color_tp operator*(const double offset) const {
        return color_tp(r * offset, g * offset, b * offset);
    }

    color_tp operator/(const double offset) const {
        return color_tp(r / offset, g / offset, b / offset);
    }
    
    color_tp& operator=(const color_tp& other) {
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }
};

const color_tp kPureRed(255, 0, 0);
const color_tp kPureGreen(0, 255, 0);
const color_tp kPureBlue(0, 0, 255);

// Particle type
class particle_tp {
    public:
    double x, y;
    int tp;

    particle_tp(double __x, double __y, int __tp) : x(__x), y(__y), tp(__tp) { }
    ~particle_tp(){}
};

// Texture type
class texture_tp {
    public:
    int type;
    
    texture_tp() {type = 0;}
    texture_tp(int __type) : type(__type) {}
};

class pure_texture_tp : public texture_tp {
    public:
    color_tp c;

    pure_texture_tp(color_tp const& __c) : texture_tp(1), c(__c) {}
};

class radius_texture_tp : public texture_tp {
    public:
    color_tp c_inner;
    color_tp c_outer;

    radius_texture_tp(color_tp const& __c1, color_tp const& __c2) : texture_tp(2), c_inner(__c1), c_outer(__c2) {}
};

class Plotter {
    private:
    // TODO: Build texture system
    int width, height;
    std::vector<color_tp> image_buffer;
    std::set<int> texture_buffer;
    std::vector<particle_tp> particles_list;
    std::map<int, texture_tp> texture_map;
    double radius;
    
    public:
    Plotter(std::string __filename, std::string __texture, int __width, int __height, double __radius);
};
