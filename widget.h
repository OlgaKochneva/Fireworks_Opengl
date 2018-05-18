#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QVector3D>
#include <QTimer>
#include <QMouseEvent>

#include "particle.h"



class Widget: public QGLWidget{



private:
    QList <Particle> particles;
    int N=50;
    QTimer timer;
    int time_counter = 0;

    float axisSize = 3.5, arrowSize = 0.1;



public:

    float angleX, angleZ, angleY;
    float max_rad = 2.5;//радиус салюта максимальный


    QVector3D *cameraPosition;
    QVector3D *figurePosition;
    QVector3D *figureScale;

    Widget(QWidget*);
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    float color_choice(int i, int j);

    void setPerspectiveProjection();

    void drawAxises();
    void setLight();
    void changeBrightness(float b);


    void changeCameraPositionX(float x);
    void changeCameraPositionY(float y);
    void changeCameraPositionZ(float z);

    void changeFigurePositionX(float x);
    void changeFigurePositionY(float y);
    void changeFigurePositionZ(float z);

    void changeFigureScaleX(float x);
    void changeFigureScaleY(float y);
    void changeFigureScaleZ(float z);


    void recountPoints();



};

#endif // WIDGET_H
