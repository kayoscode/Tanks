#pragma once

#include "../lib/glew/include/GL/glew.h"
#include "../Serializers/STB_image/ImageLoader.h"

//free textures: https://textures.pixel-furnace.com/

/**
 * Base class for storing texture data
 * @author Bryce Young 5/28/2021
 * */
class Texture {
    public:
        Texture() {

        }

        ~Texture() {

        }

        /**
         * Loads the texture from a file
         * */
        void loadFromFile(const std::string& path) {
            Image img;
            if(!ImageLoader::loadImage(path, img)) {
            }
            else {
                loadFromImg(img);
            }
        }

        /**
         * Loads the texture from an image object
         * */
        void loadFromImg(Image& img) {
            //load texture id
            glCreateTextures(GL_TEXTURE_2D, 1, &diffuseID);

            //bind texture before operating
            glBindTexture(GL_TEXTURE_2D, diffuseID);

            //set default parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            //load texture data
            if(img.numComponents == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data);
            }
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data);
            }
        }

        /**
         * @return the texture's id
         * */
        int getDiffuseID() {
            return (int)diffuseID;
        }

    protected:
        GLuint diffuseID;
};

