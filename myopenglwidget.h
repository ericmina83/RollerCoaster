#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include "Camera.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLShader>
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QBasicTimer>

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget *parent = nullptr);

    QMatrix4x4 projection;
    QMatrix4x4 model;

    QOpenGLShaderProgram *program;

    QOpenGLBuffer *arrayBuf;
    QOpenGLBuffer *indexBuf;

    Camera *camera;

    int array_size;
    int index_size;

    int a_fcolor;
    int a_vertex;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void timerEvent(QTimerEvent *) override;
    QBasicTimer timer;

signals:

};

#endif // MYOPENGLWIDGET_H
