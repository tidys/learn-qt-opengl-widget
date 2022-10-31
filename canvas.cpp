#include "canvas.h"

Canvas::Canvas(QWidget* parent)
    :QOpenGLWidget(parent)
{

}
void Canvas::paintGL()
{

}
void Canvas::initializeGL()
{
    this->initializeOpenGLFunctions();
    glClearColor(1.0,0,0,1.0);
}
