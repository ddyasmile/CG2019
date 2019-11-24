#ifndef PARTICALSYSTEM_H
#define PARTICALSYSTEM_H

#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "particle.h"

#define PI 3.1415926

class ParticalSystem
{
    public:
        glm::vec3 launcher;
        void kill();

        ParticalSystem();
        virtual ~ParticalSystem();
        ParticalSystem(int,float,float,float,glm::vec3);
        // 初始化粒子系统
        void init();
        // 粒子模拟总负责函数
        void simulate(float dt);
        // 计算粒子年龄
        void aging(float dt);
        // 向粒子施加重力
        void applyGravity();
        // 管理粒子加速，位移
        void kinematics(float dt);
        // 渲染粒子
        void render();
        
    protected:
    private:
    int ptlCount;
    float gravity;
    GLUquadricObj *mySphere;
    std::vector<Particle> particles;

    float xita;
    float phy;
    float dxita;
    float dphy;
    float radius;
    glm::vec3 heart;

    glm::vec3 move();

    bool alive;
    float particleSize;
    float particleStartAge;
};

#endif // PARTICALSYSTEM_H

