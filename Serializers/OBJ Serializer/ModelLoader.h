#ifndef INCLUDE_LOADER_H
#define INCLUDE_LOADER_H

#include "../../Math/Math.h"
#include <vector>
#include <string>

/**
 * Includes information about an indexed model loaded from a file
 * @author Bryce Young 5/28/2021
 * */
class IndexedModel {
    public:
        IndexedModel() 
            :indexCount(0),
            indices(nullptr),
            positions(nullptr),
            normals(nullptr),
            uvs(nullptr),
            positionsCount(0),
            normalsCount(0),
            uvsCount(0)
        {
        }

        int indexCount;
        int* indices = nullptr;
        float* positions = nullptr;
        float* normals = nullptr;
        float* uvs = nullptr;

        int positionsCount;
        int normalsCount;
        int uvsCount;

    ~IndexedModel() {
        delete[] indices;
        delete[] positions;
        delete[] normals;
        delete[] uvs;
    }
};

/**
 * Static class for loading models
 * OBJ+mtl and Collada files will be/are supported
 * @author Bryce Young
 * */
class ModelLoader {
    public:
        /**
         * Loads a model from an OBJ file
         * */
        static bool loadOBJ(const std::string& filePath, IndexedModel& model);
};

#endif