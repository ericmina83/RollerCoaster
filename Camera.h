#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera(QVector3D _eye, QVector3D _up, QVector3D _center);
    ~Camera();

    QVector3D eye;
    QVector3D up;
    QVector3D center;

    QMatrix4x4 getViewMatrix();
};
