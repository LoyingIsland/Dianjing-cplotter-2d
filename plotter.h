/*
 * @Author       : Chivier Humber
 * @Date         : 2021-08-19 06:38:23
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-08-19 14:25:06
 * @Description  : file content
 */
#include "common.h"

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

    color_tp operator*(double offset) const {
        return color_tp(r * offset, g * offset, b * offset);
    }

    color_tp& operator=(const color_tp& other) {
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }
};

class texture_tp {
};

class pure_texture_tp : public texture_tp {

};

class radius_texture_tp : public texture_tp {

};

class Plotter {
    private:
    std::string filename;
    // TODO: Build texture system
    int width, height;
    std::vector<color_tp> image_buffer;
    std::vector<texture_tp> texture_buffer;
    double radius;
    
    public:
    Plotter(std::string __filename, std::string __texture, int __width, int __height, double __radius);
};
