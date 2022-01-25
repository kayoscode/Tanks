#include "Shader.h"
#include "../Logger/StaticLogger.h"

#include <fstream>

Shader::Shader() {

}

Shader::~Shader() { 

}

static bool loadShaderi(const std::string& fileName, std::string& shaderString) {
	std::ifstream file;
	file.open(fileName);

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			shaderString.append(line + "\n");
		}
	}
	else {
		return false;
	}

	return true;
}

/**
 * Attach shaders, but in this case, add future compatibility for geometry shader if needed
 * */
static bool attachShaders(GLuint shaderProgram, GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = 0) {
	if (shaderProgram > 0)
	{
		if (vertexShader > 0) {
            glAttachShader(shaderProgram, vertexShader);
        }

		if (fragmentShader > 0) {
            glAttachShader(shaderProgram, fragmentShader);
        }

		if (geometryShader > 0) {
            glAttachShader(shaderProgram, geometryShader);
        }
	}
	else
	{
        return false;
	}

    return true;
}

static bool checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string& errorMessage) {
    GLint success = 0;
    GLchar error[1024];

    if (isProgram) {
        glGetProgramiv(shader, flag, &success);
    }
    else {
        glGetShaderiv(shader, flag, &success);
    }

    if (success == GL_FALSE) {
        if (isProgram) {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        }
        else {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }

        errorMessage = error;
        return false;
    }

    return true;
}

int ShaderProgram::getUniformLocation(const std::string& uniformName) {
    GLuint ret;
    ret = glGetUniformLocation(this->shaderProgram, uniformName.c_str());
    return (int)ret;
}

bool Shader::loadShader(const std::string& shaderPath, ShaderType type, std::string& errorMessage)
{
    std::string text;

    if (loadShaderi(shaderPath, text)) {
        shader = glCreateShader((GLuint)type);

        if (shader == 0) {
            errorMessage = "Failed to create shader with type: " + std::to_string((int)type);
            return false;
        }

        const GLchar* p[1];
        p[0] = text.c_str();
        GLint lengths[1];
        lengths[0] = (GLint)text.length();

        glShaderSource(shader, 1, p, lengths);
        glCompileShader(shader);

        std::string error;
        if (!checkShaderError(shader, GL_COMPILE_STATUS, false, error)) {
            errorMessage = "Error compiling shader: " + shaderPath + error;
            return false;
        }
    }
    else {
        errorMessage = "Could not open file: " + shaderPath;
        return false;
    }

    return true;
}

static bool linkShaderProgram(GLuint shaderProgram, std::string& error) {
    glLinkProgram(shaderProgram);

	if (!checkShaderError(shaderProgram, GL_LINK_STATUS, true, error)) {
		return false;
	}

    glValidateProgram(shaderProgram);

	if (!checkShaderError(shaderProgram, GL_LINK_STATUS, true, error)) {
		return false;
	}

	return true;
}

ShaderProgram::ShaderProgram(const std::vector<std::string>& attributes) 
    :vertexShader(), fragmentShader(), shaderProgram((GLuint)0),
    attributes()
{
    //copy to the hashmap
    for(int i = 0; i < attributes.size(); ++i) {
        this->attributes[attributes[i]] = i;
    }
}

