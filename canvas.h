#ifndef CANVAS_H
#define CANVAS_H

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <qopenglwidget.h>
#include <qopenglfunctions.h>
class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent);
    void paintGL() override;
    void initializeGL() override;

private:
    GLuint createShader(GLenum type, const GLchar *source);
    GLuint _program;
    GLuint _vao;
};

#endif // CANVAS_H
