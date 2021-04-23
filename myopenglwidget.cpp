#include "myopenglwidget.h"

#include <QVector2D>
#include <QVector3D>

#include <QColor>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void MyOpenGLWidget::initializeGL()
{
    qDebug() << "initializeGL";
    // Set up the rendering context, load shaders and other resources, etc.:

    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    timer.start(33, this);

    camera = new Camera(
        QVector3D(25, 25, 25),
        QVector3D(0, 1, 0),
        QVector3D(0, 0, 0));

    light = new Light(QVector3D(-10, 10, 10));

    cube = new Cube();
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    qDebug() << "resizeGL";

    // Update projection matrix and other size-related settings:
    glViewport(0, 0, w, h);

    float aspectRatio = (float)w / (float)h;

    projection.setToIdentity();
    projection.perspective(45.0f, aspectRatio, 0.1f, 1000.0f);
}

void MyOpenGLWidget::paintGL()
{
    // qDebug() << "paintGL";

    // Draw the scene:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cube->draw(light, camera, projection);
    light->draw(light, camera, projection);
}

void MyOpenGLWidget::timerEvent(QTimerEvent *)
{
    // model.rotate(5.0f, QVector3D(2, -2, 2));

    static float angle = 0.0f;

    light->u_m.setToIdentity();
    light->u_m.rotate(angle += 2, QVector3D(0, 1, 0));
    light->u_m.translate(QVector3D(0, 10, 10));

    update();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        m_x = m_prev_x = event->localPos().x();
        m_y = m_prev_y = event->localPos().y();

        right_button_press = true;
    }
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        right_button_press = false;
    }
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (right_button_press)
    {
        m_x = event->localPos().x();
        m_y = event->localPos().y();

        QMatrix4x4 m;

        m.rotate((m_prev_x - m_x) / 5.0f, camera->up);
        m.rotate((m_prev_y - m_y) / 5.0f, camera->right);

        camera->transform(m);

        m_prev_x = m_x;
        m_prev_y = m_y;
    }
}