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

        ~Texture() 
        {

        }

        /// <summary>
        /// Loads the texture from a file.
        /// </summary>
        /// <param name="path"></param>
        void loadFromFile(const std::string& path) {
            Image img;
            if(!ImageLoader::loadImage(path, img)) {
            }
            else {
                loadFromImg(img);
            }
        }

        /// <summary>
        /// Given raw image data, load the texture.
        /// </summary>
        /// <param name="img"></param>
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
        int getDiffuseID() 
        {
            return (int)diffuseID;
        }

        /// <summary>
        /// Creates the texture from a texture id.
        /// Note that this texture object now owns that texture and should
        /// be the sole object that disposes of the ID.
        /// </summary>
        /// <param name="textureId"></param>
        void loadFromTextureID(unsigned int textureId)
        {
            if (diffuseID != -1)
            {
                // Dispose previous texture.
            }

            diffuseID = textureId;
        }

    protected:

        GLuint diffuseID = -1;
};

