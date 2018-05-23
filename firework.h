#ifndef FIREWORK_H
#define FIREWORK_H
#include <QVector3D>
#include "particle.h"

class firework
{
private:
    int time_c = 0;
    QList <Particle> particles;
    int N;
public:

    firework(int N, int count);
    void inc_time();
    int particles_coordinate_size(int i);
    int particles_size();
    void recount_particles(int i);
    QVector3D particle_coordinate(int i, int j);
    QVector3D get_particle_color(int i, int j);
    float get_alpha(int i, int j);



};

#endif // FIREWORK_H
