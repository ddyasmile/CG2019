#include "particalsystem.h"

ParticalSystem::ParticalSystem()
{
    //ctor
}

ParticalSystem::~ParticalSystem()
{
    //dtor
}

ParticalSystem::ParticalSystem(int _count,float _gravity,float _size,float _age,glm::vec3 _launcher) 
{
    ptlCount=_count;
    gravity=_gravity;
    particleSize=_size;
    particleStartAge=_age;
    launcher = _launcher;
};

void ParticalSystem::init()
{
    heart = glm::vec3(10.0,0.0,0.0);
    radius = 10.0;
    phy = PI/2;
    xita = 0.0;
    dphy = 0.0;
    dxita = 0.0;
    launcher = glm::vec3(100.0,100.0,100.0);
    alive = 1;

    int i;
    srand(unsigned(time(0)));
    Color colors[3]={{0,0,1,1},{1,1,0,1},{1,0,0,1}};
    for(i=0;i<ptlCount;i++)
    {
        //theta =(rand()%361)/360.0* 2*PI;
        Particle tmp={
            launcher,
            glm::vec3(((rand()%50)-26.0f)*particleSize,((rand()%50)-26.0f)*particleSize,((rand()%50)-26.0f)*particleSize),
            glm::vec3(0,0,0),
            colors[rand()%3],
            particleStartAge,
            0.5f+(float)(0.05*(rand()%10)),
            0.3f,
            1
        };
        particles.push_back(tmp);
    }
    mySphere=gluNewQuadric();
}

void ParticalSystem::simulate(float dt)
{
    aging(dt);
    applyGravity();
    kinematics(dt);
}

void ParticalSystem::aging(float dt)
{
    std::vector<Particle>::iterator iter;
    for(iter=particles.begin();iter!=particles.end();iter++)
    {
        iter->age+=dt;
        if(iter->age>iter->life)
        {
            if (!this->alive) {
                iter->alive = false;
                continue;
            }
            iter->position=launcher;
            iter->age=0.0;
            iter->velocity=glm::vec3(((rand()%30)-15.0f),((rand()%30)-11.0f),((rand()%30)-15.0f));
        }
    }
}

void ParticalSystem::applyGravity()
{
    std::vector<Particle>::iterator iter;
    for(iter=particles.begin();iter!=particles.end();iter++)
        iter->acceleration=glm::vec3(0,gravity,0);
}

void ParticalSystem::kinematics(float dt)
{
    std::vector<Particle>::iterator iter;
    for(iter=particles.begin();iter!=particles.end();iter++)
    {
        iter->position = iter->position+iter->velocity*dt;
        iter->velocity = iter->velocity+iter->acceleration*dt;
    }
}

void ParticalSystem::render()
{
    std::vector<Particle>::iterator iter;
    for(iter=particles.begin();iter!=particles.end();iter++)
    {
        if (!iter->alive) {
            continue;
        }
        float alpha = 1 - iter->age / iter->life; //calculate the alpha value according to the age of particle.
        glm::vec3 tmp=iter->position;
        glColor4f(iter->color.r,iter->color.g,iter->color.b,alpha);
        glPushMatrix();
        // gluSphere(mySphere ,iter->size, 32, 16);
        glBegin(GL_QUADS);
        glVertex3f(tmp.x,tmp.y,tmp.z);
        glVertex3f(tmp.x+(float)(0.05*(rand()%10))*particleSize,tmp.y,tmp.z);
        glVertex3f(tmp.x+(float)(0.05*(rand()%10))*particleSize,tmp.y+(float)(0.05*(rand()%10))*particleSize,tmp.z);
        glVertex3f(tmp.x,tmp.y+(float)(0.05*(rand()%10))*particleSize,tmp.z);
        glEnd();
        glPopMatrix();
    }

    // glColor4f(0.0f,0.0f,0.0f,0.3);
    // glBegin(GL_QUADS);
    // glVertex3f(9.0f,-100.0f,-100.0f);
    // glVertex3f(9.0f,100.0f,-100.0f);
    // glVertex3f(9.0f,100.0f,100.0f);
    // glVertex3f(9.0f,-100.0f,100.0f);
    // glEnd();
}

glm::vec3 ParticalSystem::move()
{
    float next_phy = phy+dphy;
    if (next_phy<0) {
        next_phy = -next_phy;
        dphy = -dphy;
        xita += PI;
    }else if (next_phy>PI) {
        next_phy = PI - (next_phy-PI);
        dphy = -dphy;
        xita += PI;
    }

    float next_xita = xita + dxita;
    phy = next_phy;
    xita = next_xita;

    float x = radius*sinf(phy)*cosf(xita) + heart.x;
    float y = radius*sinf(phy)*sinf(xita) + heart.y;
    float z = radius*cosf(phy) + heart.z;

    return glm::vec3(x,y,z);
}

void ParticalSystem::kill()
{
    this->alive = false;
}

