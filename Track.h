#include <vector>
#include <QVector3D>

struct TrackPoint
{
    QVector3D pos;
    QVector3D up;
};

struct ControlPoint
{
    QVector3D pos;
    QVector3D up;
};

float M_Cardinal[4][4] = {
    {-1 / 2.0, 2 / 2.0, -1 / 2.0, 0 / 2.0},
    {3 / 2.0, -5 / 2.0, 0 / 2.0, 2 / 2.0},
    {-3 / 2.0, 4 / 2.0, 1 / 2.0, 0 / 2.0},
    {1 / 2.0, -1 / 2.0, 0 / 2.0, 0 / 2.0}};

float M_B_Spline[4][4] = {
    {-1 / 6.0, 3 / 6.0, -3 / 6.0, 1 / 6.0},
    {3 / 6.0, -6 / 6.0, 0 / 6.0, 4 / 6.0},
    {-3 / 6.0, 3 / 6.0, 3 / 6.0, 1 / 6.0},
    {1 / 6.0, 0, 0, 0}};

class Track
{
public:
    Track();
    ~Track();

    std::vector<TrackPoint> trackPoints;
    std::vector<ControlPoint> controlPoints;
};
