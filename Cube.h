#include "MyShader.h"

#include "Camera.h"
#include "Light.h"

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

class Cube : QOpenGLFunctions
{
private:
    MyShader *shader;

    QOpenGLBuffer *vbo;
    QOpenGLBuffer *ebo;

    QOpenGLVertexArrayObject *vao;

    int vbo_size;
    int ebo_size;

    int a_vertex;
    int a_normal;

    QMatrix4x4 u_m;

public:
    Cube();
    ~Cube();

    void draw(Light *light, Camera *camera, QMatrix4x4 u_p);
};
