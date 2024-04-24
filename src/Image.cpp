/***************************************************************************************************
 * @file  Image.cpp
 * @brief Implementation of the Image class
 **************************************************************************************************/

#include "Image.hpp"

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

const unsigned char* Image::getData() {
    return data;
}

unsigned int Image::getWidth() {
    return width;
}

unsigned int Image::getHeight() {
    return height;
}

unsigned int Image::getChannelsNumber() {
    return nbChannels;
}
