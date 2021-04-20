#include "Light.h"

struct VertexData
{
    QVector3D a_vertex;
    QVector3D a_normal;
};

Light::Light(QVector3D _pos)
{
    pos = _pos;

    u_m.setToIdentity();
    u_m.translate(pos);

    QVector3D vertices[] = {
        QVector3D(-1.0f, -1.0f, 1.0f), // v0
        QVector3D(1.0f, -1.0f, 1.0f),  // v1
        QVector3D(-1.0f, 1.0f, 1.0f),  // v2
        QVector3D(1.0f, 1.0f, 1.0f),   // v3 V

        QVector3D(-1.0f, -1.0f, -1.0f), // v4 V
        QVector3D(1.0f, -1.0f, -1.0f),  // v5
        QVector3D(-1.0f, 1.0f, -1.0f),  // v6
        QVector3D(1.0f, 1.0f, -1.0f)    // v7
    };

    GLushort indices[] = {
        0, 1, 2, 3, 6, 7, 4, 5, 0, 1, 1, 1, 3, 5, 7, 7, 0, 0, 0, 2, 4, 6};

    initializeOpenGLFunctions();

    shader = new MyShader(":/light.vsh", ":/light.fsh");

    vbo = new QOpenGLBuffer();
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->allocate(vertices, sizeof(vertices));
    vbo_size = sizeof(vertices) / sizeof(QVector3D);

    ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ebo->create();
    ebo->bind();
    ebo->allocate(indices, sizeof(indices));
    ebo_size = sizeof(indices) / sizeof(GLushort);

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();

    shader->program->bind();

    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    a_vertex = shader->program->attributeLocation("a_vertex");
    shader->program->enableAttributeArray(a_vertex);
    shader->program->setAttributeBuffer(a_vertex, GL_FLOAT, offset, 3, sizeof(QVector3D));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    a_normal = shader->program->attributeLocation("a_normal");
    shader->program->enableAttributeArray(a_normal);
    shader->program->setAttributeBuffer(a_normal, GL_FLOAT, offset, 3, sizeof(QVector3D));

    shader->program->release();
    vbo->release();
    ebo->release();
    vao->release();
}

Light::~Light()
{
}

QVector3D Light::getLightPos()
{
    return (u_m * QVector4D(0, 0, 0, 1)).toVector3D();
}

void Light::draw(Light *light, Camera *camera, QMatrix4x4 u_p)
{
    shader->program->bind();
    {
        shader->program->setUniformValue("u_m", u_m);
        shader->program->setUniformValue("u_v", camera->getViewMatrix());
        shader->program->setUniformValue("u_p", u_p);

        shader->program->setUniformValue("u_eye", camera->eye);
        shader->program->setUniformValue("u_light", light->getLightPos());

        vao->bind();
        {
            ebo->bind();
            {
                glDrawElements(GL_TRIANGLE_STRIP, ebo_size, GL_UNSIGNED_SHORT, nullptr);
            }
            ebo->release();
        }
        vao->release();
    }
    shader->program->release();
}
