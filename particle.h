#ifndef PARTICLE_H
#define PARTICLE_H
#include <QVector3D>
#include <QList>
#include <QGLWidget>

class Particle
{

private:
    int id;
    float velocity;
    QVector3D color;
    int lifetime;
    int type;
    float radius;
    bool is_dying = false;
    float x0, y0, z0;

public:
    Particle();
    Particle(int ID, float x_0, float y_0, float z_0);
    QList <QVector3D> coordinate;

    float get_velocity();
    bool waiting_for_death();
    int get_id();
    QVector3D get_color();
    int get_lifetime();
    void draw_particle();
    void recount_points(int time);


};

#endif // PARTICLE_H
