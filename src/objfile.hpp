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
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_normals;
        std::vector<unsigned int> m_indices;

        // GPU-side data
        GLuint m_vao = 0;
        GLuint m_vbo_pos = 0;
        GLuint m_vbo_norm = 0;
        GLuint m_ibo = 0;

    public:
        objfile(){

        }
};