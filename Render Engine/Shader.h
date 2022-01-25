#pragma once

#include "../lib/glew/include/GL/glew.h"
#include "../Math/Math.h"

#include <string>
#include <map>
#include <vector>

/// <summary>
/// The valid types of shaders.
/// </summary>
enum class ShaderType
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

/// <summary>
/// Class for dealing with shaders
/// This shader baseclass is responsible for loading shader data,
/// linking vertex and fragment shaders, and getting/setting uniform/attribute data
/// <author>Bryce Young</author>
/// </summary>
class Shader {
public:
	Shader();
	~Shader();

	/// <summary>
	/// Loads a shader from the file system.
	/// </summary>
	/// <param name="shaderPath"></param>
	/// <param name="type"></param>
	/// <param name="errorMessage"></param>
	/// <returns></returns>
	bool loadShader(const std::string& shaderPath, ShaderType type, std::string& errorMessage);

	/// <summary>
	/// Returns the shader program by index.
	/// </summary>
	/// <returns></returns>
	GLuint getShader() {
		return shader;
	}

protected:
	GLuint shader;

private:
};

/**
 * A class that holds a linked vertex and fragment shader
 * @author Bryce Young 5/27/2021
 * */
class ShaderProgram {
public:
	/// <summary>
	/// Empty constructor, initializes members to 0.
	/// </summary>
	ShaderProgram(const std::vector<std::string>& attributes);
	virtual ~ShaderProgram() {}

	/// <summary>
	/// Prepares the shader for use.
	/// </summary>
	void bind();
	void unbind();

	virtual void setUniformLocations() = 0;

	/// <summary>
	/// Loads a vertex shader and a fragment shader from a file.
	/// </summary>
	/// <param name="vertexShaderPath"></param>
	/// <param name="fragmentShaderPath"></param>
	void loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

protected:
	/// <summary>
	/// Uniform loading functions.
	/// </summary>
	/// <param name="location"></param>
	/// <param name="value"></param>
	void loadUniformf(unsigned int location, float value);
	void loadUniformVec2f(unsigned int location, const Vector2f& value);
	void loadUniformVec3f(unsigned int location, const Vector3f& value);
	void loadUniformVec4f(unsigned int location, const Vector4f& value);

	// Doubles.
	void loadUniformd(unsigned int location, double value);
	void loadUniformVec2d(unsigned int location, const Vector2d& value);
	void loadUniformVec3d(unsigned int location, const Vector3d& value);
	void loadUniformVec4d(unsigned int location, const Vector4d& value);

	// Integers.
	void loadUniformi(unsigned int location, int value);
	void loadUniformVec2i(unsigned int location, const Vector2i& value);
	void loadUniformVec3i(unsigned int location, const Vector3i& value);
	void loadUniformVec4i(unsigned int location, const Vector4i& value);

	// Array.
	void loadUniformArrayf(unsigned int location, float* values, int count);
	void loadUniformArrayd(unsigned int location, double* values, int count);
	void loadUniformArrayi(unsigned int loc0ation, int* values, int count);

	// Matrix22.
	void loadMatrix22f(unsigned int location, const Matrix22f& value);
	void loadMatrix22d(unsigned int location, const Matrix22d& value);

	// Matrix33.
	void loadMatrix33f(unsigned int location, const Matrix33f& value);
	void loadMatrix33d(unsigned int location, const Matrix33d& value);

	// Matrix44.
	void loadMatrix44f(unsigned int location, const Matrix44f& value);
	void loadMatrix44d(unsigned int location, const Matrix44d& value);

	/// <summary>
	/// Returns the location of the attribute.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	int getAttributeLocation(const std::string& name);

	/// <summary>
	/// Returns the location of a uniform by name.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	int getUniformLocation(const std::string& name);

	Shader vertexShader;
	Shader fragmentShader;
	GLuint shaderProgram;
	std::map<std::string, int> attributes;
};

