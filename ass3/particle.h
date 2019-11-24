#ifndef PARTICLE_H
#define PARTICLE_H

#include "color.h"
#include "glm/glm.hpp"

typedef struct
{
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    Color color;
    float age;
    float life;
    float size;
    bool alive;
}Particle;

#endif // PARTICLE_H
