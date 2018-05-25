#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QVector3D>
#include <QVector4D>

#include <QTimer>
#include <QMouseEvent>

//#include "particle.h"
#include "firework.h"


class Widget: public QGLWidget{



private:
    QList <firework> fire;
    int N=50;
    int time_counter = 0;
    float axisSize = 3.5, arrowSize = 0.1;



public:
    QTimer timer;

    float angleX, angleZ, angleY;
    float max_rad = 2.5;//радиус салюта максимальный


    QVector3D *cameraPosition;
    QVector3D *figurePosition;
    QVector3D *figureScale;

    Widget(QWidget*);
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();
    void add_new_firework();
    void setPerspectiveProjection();
    void drawAxises();
    void setLight();
    void recountPoints();
    void camera_rotate(int dx, int dy, int dz);


};

#endif // WIDGET_H
