#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#include "objloader.h"
#include "particalsystem.h"

ParticalSystem ps;
ParticalSystem bombPs;
ObjLoader bombLoader;
int bombCount = 0;

static void display();
static void rander();

int main(int argc, char **argv)
{
    GLenum type;
    type = GLUT_RGBA | GLUT_DOUBLE;

    glutInit(&argc, argv);
    glutInitDisplayMode(type);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1280,960);
    
    glutCreateWindow("Bomb!");

    glClearColor(1.0,1.0,1.0,0.0);
    glutDisplayFunc(display);
    glutIdleFunc(rander);
    glutMainLoop();
}

static void display()
{
    ps = ParticalSystem(600, -120, 1, 0.5, glm::vec3(0.0,0.0,0.0));
    ps.init();

    bombPs = ParticalSystem(5000, -40, 3, 0.0, glm::vec3(0.0,0.0,0.0));
    bombPs.init();
    // bombPs.kill();

    std::string filename = "Bomb/Bomb.obj";
    bombLoader = ObjLoader(filename);
    bombLoader.loadObj();
}

static void rander()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, 1280.0/960.0, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, -10.0);
    
    glm::vec3 burned = bombLoader.burn();
    if (bombCount == 0) {
        if (burned == ps.launcher) {
            bombCount++;
        }
        ps.launcher = burned;
        bombLoader.draw();

    }else if (bombCount == 1) {
        ps.kill();
        bombLoader.draw();
        bombCount++;
    }else if (bombCount>1&&bombCount<70) {
        bombLoader.draw();
        bombCount++;
        if (bombCount==69) {
            bombPs.launcher = glm::vec3(
                burned.x,
                burned.y-3,
                burned.z+3
            );
            // bombPs.kill();
        }
    }else if (bombCount == 70) {
        // bombPs.simulate(0.01);
        // bombPs.render();
        bombPs.kill();
    }

    bombPs.simulate(0.01);
    bombPs.render();
    ps.simulate(0.01);
    ps.render();
    glutSwapBuffers();
}