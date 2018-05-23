#include "firework.h"
#include <QDebug>

firework::firework(int N, int count)
{
    if(count == 0){//центр в 0
        for(int i = 0;i<N;i++){
            particles.append(Particle(i, 0, 0, 0));
        }
    }
    else{//смещаем центр
        float coord[3];
        for (int i = 0; i<3; i++){
            int x = rand();
            if(x%2==0){
                coord[i]= (rand()%31)/10.0;
            }
            else{
                 coord[i]= -(rand()%31)/10.0;
            }
        }
        for(int i = 0;i<N;i++){

            particles.append(Particle(i, coord[0], coord[1], coord[2]));
        }
    }

}
QVector3D firework::particle_coordinate(int i, int j){
    return particles[i].coordinate.at(j);
}


QVector3D firework::get_particle_color(int i, int j){
    return (QVector3D(particles[i].get_color().x(),particles[i].get_color().y(),particles[i].get_color().z()));
}

float firework::get_alpha(int i, int j){
    int n = particles[i].coordinate.size();
    float del = 1/(float)n;
    if(!particles[i].waiting_for_death())
    {
        return j*del;
    }

    else
    {
        return (n-j)*del;
    }
}

void firework::inc_time(){
    time_c++;
}

int firework::particles_coordinate_size(int i){
    return particles[i].coordinate.size();
}

int firework::particles_size(){
    return particles.size();
}

void firework::recount_particles(int i){
    particles[i].recount_points(time_c);
    //qDebug()<<"пересчитали"<<i;
}
