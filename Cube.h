#include "MyShader.h"

#include "Camera.h"
#include "Light.h"

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>

class Cube : QOpenGLFunctions
{
private:
    MyShader *shader;

    QOpenGLBuffer *vbo;
    QOpenGLBuffer *ebo;

    QOpenGLVertexArrayObject *vao;

    QOpenGLTexture *texture1;
    QOpenGLTexture *texture2;

    int vbo_size;
    int ebo_size;

    int a_vertex;
    int a_normal;
    int a_uv;

    QMatrix4x4 u_m;

public:
    Cube();
    ~Cube();

    void draw(Light *light, Camera *camera, QMatrix4x4 u_p);
};
