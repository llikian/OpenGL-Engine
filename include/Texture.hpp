/***************************************************************************************************
 * @file  Texture.hpp
 * @brief Declaration of the Texture class
 **************************************************************************************************/

#pragma once

#include "Image.hpp"

/**
 * @class Texture
 * @brief Creates a texture and assigns an image's data to it. Can then be bound.
 */
class Texture {
public:
    /**
     * @brief Constructs a texture by loading an image and assigning its data to a new texture.
     * @param path The image's path.
     */
    Texture(const std::string& path);

    /**
     * @brief Constructs a texture by assigning an image's data to a new texture.
     * @param image The image.
     */
    Texture(const Image& image);

    /**
     * @brief Deletes the texture.
     */
    ~Texture();

    /**
     * @brief Binds the texture to a specifc texture unit.
     * @param texUnit The opengl texture unit ID.
     */
    void bind(unsigned int texUnit = 0) const;

private:
    unsigned int id; ///< Texture id.
};