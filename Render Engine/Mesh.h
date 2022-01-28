#pragma once

#include <vector>

/**
 * Dyanmic if the mesh will be changing its veritices a lot
 * Static if the mesh will not be frequently written to
 * */
enum class BufferHint {
    STATIC,
    DYNAMIC
};

/**
 * Base class for mesh and storage information
 * @author Bryce Young 5/28/2021
 * */
class Mesh {
public:
    Mesh()
        :bufferHint(BufferHint::STATIC)
    {}

	virtual ~Mesh();

	/**
	 * Loads float
	 * */
	void addFloatData(const float* data, int count, int dimensions);

	/**
	 * Adds an attribute containing doubles
	 * */
	void addDoubleData(const double* data, int count, int dimensions);

	/**
	 * Updates an attribute VBO
	 * */
	void updateFloatData(int attribute, const float* data, int count, int dimensions);

	/**
	 * Updates double data
	 * */
	void updateDoubleData(int attribute, const double* data, int count, int dimensions);

	/**
	 * Specific operations for rendering the mesh
	 * Typically would be different for different types of meshes
	 * @param framebuffer the framebuffer on which to render
	 * */
	virtual void render() = 0;

	BufferHint getBufferHint() {
		return bufferHint;
	}

	void setBufferHint(BufferHint hint) {
		this->bufferHint = hint;
	}

	void setDrawCount(int drawCount) {
		this->drawCount = drawCount;
	}

	int getDrawCount() {
		return this->drawCount;
	}

protected:
	int vao = -1;
	std::vector<int> vbos;
	std::vector<int> vbosDimensions;

	int drawCount;

	BufferHint bufferHint;
	int getBufferMode();
};

/// <summary>
/// A mesh which is drawn with indices.
/// <author>Bryce Young 1/24/2022</author>
/// </summary>
class IndexedMesh : public Mesh
{
public:
	~IndexedMesh();

	/// <summary>
	/// Renders the mesh to a framebuffer.
	/// </summary>
	virtual void render();

	/// <summary>
	/// Sets the indices.
	/// </summary>
	/// <param name="indices"></param>
	/// <param name="count"></param>
	void setIndices(const int* indices, int count);

	/// <summary>
	/// Updates index data.
	/// </summary>
	/// <param name="indices"></param>
	/// <param name="count"></param>
	void updateIndices(const int* indices, int count);


protected:
	int indicesBuffer;
};

/**
 * Holds a 2D mesh.
 * @author Bryce Young 5/30/2021
 * */
class Mesh2D : public Mesh {
public:
	virtual void render();

protected:
};

