# Assignment3

A bomb!

## Run

Install libs on Ubuntu

``` 
sudo apt-get install build-essential libgl1-mesa-dev
sudo apt-get install libglew-dev libsdl2-dev libsdl2-image-dev libglm-dev libfreetype6-dev
sudo apt-get install libglfw3-dev libglfw3
sudo apt-get install libglu1-mesa-dev
sudo apt-get install freeglut3-dev
```

make
```
make
```

run
```
./main
```

Then do nothing.

## Intruction

It consists of main, objloader and particalsystem.

## Partical System

In `particle.h`

```
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
```

> `age` and `life` describe how long a particle can keep alive, if `age` becomes greater then `life`, `age` will be reset to give this particle a new life. 
>
> `size` is used to describe size of the particle, but now it is abandoned.
>
> If `alive` is false, this particle won't be shown.

In `particlesystem.h`

```
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
```

> `launcher` is where particles will be launched. `ptlCount` is number of particles. `gravity` is value of gravity. `particles` store all particles. `mySphere` is used to describe the shape of particles, but now particles will be draw in `render` directly.
>
> `xita`, `phy`, `dxita`, `dphy`, `radius` and `heart` are parameters of a sphere. Partical system can call `move()` to get next position of launcher so that this partical system seems to be traveling on the surface of the sphere. But at last, I directly change launcher with a `glm::vec3` returned by `ObjLoader::burn()` to bind the partical system and the Bomb.
>
> `alive` describes if this system will keep alive. `kill()` can turn it to false and then those particles whoes age is too great will be not alive instead of reset. Particles in the system will not be killed once the system is killed, they will still alive until they are too old.
>
> `particleSize` describes the size of particles. `particleStartAge` is the initial value of age of particles.
>
> `ParticalSystem(int,float,float,float,glm::vec3)` has five parameters. Number of particles, gravity, size of particles, initial value of age of particles and initial value of launcher.

In `particlesystem.cpp`

```
void ParticalSystem::init();

void ParticalSystem::aging(float dt);

void ParticalSystem::render();
```

> `init()` will initialize particles with `launcher` and a random velocity.
>
> `aging(float dt)` will reset age of particles whoes age is greater then life if the system is alive.
>
> `render()` will draw the partical system. It will ignore particles whoes `alive` is false. It will add a random number to `position` of particles to generate three more points and draw quadrilateral. 

## Obj Loader

In objloader.h

```
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
```

> `start` and `end` is index of begin and end of the bomb's fuse. `curr` means how long the fuse left. `burn()` will change `curr` and return the position of fuse.
> 
> `loadObj()` read .obj file. `draw()` draw the bomb but it will ignore part of fuse according to `start`, `end` and `curr`.

## Main

There are two partical system, one for fuse and another for bomb. In fact, these two system are both alive but system for bomb is out of the window. I use `bombCount` to decide if it is time to kill system for fuse and make the system for bomb visible.

## More

* There is texture information in ObjLoader. I have read all information of bomb.obj but I don't show the texture because this part is a little hard.

* I don't implement click to start because I have not time. I have idea about this. At first, only draw the bomb and initialize partical systems. Then bind `burn()` and `ParticalSystem::render()` to an click event.

* I make bomb invisible directly. It can also be a partical system when it explodes, but the velocity of each particles can't be random.

## Reference

[Partical System](https://blog.csdn.net/silangquan/article/details/8373896)

[Obj Loader](https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ)

