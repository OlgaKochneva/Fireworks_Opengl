#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include <QResizeEvent>
#include <qmath.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QGLFormat fmt;
    fmt.setSampleBuffers(true);
    fmt.setSamples(16);
    QGLFormat::setDefaultFormat(fmt);
    glwidget = new Widget(this);
    int width = size().width() - 245;
    int height = size().height() - 10;
    glwidget->setGeometry(235, 5, width, height);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    int width = e->size().width() - 245;
    int height = e->size().height() - 10;
    glwidget->setGeometry(235, 5, width, height);
    glwidget->resizeGL(width, height);
}


//положение наблюдателя
void MainWindow::on_xSlider_valueChanged(int value)
{
    glwidget->changeCameraPositionX(value * 10.0 / 100.0 - 5.0);
}

void MainWindow::on_ySlider_valueChanged(int value)
{
    glwidget->changeCameraPositionY(value * 10.0 / 100.0 - 5.0);
}

void MainWindow::on_zSlider_valueChanged(int value)
{
    glwidget->changeCameraPositionZ(value * 10.0 / 100.0 - 5.0);
}
//поворот
void MainWindow::on_oxSlider_valueChanged(int value)
{
    glwidget->angleX = value / 100.0 * 360;
    glwidget->update();
}

void MainWindow::on_ozSlider_valueChanged(int value)
{
    glwidget->angleZ = value / 100.0 * 360;
    glwidget->update();
}

void MainWindow::on_oySlider_valueChanged(int value)
{
    glwidget->angleY = value / 100.0 * 360;
    glwidget->update();
}
//смещение
void MainWindow::on_fxSlider_valueChanged(int value)
{
    glwidget->changeFigurePositionX(value * 10.0 / 100.0 - 5.0);
}


void MainWindow::on_fySlider_valueChanged(int value)
{
    glwidget->changeFigurePositionY(value * 10.0 / 100.0 - 5.0);
}


void MainWindow::on_fzSlider_valueChanged(int value)
{
    glwidget->changeFigurePositionZ(value * 10.0 / 100.0 - 5.0);
}
//масштабирование
void MainWindow::on_sxSlider_valueChanged(int value)
{
    glwidget->changeFigureScaleX(value / 50.0);
}

void MainWindow::on_sySlider_valueChanged(int value)
{
    glwidget->changeFigureScaleY(value / 50.0);
}

void MainWindow::on_szSlider_valueChanged(int value)
{
    glwidget->changeFigureScaleZ(value / 50.0);
}
//освещенность
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    glwidget->changeBrightness(value / 100.0);
}


//вращение перемещением мыши

void MainWindow::mousePressEvent(QMouseEvent *e) {

    if(e->x()<235||e->x()>815)
        return;
    if(e->y()<5||e->y()>500)
        return;

    //qDebug()<<"click"<<e->x();
    //qDebug()<<"click"<<e->y();
    x0 = (float) e->x();
    y0 = (float) e->y();
    glwidget->timer.stop();

}

void MainWindow::mouseReleaseEvent(QMouseEvent *e) {
   /* glwidget->timer.start(60);
    glwidget->updateGL();*/
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    if(e->x()<235||e->x()>815)
        return;
    if(e->y()<5||e->y()>500)
        return;

    if (e->buttons() & Qt::LeftButton) {
        glwidget->camera_rotate((e->x()-x0)/1000.0, 0,0);
        glwidget->camera_rotate(0, (e->y()-y0)/1000.0, 0);
    }
    if (e->buttons() & Qt::RightButton) {

            glwidget->camera_rotate(0, 0, (e->x()-x0)/1000.0);
            glwidget->camera_rotate(0, (e->y()-y0)/1000.0, 0);

    }




    /*if(e->y()-y0>0)
        glwidget->camera_rotate(0, 0.2);
    if(e->y()-y0<0)
        glwidget->camera_rotate(0, -0.2);*/
    //glwidget->camera_rotate();
    //x0 = (float) e->x();
    //y0 = (float) e->y();
   // yz = (float) e->z();
}
