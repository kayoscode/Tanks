#ifndef INCLUDE_IMAGE_LOADER_H
#define INCLUDE_IMAGE_LOADER_H

#include <string>

struct Image;

/**
 * Class using stb_image to load image data into a texture
 * @author Bryce Young 5/28/2021
 * */
class ImageLoader {
    public:
        ImageLoader() {
        }

        ~ImageLoader() {
        }

        static bool loadImage(const std::string& path, Image& img);

    private:

};

/**
 * Stores data about an image
 * */
struct Image {
    int width, height, numComponents;
    unsigned char* data;

    Image() :width(0), height(0), numComponents(0) {
        this->data = nullptr;
    }

    ~Image() {
        if(data != nullptr) {
            delete[] data;
        }
    }

    friend bool ImageLoader::loadImage(const std::string&, Image&);
};

#endif