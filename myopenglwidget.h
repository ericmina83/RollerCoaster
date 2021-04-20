#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include "Camera.h"
#include "Cube.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLShader>
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QBasicTimer>
#include <QOpenGLVertexArrayObject>

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget *parent = nullptr);

    QMatrix4x4 projection;

    Camera *camera;
    Light *light;
    Cube *cube;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void timerEvent(QTimerEvent *) override;
    QBasicTimer timer;
};

#endif // MYOPENGLWIDGET_H