void ShaderProgram::loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    bool loadError = false;
    std::string currentError;

    //create the shader program
    this->shaderProgram = glCreateProgram();

    //load each shader from a file
    if(!vertexShader.loadShader(vertexShaderPath, ShaderType::VERTEX_SHADER, currentError)) {
        StaticLogger::instance.error("{string}", currentError.c_str());
        loadError = true;
    }

    //load fragment shader from file
    currentError = "";
    if(!fragmentShader.loadShader(fragmentShaderPath, ShaderType::FRAGMENT_SHADER, currentError)) {
        StaticLogger::instance.error("{string}", currentError.c_str());
        loadError = true;
    }

    //link the shaders in a shader program
    if(!loadError) {
        if(!attachShaders(shaderProgram, vertexShader.getShader(), fragmentShader.getShader())) {
            StaticLogger::instance.error("Invalid shader program {int}", shaderProgram);
        }

        //bind each attribute location to the correct name
        for(std::map<std::string, int>::iterator i = attributes.begin(); i != attributes.end(); ++i) {
            glBindAttribLocation(this->shaderProgram, (GLuint)i->second, i->first.c_str());
        }

        //create the shader program
        currentError = "";
        if(!linkShaderProgram(this->shaderProgram, currentError)) {
            StaticLogger::instance.error("Link shader failed\n: {string}", currentError.c_str());
        }
        else {
            StaticLogger::instance.trace("Successfully loaded shader: vertex: '{string}', fragment: '{string}'", vertexShaderPath.c_str(), fragmentShaderPath.c_str());
        }

        //load uniforms
        setUniformLocations();
    }
}

int ShaderProgram::getAttributeLocation(const std::string& name) {
    std::map<std::string, int>::iterator i = attributes.find(name);
    
    if(i != attributes.end()) {
        return i->second;
    }

    return -1;
}

void ShaderProgram::loadUniformf(unsigned int location, float value) {
    glUniform1f(location, value);
}

void ShaderProgram::loadUniformVec2f(unsigned int location, const Vector2f& value) {
    glUniform2f(location, value.x, value.y);
}

void ShaderProgram::loadUniformVec3f(unsigned int location, const Vector3f& value) {
    glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::loadUniformVec4f(unsigned int location, const Vector4f& value) {
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::loadUniformd(unsigned int location, double value) {
    glUniform1d(location, value);
}

void ShaderProgram::loadUniformVec2d(unsigned int location, const Vector2d& value) {
    glUniform2d(location, value.x, value.y);
}

void ShaderProgram::loadUniformVec3d(unsigned int location, const Vector3d& value) {
    glUniform3d(location, value.x, value.y, value.z);
}

void ShaderProgram::loadUniformVec4d(unsigned int location, const Vector4d& value) {
    glUniform4d(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::loadUniformi(unsigned int location, int value) {
    glUniform1i(location, value);
}

void ShaderProgram::loadUniformVec2i(unsigned int location, const Vector2i& value) {
    glUniform2i(location, value.x, value.y);
}

void ShaderProgram::loadUniformVec3i(unsigned int location, const Vector3i& value) {
    glUniform3i(location, value.x, value.y, value.z);
}

void ShaderProgram::loadUniformVec4i(unsigned int location, const Vector4i& value) {
    glUniform4i(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::loadUniformArrayf(unsigned int location, float* values, int count) {
    glUniform1fv(location, count, values);
}

void ShaderProgram::loadUniformArrayd(unsigned int location, double* values, int count) {
    glUniform1dv(location, count, values);
}

void ShaderProgram::loadUniformArrayi(unsigned int location, int* values, int count) {
    glUniform1iv(location, count, values);
}

void ShaderProgram::loadMatrix22f(unsigned int location, const Matrix22f& value) {
    glUniformMatrix2fv(location, 1, false, &value.data[0][0]);
}

void ShaderProgram::loadMatrix22d(unsigned int location, const Matrix22d& value) {
    glUniformMatrix2dv(location, 1, false, &value.data[0][0]);
}

void ShaderProgram::loadMatrix33f(unsigned int location, const Matrix33f& value) {
    glUniformMatrix3fv(location, 1, false, &value.data[0][0]);
}

void ShaderProgram::loadMatrix33d(unsigned int location, const Matrix33d& value) {
    glUniformMatrix3dv(location, 1, false, &value.data[0][0]);
}

void ShaderProgram::loadMatrix44f(unsigned int location, const Matrix44f& value) {
    glUniformMatrix4fv(location, 1, false, &value.data[0][0]);
}

void ShaderProgram::loadMatrix44d(unsigned int location, const Matrix44d& value) {
    glUniformMatrix4dv(location, 1, false, &value.data[0][0]);
}

void ShaderProgram::bind() {
    glUseProgram(this->shaderProgram);
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}
