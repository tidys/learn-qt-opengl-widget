#include "mainwindow.h"
#include <qopenglwidget.h>
#include <QPushButton>
#include "canvas.h"
#include "qevent.h"
#include "qmimedata.h"
#include "qdebug.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setAcceptDrops(true);
    QOpenGLWidget *widget = new Canvas(this);
    widget->resize(QSize(300, 300));
    this->resize(QSize(400, 400));
}

MainWindow::~MainWindow()
{
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* e)
{
    foreach(const QUrl & url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        qDebug() << "Dropped file:" << fileName;
    }
}
