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

    for(int i = 0;i<N;i++){
        particles.append(Particle(i));
    }
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

    drawAxises();//оси координат

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
    //glRotatef(angleX, 1.0, 0.0, 0.0);
    //glRotatef(angleY, 0.0, 1.0, 0.0);
    //glRotatef(angleZ, 0.0, 0.0, 1.0);
    glTranslatef(figurePosition->x(), figurePosition->y(), figurePosition->z());

    glScalef(figureScale->x(), figureScale->y(), figureScale->z());

    if(timer.isActive()){
        recountPoints();
    }
    glPopMatrix();


}


float Widget::color_choice(int i, int j){
    glDisable(GL_LIGHTING);
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
    glEnable(GL_LIGHTING);

}

void Widget::recountPoints() {   

   // glDisable(GL_LIGHTING);
    time_counter++;
    glPointSize(4);
    glBegin(GL_POINTS);
    int n = particles.size();

    for(int i = 0; i < particles.size();i++){
        particles[i].recount_points(time_counter);

        int n = particles[i].coordinate.size();


        for(int j = 0; j < n; j++)
        {
            QVector3D newcoord = particles[i].coordinate.at(j);
            //float alpha = color_choice(i, j+1);
           // glColor4f(particles[i].get_color().x(), particles[i].get_color().y(), particles[i].get_color().z(), alpha);
            glVertex3f(newcoord.x(), newcoord.y(), newcoord.z());


        }
    }
    glEnd();
   // glEnable(GL_LIGHTING);

}



void Widget::setLight() {

    //material
    GLfloat material_ambient[] = {0.5, 0.5, 0.5, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);

    GLfloat material_diffuse[] = {0.5, 0.5, 0.5, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

    //light
    GLfloat ambient[] = {0.5, 0.5, 0.0, 0.5};//тень
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

    GLfloat diffuse[] = {1.0, 1.0, 0.0, 1.0};//цвет фигуры
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

    GLfloat position[] = {0.0, 2.5, 5.0, 1.0};
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

void Widget::camera_rotate(float dx, float dy, float dz){

    if(fabs(cameraPosition->y()+dy)>5)
         return;

    if(fabs(cameraPosition->x()+dx)>5)
        return;

    if(fabs(cameraPosition->z()+dz)>5)
        return;

    cameraPosition->setY(cameraPosition->y()+dy);
    cameraPosition->setX(cameraPosition->x()+dx);
    cameraPosition->setZ(cameraPosition->z()+dz);

    setPerspectiveProjection();
}

void Widget::changeCameraPositionX(float x) {

    cameraPosition->setX(x);

    setPerspectiveProjection();

}

void Widget::changeCameraPositionY(float y) {

    cameraPosition->setY(y);
    setPerspectiveProjection();

}

void Widget::changeCameraPositionZ(float z) {

    cameraPosition->setZ(z);
    setPerspectiveProjection();

}

void Widget::changeFigurePositionX(float x) {

    figurePosition->setX(x);
    setPerspectiveProjection();

}

void Widget::changeFigurePositionY(float y) {

    figurePosition->setY(y);
    setPerspectiveProjection();

}

void Widget::changeFigurePositionZ(float z) {

    figurePosition->setZ(z);
    setPerspectiveProjection();

}

void Widget::changeFigureScaleX(float x) {

    figureScale->setX(x);
    setPerspectiveProjection();

}

void Widget::changeFigureScaleY(float y) {

    figureScale->setY(y);
    setPerspectiveProjection();

}

void Widget::changeFigureScaleZ(float z) {

    figureScale->setZ(z);
    setPerspectiveProjection();

}

void Widget::changeBrightness(float b) {

    GLfloat d[] = {b, b, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, d);
    updateGL();


}





