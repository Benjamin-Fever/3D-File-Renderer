//
// Created by Benjamin Fever on 28/07/2022.
//
// std
#include <vector>

// glm
#include <glm/glm.hpp>

// project
#include "opengl.hpp"

#define ATTRIB_POSITION 0
#define ATTRIB_NORMAL 1


class objfile{
    private:
        // GPU-side data
        GLuint m_vao = 0;
        GLuint m_vbo_pos = 0;
        GLuint m_vbo_norm = 0;
        GLuint m_ibo = 0;

        // Position and Normal vectors
        std::vector<glm::vec3> vertexPositions;
        std::vector<glm::vec3> vertexNormals;
        std::vector<unsigned int> vertexIndices;


    public:
        void loadOBJ(char[]);

    void build();

    void draw();

    void destroy();
};

