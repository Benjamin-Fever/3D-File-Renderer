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
    for (int i =0; i < 9; i++) { // Skip first 9 lines
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
            char data[100];
            for (int i = 0; i < 3; i++) {
                lineStream >> data;

            }
        }
    }
}
