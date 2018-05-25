#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    float x0, y0, z0;
    Widget* glwidget;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent*);

private slots:


    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void mouseMoveEvent(QMouseEvent * e);

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
