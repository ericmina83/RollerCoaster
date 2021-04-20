#ifndef __MYSHADER_H__
#define __MYSHADER_H__

#include <string>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class MyShader : QOpenGLFunctions
{
private:
    std::string vshpath;
    std::string fshpath;

public:
    MyShader(std::string _vshpath, std::string _fshpath);
    ~MyShader();

    QOpenGLShaderProgram *program;
};

#endif