#ifndef CANVAS_H
#define CANVAS_H

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <qopenglextrafunctions.h>
class Canvas : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent);
    void paintGL() override;
    void initializeGL() override;

private:
    GLuint createShader(GLenum type, const GLchar *source);
    void initVao();
    void initShader();
    GLuint _program;
    GLuint _vao;
};

#endif // CANVAS_H
