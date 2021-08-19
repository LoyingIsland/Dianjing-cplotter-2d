/*
 * @Author       : Chivier Humber
 * @Date         : 2021-08-19 06:47:20
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-08-19 17:43:34
 * @Description  : file content
 */
 #include "plotter.h"

Plotter::Plotter(std::string __filename, std::string __texture, int __width, int __height, double __radius) {
    // Update basic parameters
    width = __width;
    height = __height;
    radius = __radius;
    
    // TODO: add options for the program
    const double opacity = 0.75;
    const color_tp background_color(255,255,255);

    // Initialize the image buffer
    image_buffer.clear();
    image_buffer.resize(width * height, color_tp(255, 255, 255));

    // Read file to build particle list
    particles_list.clear();
    std::string line;
    std::ifstream input_file (__filename);
    if (input_file.is_open()) {
        while (getline (input_file,line)) {
            std::vector<std::string> split;
            double x, y;
            int tp;
            boost::split(split, line, [](char c){return c == ' ';});
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
        color_tp end_ci(34,181,255);
        color_tp end_co(177,229,255);

        color_tp delta_ci = end_ci - begin_ci;
        color_tp delta_co = end_co - begin_co;
        
        int count_texture = texture_buffer.size() - 1;
        int index = 0;
        std::cout << count_texture;
        for (auto item : texture_buffer) {
            // Calculate the inner color and the outer color
            auto ci = begin_ci + delta_ci * index / count_texture;
            auto co = begin_co + delta_co * index / count_texture;
            texture_map[item] = radius_texture_tp(ci, co);
            index++;
            // std::cout << ci.r << ", " << ci.g << ", " << ci.b << std::endl;
            // std::cout << co.r << ", " << co.g << ", " << co.b << std::endl;
        }
    } else {
        std::ifstream texture_file(__texture);
        // TODO : to be done
        // TODO : generate the texture from texture file
    }
}