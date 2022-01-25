#ifndef INCLUDE_GUI_SHADER_H
#define INCLUDE_GUI_SHADER_H

//Graphics/Shader.h
#include "Math/Math.h"
#include "Render Engine/Shader.h"

/**
 * Class that handles a GUI shader
 * Includes attribute for vertex positions
 * 
 * Uniform location for position, scale, and texture
 * @author Bryce Young 5/28/2021
 * */
class GUIShader : public ShaderProgram {
    public:
        GUIShader();
        ~GUIShader();

        /**
         * @override setting uniform locations for this specific shader
         * */
        void setUniformLocations();

        /**
         * Loads the position and scale into graphics memory
         * @param pos the position from -1 to 1
         * @param scale the x and y scale from 0 to 1
         * */
        void loadTransformVars(const Vector2f& pos, const Vector2f& scale);

        /**
         * Sets the texture
         * */
        void loadTexture(const int textureIndex);

    protected:
        int locationPosition;
        int locationScale;
        int locationTexture;
};

#endif