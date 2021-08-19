/*
 * @Author       : Chivier Humber
 * @Date         : 2021-08-19 06:47:20
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-08-19 14:30:31
 * @Description  : file content
 */
 #include "plotter.h"

Plotter::Plotter(std::string __filename, std::string __texture, int __width, int __height, double __radius) {
    std::string line;
    std::ifstream myfile (__filename);
    if (myfile.is_open()) {
        while (getline (myfile,line)) {
            std::cout << line << std::endl;
        }
        myfile.close();
    }
}