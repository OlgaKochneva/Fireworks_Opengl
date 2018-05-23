#include "particle.h"
#include <QDebug>

Particle::Particle(){

}

Particle::Particle(int ID, float x_0, float y_0, float z_0)
{
    id = ID;
    velocity = rand()%3+2;
    lifetime = rand()%101;
    radius = (rand()%91)/30.0;
    color.setX((rand()%256)/255.0);
    color.setY((rand()%256)/255.0);
    color.setZ((rand()%256)/255.0);
    x0=x_0;
    y0=y_0;
    z0=z_0;

}


float Particle::get_velocity(){
    return velocity;
}

QVector3D Particle::get_color(){
    return color;
}

int Particle::get_lifetime(){
    return lifetime;
}

int Particle::get_id(){
    return id;
}

void Particle::draw_particle(){


}

bool Particle::waiting_for_death(){
    return is_dying;
}

void Particle::recount_points(int time){
    float x, y, z, step = 2 * M_PI / 100.0;
    float Angle = (time%101)*step;
    coordinate.clear();
    if(is_dying)
        return;
    if(lifetime<time)
        is_dying = true;


    for (int i = 0; (i < 5)&&(Angle<=M_PI);i++){
        x = radius+radius * cos(Angle+M_PI);
        y = radius * sin(Angle);
        z = 0;
        coordinate.append(QVector3D(x, y, z));
        Angle+=step/(velocity/4.0);
    }

    int n = coordinate.size();

    for(int i = 0; i< n; i++){
        QVector3D newcoord = coordinate.at(i);
        coordinate[i].setX(newcoord.x()*cos(id*7.2)+newcoord.z()*sin(id*7.2)+x0);
        coordinate[i].setY(newcoord.y()+y0);
        coordinate[i].setZ(-newcoord.x()*sin(id*7.2)+newcoord.z()*cos(id*7.2)+z0);
    }
}


