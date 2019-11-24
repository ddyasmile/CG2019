#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <string>
#include <glm/glm.hpp>


class ObjLoader
{
private:
    std::string filename;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;
    std::vector<int> fvertices;
    std::vector<int> fnormals;
    std::vector<int> ftextures;

    int start, end, curr;
public:
    ObjLoader() {};
    ~ObjLoader() {};

    ObjLoader(std::string filename);
    void loadObj();
    void draw();
    glm::vec3 burn();
};

#endif // OBJLOADER_H