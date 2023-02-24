#include "canvas.h"
#include <stdio.h>
#include <iostream>
#include <qopengltexture.h>
using namespace std;

const GLchar *verticesShaderSource = R"(
#version 120
varying   vec2 vTexcoord;

attribute vec3 position;
attribute vec2 aTexcoord;

void main(){
    vTexcoord = aTexcoord;
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
)";

const GLchar *fragmentShaderSource = R"(
#version 120
varying vec2 vTexcoord;
uniform sampler2D uTexture;
void main(){
    //gl_FragColor=vec4(1.0,1.0,0.0,1.0);
    gl_FragColor=texture2D(uTexture, vTexcoord);
}
)";

Canvas::Canvas(QWidget *parent)
    : QOpenGLWidget(parent)
{
}
void Canvas::initVao()
{
  glGenVertexArrays(1, &this->_vao);
  // 纹理
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  QOpenGLTexture img(QImage(":wall.jpeg").mirrored());
  int w = img.width();
  int h = img.height();

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width(), img.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &img);
  glGenerateMipmap(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  // 顶点
  GLfloat vertices[] = {
      -0.5f,
      -0.5f,
      0.0f,
      0.0f, 0.0f, // 左下角

      0.5f,
      -0.5f,
      0.0f,
      1.0f, 0.0f, // 右下角

      0.0f,
      0.5f,
      0.0f,
      0.5f, 1.0f // 上中
  };
  glBindVertexArray(this->_vao);
  {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    {
      // sizeof(vertices) = 36
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      {

        GLint position = glGetAttribLocation(this->_program, "position");
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
      }
      {
        GLint aTexcoord = glGetAttribLocation(this->_program, "aTexcoord");
        glEnableVertexAttribArray(aTexcoord);
        glVertexAttribPointer(aTexcoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
      }
      {
        GLuint uTexture = glGetUniformLocation(this->_program, "uTexture");
        glUniform1i(uTexture, texture);
      }
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  glBindVertexArray(0);
}
void Canvas::initShader()
{
  // 准备shader
  GLuint vert = this->createShader(GL_VERTEX_SHADER, verticesShaderSource);
  GLuint frag = this->createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  GLuint program = glCreateProgram();
  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);
  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    GLchar infoLog[512];
    glGetProgramInfoLog(program, 512, nullptr, infoLog);
    std::cout << "error： program link failed: " << infoLog << std::endl;
  }
  this->_program = program;

  // link之后就不需要了
  glDeleteShader(vert);
  glDeleteShader(frag);
}
void Canvas::paintGL()
{
  glClearColor(1.0, 0, 0, 1.0);
  glUseProgram(this->_program);

  glBindVertexArray(this->_vao);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Canvas::initializeGL()
{

  this->initializeOpenGLFunctions();

  this->initShader();
  this->initVao();
}
GLuint Canvas::createShader(GLenum type, const GLchar *source)
{
  GLuint vertexShader = glCreateShader(type);
  glShaderSource(vertexShader, 1, &source, nullptr);
  glCompileShader(vertexShader);
  GLint success;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    GLchar infoLog[512];
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cout << "error： shader compilation failed: " << infoLog << source << std::endl;
  }
  return vertexShader;
}
