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
    ui->pushButton->setStyleSheet("border-image: url(:/fire.png) stretch;");

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


void MainWindow::on_pushButton_clicked(){
    glwidget->add_new_firework();
}

//вращение перемещением мыши

void MainWindow::mousePressEvent(QMouseEvent *e) {

    if(e->x()<235||e->x()>815)
        return;
    if(e->y()<5||e->y()>500)
        return;
    x0 = (float) e->x();
    y0 = (float) e->y();
    glwidget->timer.stop();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e) {
     glwidget->timer.start(60);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    if(e->x()<235||e->x()>815)
        return;
    if(e->y()<5||e->y()>500)
        return;

    if (e->buttons() & Qt::LeftButton) {
        glwidget->camera_rotate((e->y()-y0)/100.0, 0,0);
        glwidget->camera_rotate(0, (e->x()-x0)/100.0, 0);
    }
    if (e->buttons() & Qt::RightButton) {

        glwidget->camera_rotate(0, 0, (e->y()-y0)/100.0);
        glwidget->camera_rotate(0, (e->x()-x0)/100.0, 0);
    }

}


