#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool ImageLoader::loadImage(const std::string& fileName, Image& img) {
    stbi_set_flip_vertically_on_load(true);  

    int width, height, numComponents;
	unsigned char *data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

    if(data) {
        img.data = data;
        img.width = width;
        img.height = height;
        img.numComponents = numComponents;

        return true;
    } 

    return false;
}