#include "mainwindow.h"
#include <qopenglwidget.h>
#include <QPushButton>
#include "canvas.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QOpenGLWidget *widget = new Canvas(this);
    this->resize(QSize(400, 400));

    widget->resize(QSize(300, 300));
}

MainWindow::~MainWindow()
{
}
