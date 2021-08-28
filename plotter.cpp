/*
 * @Author       : Chivier Humber
 * @Date         : 2021-08-19 06:47:20
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-08-21 23:06:27
 * @Description  : file content
 */
#include "plotter.h"
#include "lodepng.h"

Plotter::Plotter(std::string __filename, std::string __texture, int __width, int __height, double __radius) {
    // Update basic parameters
    width = __width;
    height = __height;
    radius = __radius;

    // Initialize the image buffer
    image_buffer.clear();
    image_buffer.resize(width * height, background_color);

    // Read file to build particle list
    particles_list.clear();
    std::string line;
    std::ifstream input_file(__filename);
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            std::vector<std::string> split;
            double x, y;
            int tp;
            boost::split(split, line, [](char c) { return c == ' '; });
            // Empty line
            // If the split result is less than 3, we ignore this line
            if (split.size() < 3)
                continue;
            x = std::stod(split[0]);
            y = std::stod(split[1]);
            tp = std::stod(split[split.size() - 1]);
            // std::cout << x << ", " << y << ", " << tp << std::endl;
            particles_list.push_back(particle_tp(x, y, tp));
            // Add texture
            texture_buffer.insert(tp);
        }
        input_file.close();
    }

    // Build texture information
    if (__texture == "") {
        // Using default texture configure
        // - Use color belt loop method
        // - From `Red` to `Blue`
        // - Red texture : #ff1a1a -> #ff9c9c
        // - also = rgb(255,26,26) -> rgb(255,156,156)
        // - Blue texture : #22b5ff -> #b1e5ff
        // - also = rgb(34,181,255) -> rgb(177,229,255)

        color_tp begin_ci(255, 26, 26);
        color_tp begin_co(255, 156, 156);
        color_tp end_ci(34, 181, 255);
        color_tp end_co(177, 229, 255);

        color_tp delta_ci = end_ci - begin_ci;
        color_tp delta_co = end_co - begin_co;

        int count_texture = texture_buffer.size() - 1;
        int index = 0;
        for (auto item : texture_buffer) {
            // Calculate the inner color and the outer color
            auto ci = begin_ci + delta_ci * index / count_texture;
            auto co = begin_co + delta_co * index / count_texture;
            auto new_texture = new radius_texture_tp(ci, co);
            texture_map.insert(std::pair<int, std::shared_ptr<radius_texture_tp>>(item, new_texture));
            index++;
            // std::cout << ci << std::endl << co << std::endl;
        }
    } else {
        std::ifstream texture_file(__texture);
        // TODO : generate the texture from texture file
        
    }

    // debug texture
    // for (auto item : texture_map) {
    //     std::cout << item.first << " ";
    //     auto texture = item.second;
    //     std::cout << texture->type() << " " << texture->get(0.4) << std::endl;
    //     texture->print();
    // }
}

color_tp Plotter::getPixel(int w, int h) {
    if (w >= 0 && h >= 0 && w < width && h < height) {
        return image_buffer[h * width + w];
    }
    return color_tp(-1, -1, -1);
}

void Plotter::setPixel(int w, int h, color_tp color) {
    if (w >= 0 && h >= 0 && w < width && h < height) {
        image_buffer[h * width + w] = color;
    }
}

void Plotter::CircleSubPlotter(int offsetx, int offsety, int centerx, int centery, color_tp color) {
    setPixel(centerx + offsetx, centery + offsety, color);
    setPixel(centerx - offsetx, centery + offsety, color);
    setPixel(centerx + offsetx, centery - offsety, color);
    setPixel(centerx - offsetx, centery - offsety, color);
    setPixel(centerx + offsety, centery + offsetx, color);
    setPixel(centerx - offsety, centery + offsetx, color);
    setPixel(centerx + offsety, centery - offsetx, color);
    setPixel(centerx - offsety, centery - offsetx, color);
}

void Plotter::Generate() {
    // Fix coordination, from double -> int
    double begin_x_cord, begin_y_cord;
    double end_x_cord, end_y_cord;

    begin_x_cord = std::numeric_limits<double>::max();
    begin_y_cord = std::numeric_limits<double>::max();
    end_x_cord = std::numeric_limits<double>::min();
    end_y_cord = std::numeric_limits<double>::min();

    int int_radius = (int)(radius);

    for (particle_tp particle_item : particles_list) {
        if (particle_item.x <= begin_x_cord) {
            begin_x_cord = particle_item.x;
        }
        if (particle_item.x >= end_x_cord) {
            end_x_cord = particle_item.x;
        }
        if (particle_item.y <= begin_y_cord) {
            begin_y_cord = particle_item.y;
        }
        if (particle_item.y >= end_y_cord) {
            end_y_cord = particle_item.y;
        }
    }
    
    // Generate image buffer
    for (particle_tp particle_item : particles_list) {
        int x = (int)((particle_item.x - begin_x_cord) / (end_x_cord - begin_x_cord) * (height - 2 * radius)) + int_radius;
        int y = (int)((particle_item.y - begin_y_cord) / (end_y_cord - begin_y_cord) * (width - 2 * radius)) + int_radius;

        auto current_texture = texture_map[particle_item.tp];
        
        int sub_radius = int_radius;
        for (sub_radius = int_radius; sub_radius >= 0; --sub_radius) {
            int sub_x = 0;
            int sub_y = sub_radius;
            int delta = 3 - 2 * sub_radius;
            auto current_color = current_texture->get((double) sub_radius / radius);
            CircleSubPlotter(sub_x, sub_y, x, y, current_color);
            while (sub_y >= sub_x) {
                sub_x++;
                if (delta > 0) {
                    sub_y--;
                    delta += 4 * (sub_x - sub_y) + 10;
                } else {
                    delta += 4 * sub_x + 6;
                }
                CircleSubPlotter(sub_x, sub_y, x, y, current_color);
            }
            // std::cout << std::endl;
        }
    }
}

void Plotter::Savepng(const char *filename) {
    std::vector<unsigned char> png;
    lodepng::State state; //optionally customize this one
    std::vector<unsigned char> image;

    for (int y_id = 0; y_id < height; ++y_id) {
        for (int x_id = 0; x_id < width; ++x_id) {
            auto item = image_buffer[y_id * width + x_id];
            image.push_back(item.r);
            image.push_back(item.g);
            image.push_back(item.b);
            image.push_back(255);
        }
    }
    unsigned error = lodepng::encode(png, image, width, height, state);
    if(!error) lodepng::save_file(png, filename);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}