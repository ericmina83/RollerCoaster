#include "myopenglwidget.h"

#include <QVector2D>
#include <QVector3D>

#include <QColor>

struct VertexData
{
    QVector3D a_vertex;
    QVector3D a_fcolor;
};

VertexData vertices[] = {
    {QVector3D(-1.0f, -1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)}, // v0
    {QVector3D(1.0f, -1.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)},  // v1
    {QVector3D(-1.0f, 1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f)},  // v2
    {QVector3D(1.0f, 1.0f, 1.0f), QVector3D(0.0f, 0.0f, 0.0f)},   // v3 V

    {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f, 0.0f)}, // v4 V
    {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f, 1.0f)},  // v5
    {QVector3D(-1.0f, 1.0f, -1.0f), QVector3D(0.0f, 1.0f, 0.0f)},  // v6
    {QVector3D(1.0f, 1.0f, -1.0f), QVector3D(1.0f, 0.0f, 0.0f)},   // v7
};

GLushort indices[] = {
    0, 1, 2, 3, 6, 7, 4, 5, 0, 1, 1, 1, 3, 5, 7, 7, 0, 0, 0, 2, 4, 6};

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    program = new QOpenGLShaderProgram();
    arrayBuf = new QOpenGLBuffer();
    indexBuf = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
}

void MyOpenGLWidget::initializeGL()
{
    qDebug() << "initializeGL";
    // Set up the rendering context, load shaders and other resources, etc.:

    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaderv.glsl"))
    {
        qDebug() << "Vertex Shader Error " << program->log();
        close();
    }

    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaderf.glsl"))
    {
        qDebug() << "Fragment Shader Error " << program->log();
        close();
    }

    if (!program->link())
    {
        qDebug() << "link Error " << program->log();
        close();
    }

    if (!program->bind())
    {
        qDebug() << "bind Error " << program->log();
        close();
    }

    // Transfer vertex data to VBO 0
    arrayBuf->create();
    arrayBuf->bind();
    arrayBuf->allocate(vertices, sizeof(vertices));
    array_size = sizeof(vertices) / sizeof(VertexData);

    // Transfer index data to VBO 1
    indexBuf->create();
    indexBuf->bind();
    indexBuf->allocate(indices, sizeof(indices));
    index_size = sizeof(indices) / sizeof(GLushort);

    timer.start(33, this);

    camera = new Camera(
        QVector3D(0, 0, 5),
        QVector3D(0, 1, 0),
        QVector3D(0, 0, 0));
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    qDebug() << "resizeGL";

    // Update projection matrix and other size-related settings:
    glViewport(0, 0, w, h);

    float aspectRatio = (float)w / (float)h;

    projection.setToIdentity();
    projection.perspective(45.0f, aspectRatio, 0.1f, 1000.0f);

    program->setUniformValue("u_p", projection);
}

void MyOpenGLWidget::paintGL()
{
    // qDebug() << "paintGL";

    // Draw the scene:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->setUniformValue("u_m", model);
    program->setUniformValue("u_v", camera->getViewMatrix());

    arrayBuf->bind();
    indexBuf->bind();

    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    a_vertex = program->attributeLocation("a_vertex");
    program->enableAttributeArray(a_vertex);
    program->setAttributeBuffer(a_vertex, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    a_fcolor = program->attributeLocation("a_fcolor");
    program->enableAttributeArray(a_fcolor);
    program->setAttributeBuffer(a_fcolor, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, index_size, GL_UNSIGNED_SHORT, 0);
}

void MyOpenGLWidget::timerEvent(QTimerEvent *)
{
    model.rotate(5.0f, QVector3D(1, 1, 1));

    update();
}
