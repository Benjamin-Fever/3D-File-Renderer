//
// Created by Benjamin Fever on 28/07/2022.
//

#include "objfile.hpp"

#include <fstream> // ifstream
#include <sstream>  // istringstream
#include <iostream>
#include <string>

void objfile::loadOBJ(char filename[521]) {
    std::ifstream file(filename); // Open the file
    for (int i =0; i < 4; i++) { // Skip first 4 lines
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char line[100];
    while (file.peek() != EOF) { // Loop each line
        file.getline(line, 100); // Get the line and store it in line buffer
        std::stringstream lineStream;
        lineStream << line; // Put the line into a string stream
        char token[32];
        lineStream.getline(token, 32, ' ');


        if (std::string(token) == "v"){ // Vertex position
            glm::vec3 vertexPosition;
            lineStream >> vertexPosition.x >> vertexPosition.y >> vertexPosition.z;
            vertexPositions.push_back(vertexPosition);
        }
        else if (std::string(token) == "vn"){ // Vertex vertexNormal
            glm::vec3 vertexNormal;
            lineStream >> vertexNormal.x >> vertexNormal.y >> vertexNormal.z;
            vertexNormals.push_back(vertexNormal);
        }
        else if (std::string(token) == "f") { // Vertex face
            char rawVert[100];
            for (int i = 0; i < 3; i++) {
                char data[30];
                int p1, p2, p3;
                lineStream >> rawVert;
                std::stringstream ss;
                ss << rawVert;

                ss.getline(data, 30, '/'); // Break line by / this will put the first point in data
                p1 = std::stoi(data); // Convert the first point into an int
                ss >> p2; // push the second put into p2
                ss >> data; // push the rest of the string stream into data this will give the format of "/<num>" where num is a face value
                p3 = std::stoi(std::string(data).substr(1)); // ignore the starting / and convert it into an int
                p1--;
                p2--;
                p3--;
                vertexIndices.push_back(p1);
                vertexIndices.push_back(p3);
            }
        }
    }


}

void objfile::build(){
    if (m_vao == 0) {
        // generate buffers
        glGenVertexArrays(1, &m_vao); // VAO stores information about how the buffers are set up
        glGenBuffers(1, &m_vbo_pos); // VBO stores the Vertex data
        glGenBuffers(1, &m_vbo_norm);
        glGenBuffers(1, &m_ibo); // IBO stores the indices that make up primitives


        // VAO
        //
        glBindVertexArray(m_vao);


        // VBO
        //
        // upload Positions to this buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_pos);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexPositions.size(), vertexPositions.data(), GL_STATIC_DRAW);
        // this buffer will use location=0 when we use our VAO
        glEnableVertexAttribArray(0);
        // tell opengl how to treat data in location=0 - the data is treated in lots of 3 (3 floats = vec3)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        // do the same thing for Normals but bind it to location=1
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_norm);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexNormals.size(), vertexNormals.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        // IBO
        //
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        // upload the indices for drawing primitives
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vertexIndices.size(), vertexIndices.data(), GL_STATIC_DRAW);

        // clean up by binding VAO 0 (good practice)
        glBindVertexArray(0);
    }
}

void objfile::draw() {
    if (m_vao == 0) return;
    // bind our VAO which sets up all our buffers and data for us
    glBindVertexArray(m_vao);
    // tell opengl to draw our VAO using the draw mode and how many verticies to render
    glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
}

void objfile::destroy() {
    // delete the data buffers
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo_pos);
    glDeleteBuffers(1, &m_vbo_norm);
    glDeleteBuffers(1, &m_ibo);
    m_vao = 0;
    m_vbo_pos = 0;
    m_vbo_norm = 0;
    m_ibo = 0;
    vertexIndices.clear();
    vertexNormals.clear();
    vertexIndices.clear();
}