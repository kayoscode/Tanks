#include "Mesh.h"

#include "../lib/glew/include/GL/glew.h"

void Mesh::addFloatData(const float* data, int count, int dimensions) 
{
    if(vao == -1) {
        glGenVertexArrays(1, (GLuint*)&vao);
    }

    //bind the vao before modifying the data
    glBindVertexArray(vao);
    
    //gen VBO
    GLuint vbo;
    glGenBuffers(1, (GLuint*)&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //write to vbo
    glEnableVertexAttribArray((GLuint)vbos.size());
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, getBufferMode());

    glVertexAttribPointer((GLuint)vbos.size(), dimensions, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vbos.push_back(vbo);
}

void Mesh::addDoubleData(const double* data, int count, int dimensions) 
{
    if(vao == -1) {
        glGenVertexArrays(1, (GLuint*)&vao);
    }

    //bind the vao before modifying the data
    glBindVertexArray(vao);
    
    //gen VBO
    GLuint vbo;
    glGenBuffers(1, (GLuint*)&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //write to vbo
    glEnableVertexAttribArray((GLuint)vbos.size());
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(double), data, getBufferMode());

    glVertexAttribPointer((GLuint)vbos.size(), dimensions, GL_DOUBLE, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vbos.push_back(vbo);
}

void Mesh::updateDoubleData(int attribute, const double* data, int count, int dimensions) 
{
    //update double data
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[attribute]);
    glEnableVertexAttribArray(vbos[attribute]);

    //glBufferSubData(GL_ARRAY_BUFFER, count * sizeof(double), data, getBufferMode());
    glVertexAttribPointer(vbos[attribute], dimensions, GL_DOUBLE, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::updateFloatData(int attribute, const float* data, int count, int dimensions) 
{
    //update float data
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[attribute]);
    glEnableVertexAttribArray(attribute);

    //get the buffer size
    GLint size = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    if(sizeof(float) * count > size) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, data, getBufferMode());
        //glVertexAttribPointer(vbos[attribute], dimensions, GL_FLOAT, GL_FALSE, 0, NULL);
    }
    else {
        glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float), data);
        //glVertexAttribPointer(vbos[attribute], dimensions, GL_FLOAT, GL_FALSE, 0, NULL);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int Mesh::getBufferMode() 
{
    if(bufferHint == BufferHint::STATIC) {
        return GL_STATIC_DRAW;
    }
    else if(bufferHint == BufferHint::DYNAMIC) { 
        return GL_DYNAMIC_DRAW;
    }

    return GL_DYNAMIC_DRAW;
}

Mesh::~Mesh()
{
    if (vao != -1)
    {
		glBindVertexArray(vao);

        for (int i = 0; i < this->vbos.size(); i++)
        {
            glDeleteBuffers(1, (GLuint*)&vbos[i]);
        }

        glDeleteVertexArrays(1, (GLuint*)&vao);
    }
}

IndexedMesh::~IndexedMesh()
{
    if (vao != -1)
    {
		glBindVertexArray(vao);

        glDeleteBuffers(1, (GLuint*)&indicesBuffer);
    }
}

void IndexedMesh::setIndices(const int* indices, int count) 
{
    drawCount = count;

    if(vao == -1) {
        glGenVertexArrays(1, (GLuint*)&vao);
    }

    glBindVertexArray(vao);

    glGenBuffers(1, (GLuint*)&indicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int), indices, getBufferMode());
}

void IndexedMesh::updateIndices(const int* indices, int count) 
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int), indices, getBufferMode());
}

void IndexedMesh::render()
{
    glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);

	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
}

void Mesh2D::render()
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, drawCount);

	//glEnableVertexArrayAttrib
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}
