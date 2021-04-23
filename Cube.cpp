#include "Cube.h"

struct VertexData
{
    QVector3D a_vertex;
    QVector3D a_normal;
    QVector2D a_uv;
};

static QOpenGLTexture *init_shader(const char *image_path)
{
    // Load cube.png image
    QOpenGLTexture *texture = new QOpenGLTexture(QImage(image_path).mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);

    return texture;
}

Cube::Cube(/* args */)
{
    VertexData vertices[] = {
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f), QVector2D(0, 0)}, // v0
        {QVector3D(1.0f, -1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f), QVector2D(1, 0)},  // v1
        {QVector3D(1.0f, 1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f), QVector2D(1, 1)},   // v2
        {QVector3D(-1.0f, 1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f), QVector2D(0, 1)},  // v3

        {QVector3D(-1.0f, 1.0f, -1.0f), QVector3D(0.0f, 1.0f, 0.0f), QVector2D(0, 0)}, // v4
        {QVector3D(1.0f, 1.0f, -1.0f), QVector3D(0.0f, 1.0f, 0.0f), QVector2D(1, 0)},  // v5
        {QVector3D(1.0f, 1.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f), QVector2D(1, 1)},   // v6
        {QVector3D(-1.0f, 1.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f), QVector2D(0, 1)},  // v7

        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f), QVector2D(0, 0)}, // v8
        {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f), QVector2D(1, 0)},  // v9
        {QVector3D(1.0f, 1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f), QVector2D(1, 1)},   // v10
        {QVector3D(-1.0f, 1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f), QVector2D(0, 1)},  // v11

        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f, -1.0f, 0.0f), QVector2D(0, 0)}, // v12
        {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(0.0f, -1.0f, 0.0f), QVector2D(1, 0)},  // v13
        {QVector3D(1.0f, -1.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f), QVector2D(1, 1)},   // v14
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f), QVector2D(0, 1)},  // v15

        {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(1.0f, 0.0f, 0.0f), QVector2D(0, 0)}, // v16
        {QVector3D(1.0f, 1.0f, -1.0f), QVector3D(1.0f, 0.0f, 0.0f), QVector2D(1, 0)},  // v17
        {QVector3D(1.0f, 1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f), QVector2D(1, 1)},   // v18
        {QVector3D(1.0f, -1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f), QVector2D(0, 1)},  // v19

        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(-1.0f, 0.0f, 0.0f), QVector2D(0, 0)}, // 20
        {QVector3D(-1.0f, 1.0f, -1.0f), QVector3D(-1.0f, 0.0f, 0.0f), QVector2D(1, 0)},  // v21
        {QVector3D(-1.0f, 1.0f, 1.0f), QVector3D(-1.0f, 0.0f, 0.0f), QVector2D(1, 1)},   // v22
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector3D(-1.0f, 0.0f, 0.0f), QVector2D(0, 1)},  // v23
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
    offset += sizeof(decltype(VertexData::a_vertex));

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    a_normal = shader->program->attributeLocation("a_normal");
    shader->program->enableAttributeArray(a_normal);
    shader->program->setAttributeBuffer(a_normal, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(decltype(VertexData::a_normal));

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    a_uv = shader->program->attributeLocation("a_uv");
    shader->program->enableAttributeArray(a_uv);
    shader->program->setAttributeBuffer(a_uv, GL_FLOAT, offset, 2, sizeof(VertexData));

    shader->program->release();
    vbo->release();
    ebo->release();
    vao->release();

    texture1 = init_shader(":/youtube.jpg");
    texture2 = init_shader(":/twitch.jpg");

    u_m.scale(QVector3D(5, 5, 5));
}

Cube::~Cube()
{
}

void Cube::draw(Light *light, Camera *camera, QMatrix4x4 u_p)
{

    shader->program->bind();
    {
        texture1->bind(0);
        texture2->bind(1);
        {
            shader->program->setUniformValue("u_tex1", 0);
            shader->program->setUniformValue("u_tex2", 1);
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
        texture1->release();
        texture2->release();
    }
    shader->program->release();
}
