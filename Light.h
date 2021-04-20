#include "MyShader.h"

#include "Camera.h"

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

class Light : QOpenGLFunctions
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

    QVector3D pos;


public:
    Light(QVector3D _pos);
    ~Light();

    void draw(Light *light, Camera *camera, QMatrix4x4 u_p);

    QVector3D getLightPos();
    QMatrix4x4 u_m;
};