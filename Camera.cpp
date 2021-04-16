#include "Camera.h"

Camera::Camera(QVector3D _eye, QVector3D _up, QVector3D _center)
{
    eye = _eye;
    up = _up;
    center = _center;
}

Camera::~Camera()
{
}

QMatrix4x4 Camera::getViewMatrix()
{
    QMatrix4x4 matrix;

    matrix.lookAt(this->eye, this->center, this->up);

    return matrix;
}
