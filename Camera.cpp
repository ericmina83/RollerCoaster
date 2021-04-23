#include "Camera.h"

Camera::Camera(QVector3D _eye, QVector3D _up, QVector3D center)
{
    eye = _eye;
    front = center - _eye;
    right = QVector3D::crossProduct(front, _up);
    up = QVector3D::crossProduct(right, front);
}

Camera::~Camera()
{
}

QMatrix4x4 Camera::getViewMatrix()
{
    QMatrix4x4 matrix;

    matrix.lookAt(this->eye, this->eye + front, this->up);

    return matrix;
}

void Camera::transform(QMatrix4x4 m)
{
    eye = (m * QVector4D(eye, 1.0f)).toVector3D();

    m = m.transposed().inverted();

    up = (m * QVector4D(up, 0.0f)).toVector3D();
    front = (m * QVector4D(front, 0.0f)).toVector3D();
    right = (m * QVector4D(right, 0.0f)).toVector3D();
}
