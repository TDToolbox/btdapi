#include "strutil.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

std::vector<u8> loadFile(std::string path) {


    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.good()) {
        std::string msg = "File " + path + " Does not exist!";
        throw std::exception(msg.c_str());
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (file.read(buffer.data(), size)) {
        /* worked! */
    }
    else {
        throw std::exception("Could not open file, unknown error!");
    }
}
