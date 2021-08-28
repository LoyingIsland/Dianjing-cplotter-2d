/*
 * @Author       : Chivier Humber
 * @Date         : 2021-08-19 06:38:23
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-08-21 22:59:28
 * @Description  : file content
 */
#include "common.h"

const int kDirectionX[] = {-1, -1, 1, 1};
const int kDirectionY[] = {1, -1, 1, -1};

// Color type
class color_tp {
    public:
    short r;
    short g;
    short b;

    color_tp() : r(0), g(0), b(0) {}
    color_tp(short __r, short __g, short __b) : r(__r), g(__g), b(__b) {}
    ~color_tp() {}

    bool operator==(color_tp const &other) const { return (r == other.r && g == other.g && b == other.b); }

    bool operator!=(color_tp const &other) const { return (r != other.r || g != other.g || b != other.b); }

    color_tp operator+(color_tp const &other) const { return color_tp(r + other.r, g + other.g, b + other.b); }

    color_tp operator-(color_tp const &other) const { return color_tp(r - other.r, g - other.g, b - other.b); }

    color_tp operator*(const double offset) const { return color_tp(r * offset, g * offset, b * offset); }

    color_tp operator/(const double offset) const { return color_tp(r / offset, g / offset, b / offset); }

    color_tp &operator=(const color_tp &other) {
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const color_tp &color) {
        os << "( " << color.r << ", " << color.g << ", " << color.b << " )";
        return os;
    }
};

const color_tp kPureRed(255, 0, 0);
const color_tp kPureGreen(0, 255, 0);
const color_tp kPureBlue(0, 0, 255);

const color_tp background_color(255, 255, 255);

// Particle type
class particle_tp {
    public:
    double x, y;
    int tp;

    particle_tp(double __x, double __y, int __tp) : x(__x), y(__y), tp(__tp) {}
    ~particle_tp() {}
};

// Texture type
class texture_tp {
    public:
    texture_tp() {}
    ~texture_tp() = default;

    virtual int type() const { return 0; }

    virtual color_tp get() const = 0;
    virtual color_tp get(double ratio) const = 0;

    virtual void print() = 0;
};

class pure_texture_tp : public texture_tp {
    public:
    color_tp c;

    pure_texture_tp(color_tp const &__c) : texture_tp(), c(__c) {}

    int type() const { return 1; }

    virtual color_tp get() const { return c; }

    virtual color_tp get(double ratio) const { return c; }

    void print() { std::cout << c.r << ", " << c.g << ", " << c.b << "\n"; }
};

class radius_texture_tp : public texture_tp {
    public:
    color_tp c_inner;
    color_tp c_outer;

    radius_texture_tp(color_tp const &__c1, color_tp const &__c2) : texture_tp(), c_inner(__c1), c_outer(__c2) {}

    int type() const { return 2; }

    virtual color_tp get() const { return c_inner; }

    virtual color_tp get(double ratio) const {
        auto ct = color_tp(c_inner.r + (c_outer.r - c_inner.r) * ratio, //
                           c_inner.g + (c_outer.g - c_inner.g) * ratio, //
                           c_inner.b + (c_outer.b - c_inner.b) * ratio);
        if (ct.r > 255 || ct.g > 255 || ct.b > 255) {
            std::cout << "error" << std::endl;
            std::cout << c_inner << " " << c_outer << std::endl;
            std::cout << ratio << std::endl;
            std::cout << c_inner.r + (c_outer.r - c_inner.r) * ratio << std::endl;
            std::cout << c_inner.g + (c_outer.g - c_inner.g) * ratio << std::endl;
            std::cout << c_inner.b + (c_outer.b - c_inner.b) * ratio << std::endl;
            exit(0);
        }
        return ct;
    }

    void print() {
        std::cout << "( " << c_inner.r << ", " << c_inner.g << ", " << c_inner.b << " ) -> "
                  << "( " << c_outer.r << ", " << c_outer.g << ", " << c_outer.b << " )\n";
    }
};


class Plotter {
    private:
    // TODO: add options for the program
    const double opacity = 0.75;
    // TODO: Build texture system
    int width, height;
    std::vector<color_tp> image_buffer;
    std::set<int> texture_buffer;
    std::vector<particle_tp> particles_list;
    std::map<int, std::shared_ptr<texture_tp>> texture_map;
    double radius;

    public:
    Plotter(std::string __filename, std::string __texture, int __width, int __height, double __radius);
    color_tp getPixel(int w, int h);
    void setPixel(int w, int h, color_tp color);
    void Generate();
    void CircleSubPlotter(int offsetx, int offsety, int centerx, int centery, color_tp color);
    void Savepng(const char *filename);
};
