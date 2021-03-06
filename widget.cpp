#include "widget.h"
#include <QDebug>
#include <qmath.h>
#include <QString>
#include <QVector3D>
#include <GL/glu.h>
#include <QDebug>



Widget::Widget(QWidget *parent = 0) : QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(60);

    angleX = 0, angleY = 0, angleZ = 0;
    cameraPosition = new QVector3D(3, 4, 5);
    figurePosition = new QVector3D(0, 0, 0);
    figureScale = new QVector3D(1, 1, 1);
    fire.append(firework(50,0));
    recountPoints();
}

void Widget::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    setLight();
    setPerspectiveProjection();
}



void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
}



void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //drawAxises();//оси координат

    //расположение света
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    GLfloat position[] = {0.0, 2.5, 3.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glPopMatrix();

    //положение фигуры


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);
    glTranslatef(figurePosition->x(), figurePosition->y(), figurePosition->z());
    glScalef(figureScale->x(), figureScale->y(), figureScale->z());

    recountPoints();
    glPopMatrix();
}




void Widget::recountPoints() {   

    glPointSize(4);
    glBegin(GL_POINTS);

    for(int f = 0; f<fire.size();f++){
        if(timer.isActive())
        {
            fire[f].inc_time();
        }

        for(int i = 0; i<fire[f].particles_size();i++){
            fire[f].recount_particles(i);
            int n = fire[f].particles_coordinate_size(i);
            for(int j = 0; j<n;j++){
                QVector3D newcoord = fire[f].particle_coordinate(i, j);
                QVector3D color = fire[f].get_particle_color(i, j);
                glColor4f(color.x(), color.y(), color.z(), fire[f].get_alpha(i, j));
                glVertex3f(newcoord.x(), newcoord.y(), newcoord.z());

            }
        }


    }
    glEnd();

}
void Widget::add_new_firework(){
    int c = fire.size();
    fire.append(firework(50,c));
}


void Widget::setLight() {

    //material

    GLfloat material_diffuse[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat shine[] = {50};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);


    GLfloat diffuse[] = {1.0, 1.0, 1.0, 0.0};//цвет фигуры
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

    GLfloat position[] = {0.0, 2.5, 20.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, position);


    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.09);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
}

void Widget::drawAxises() {

    glDisable(GL_LIGHTING);
    //х координата
    qglColor(Qt::blue);
    glBegin(GL_LINES);
    glVertex3f(-axisSize, 0.0, 0.0);
    glVertex3f(axisSize, 0.0, 0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(axisSize, 0.0, 0.0);
    glVertex3f(axisSize - arrowSize*3, arrowSize, 0.0);
    glVertex3f(axisSize - arrowSize*3, -arrowSize, 0.0);
    glEnd();
    //у координата
    qglColor(Qt::red);
    glBegin(GL_LINES);
    glVertex3f(0.0, -axisSize, 0.0);
    glVertex3f(0.0, axisSize, 0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, axisSize, 0.0);
    glVertex3f(-arrowSize, axisSize - arrowSize*3, 0.0);
    glVertex3f(arrowSize, axisSize - arrowSize*3, 0.0);
    glEnd();
    //z координата
    qglColor(Qt::green);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -axisSize);
    glVertex3f(0.0, 0.0, axisSize);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.0, axisSize);
    glVertex3f(-arrowSize, 0.0, axisSize - arrowSize*3);
    glVertex3f(arrowSize, 0.0, axisSize - arrowSize*3);
    glEnd();

    glEnable(GL_LIGHTING);
}

void Widget::setPerspectiveProjection() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, 1, 1, 100);
    gluLookAt(cameraPosition->x(), cameraPosition->y(), cameraPosition->z(), 0, 3.0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    updateGL();


}

void Widget::camera_rotate(int dx, int dy, int dz){
    angleX += dx%361;
    angleY += dy%361;
    angleZ += dz%361;
    setPerspectiveProjection();
}






