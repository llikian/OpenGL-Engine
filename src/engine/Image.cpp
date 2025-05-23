/***************************************************************************************************
 * @file  Image.cpp
 * @brief Implementation of the Image class
 **************************************************************************************************/

#include "engine/Image.hpp"

Image::Image(const std::string& path) {
    int W, H, nbC;
    data = stbi_load(path.c_str(), &W, &H, &nbC, 3); // TODO : Maybe change 3 to 4 for transparency

    width = W;
    height = H;
    nbChannels = nbC;
}

Image::~Image() {
    stbi_image_free(data);
}

const unsigned char* Image::getData() const {
    return data;
}

unsigned int Image::getWidth() const {
    return width;
}

unsigned int Image::getHeight() const {
    return height;
}

unsigned int Image::getChannelsNumber() const {
    return nbChannels;
}
