#include <fstream>
#include <sstream>
#include <iostream>
#include "objloader.h"
#include "GL/glu.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "glm/glm.hpp"

ObjLoader::ObjLoader(std::string filename)
{
    this->filename = filename;
}

void ObjLoader::loadObj()
{
    std::ifstream in(filename, std::ios::in);
    if (!in) {
        // std::cerr << "Cannot open " << filename << std::endl;
        return;
    }

    // std::cout << "loading: "<<filename<<std::endl;
    std::string line;
    // int linecount = 0;
    while(getline(in, line)) {
        // linecount++;
        // std::cout << "line: "<<linecount<<std::endl;
        if (line.substr(0,2) == "v ") {
            std::stringstream s(line.substr(2));
            glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
            v.x*=30; v.y*=30; v.z*=30;
            vertices.push_back(v);
        }else if (line.substr(0,3) == "vt ") {
            std::stringstream s(line.substr(3));
            glm::vec2 v; s >> v.x; s >> v.y;
            textures.push_back(v);
        }else if (line.substr(0,3) == "vn ") {
            std::stringstream s(line.substr(3));
            glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
            normals.push_back(v);
        }else if (line.substr(0,2) == "f ") {
            std::string data = line.substr(2);
            int verticeIndex[4], uvIndex[4], normalIndex[4];
            // std::cout<<data<<std::endl;
            sscanf(data.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                &verticeIndex[0], &uvIndex[0], &normalIndex[0],
                &verticeIndex[1], &uvIndex[1], &normalIndex[1],
                &verticeIndex[2], &uvIndex[2], &normalIndex[2],
                &verticeIndex[3], &uvIndex[3], &normalIndex[3]);
            // std::cout<<"scan done"<<std::endl;
            for (int i=0; i<4; i++) {
                fvertices.push_back(verticeIndex[i]-1);
                ftextures.push_back(uvIndex[i]-1);
                fnormals.push_back(normalIndex[i]-1);
            }
        }else{
            // ignore this line
        }
    }

    // std::cout <<"vertex: "<< vertices.size() << std::endl;
    // std::cout <<"faces: "<< fvertices.size() << std::endl;
    start = 128; end = 425; curr = 425;
}

void ObjLoader::draw()
{
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    int size = fvertices.size();
    for (int i=0; i<size; i+=4) {
        int ia = fvertices[i];
        int ib = fvertices[i+1];
        int ic = fvertices[i+2];
        int id = fvertices[i+3];

        if (i>=curr&&i<end) {
            continue;
            // std::cout << vertices[ia].x << " ";
            // std::cout << vertices[ia].y << " ";
            // std::cout << vertices[ia].z << " ";
            // std::cout << std::endl;
        }

        glVertex3f(vertices[ia].x, vertices[ia].y, vertices[ia].z);
        glVertex3f(vertices[ib].x, vertices[ib].y, vertices[ib].z);
        glVertex3f(vertices[ic].x, vertices[ic].y, vertices[ic].z);
        glVertex3f(vertices[id].x, vertices[id].y, vertices[id].z);
    }
    glEnd();
    glPopMatrix();
    // std::cout << "draw done"<<std::endl;
}

glm::vec3 ObjLoader::burn()
{
    if (curr > start) {
        curr--;
    }
    return vertices[fvertices[curr]];
}
