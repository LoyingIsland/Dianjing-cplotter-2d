/*
 * @Author       : Chivier Humber
 * @Date         : 2021-08-19 02:33:23
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-08-19 06:37:50
 * @Description  : file content
 */
#include "common.h"

namespace po = boost::program_options;

int main(int argc, char **argv) {
    // Argument parsing
    po::options_description desc{"Options"};
    desc.add_options()                                                                 //
        ("help", "Help screen")                                                        //
        ("file,f", po::value<std::string>()->default_value("input.txt"), "Input file") //
        ("texture,t", po::value<std::string>()->default_value(""), "Texture file")     //
        ("radius,r", po::value<double>()->default_value(10), "Radius Level")           //
        ("width,w", po::value<int>()->default_value(1600), "Picture width")            //
        ("height,h", po::value<int>()->default_value(900), "Picture height");

    po::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    std::string input_filename;
    std::string texture_filename;
    double radius_level = 10;
    int width = 1600;
    int height = 900;

    if (vm.count("help")) {
        std::cout << desc << std::endl;
    } else if (vm.count("file")) {
        input_filename = vm["file"].as<std::string>();
    } else if (vm.count("texture")) {
        texture_filename = vm["texture"].as<std::string>();
    } else if (vm.count("radius")) {
        radius_level = vm["radius"].as<double>();
    } else if (vm.count("width")) {
        width = vm["width"].as<int>();
    } else if (vm.count("height")) {
        height = vm["height"].as<int>();
    }

    
}
