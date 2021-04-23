#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera(QVector3D _eye, QVector3D _up, QVector3D _front);
    ~Camera();

    QVector3D eye;
    QVector3D up;
    QVector3D front;
    QVector3D right;

    QMatrix4x4 getViewMatrix();
    void transform(QMatrix4x4 m);
};

#endif
