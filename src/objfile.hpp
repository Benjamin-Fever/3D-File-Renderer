//
// Created by Benjamin Fever on 28/07/2022.
//
// std
#include <vector>

// glm
#include <glm/glm.hpp>

// project
#include "opengl.hpp"


class objfile{
    private:
        struct vertex {
            glm::vec3 position;
            glm::vec2 uv;
            glm::vec3 normal;
        };

        std::vector<glm::vec3> vertexPositions;
        std::vector<glm::vec3> vertexNormals;
        std::vector<int> vertexIndices;

    public:
        std::vector<vertex> vertexs;
        void loadOBJ(char[]);
};

