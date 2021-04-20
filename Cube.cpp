#include "Cube.h"

struct VertexData
{
    QVector3D a_vertex;
    QVector3D a_normal;
};

Cube::Cube(/* args */)
{
    VertexData vertices[] = {
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f)}, // v0
        {QVector3D(1.0f, -1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f)},  // v1
        {QVector3D(1.0f, 1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f)},   // v2
        {QVector3D(-1.0f, 1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f)},  // v3

        {QVector3D(-1.0f, 1.0f, -1.0f), QVector3D(0.0f, 1.0f, 0.0f)}, // v4
        {QVector3D(1.0f, 1.0f, -1.0f), QVector3D(0.0f, 1.0f, 0.0f)},  // v5
        {QVector3D(1.0f, 1.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)},   // v6
        {QVector3D(-1.0f, 1.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)},  // v7

        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f)}, // v8
        {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f)},  // v9
        {QVector3D(1.0f, 1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f)},   // v10
        {QVector3D(-1.0f, 1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f)},  // v11

        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f, -1.0f, 0.0f)}, // v12
        {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(0.0f, -1.0f, 0.0f)},  // v13
        {QVector3D(1.0f, -1.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f)},   // v14
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f)},  // v15

        {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(1.0f, 0.0f, 0.0f)}, // v16
        {QVector3D(1.0f, 1.0f, -1.0f), QVector3D(1.0f, 0.0f, 0.0f)},  // v17
        {QVector3D(1.0f, 1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},   // v18
        {QVector3D(1.0f, -1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},  // v19

        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(-1.0f, 0.0f, 0.0f)}, // 20
        {QVector3D(-1.0f, 1.0f, -1.0f), QVector3D(-1.0f, 0.0f, 0.0f)},  // v21
        {QVector3D(-1.0f, 1.0f, 1.0f), QVector3D(-1.0f, 0.0f, 0.0f)},   // v22
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector3D(-1.0f, 0.0f, 0.0f)},  // v23
    };

    GLushort indices[] = {
        0, 1, 3, // 0
        3, 1, 2,
        4, 7, 5, // 1
        5, 7, 6,
        8, 11, 9, // 2
        9, 11, 10,
        12, 13, 14, // 3
        12, 14, 15,
        16, 17, 18, // 4
        16, 18, 19,
        20, 23, 22, // 5
        20, 22, 21};

    initializeOpenGLFunctions();

    shader = new MyShader(":/cube.vsh", ":/cube.fsh");

    vbo = new QOpenGLBuffer();
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->allocate(vertices, sizeof(vertices));
    vbo_size = sizeof(vertices) / sizeof(VertexData);

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
    shader->program->setAttributeBuffer(a_vertex, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    a_normal = shader->program->attributeLocation("a_normal");
    shader->program->enableAttributeArray(a_normal);
    shader->program->setAttributeBuffer(a_normal, GL_FLOAT, offset, 3, sizeof(VertexData));

    shader->program->release();
    vbo->release();
    ebo->release();
    vao->release();

    u_m.scale(QVector3D(5, 5, 5));
}

Cube::~Cube()
{
}

void Cube::draw(Light *light, Camera *camera, QMatrix4x4 u_p)
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
                glDrawElements(GL_TRIANGLES, ebo_size, GL_UNSIGNED_SHORT, nullptr);
            }
            ebo->release();
        }
        vao->release();
    }
    shader->program->release();
}
