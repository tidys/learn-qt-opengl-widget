#ifndef CANVAS_H
#define CANVAS_H

#include <qopenglwidget.h>
#include <qopenglfunctions.h>
class Canvas:public QOpenGLWidget,protected QOpenGLFunctions
{
public:
    Canvas(QWidget* parent);
    void paintGL() override;
    void initializeGL() override;
};

#endif // CANVAS_H
