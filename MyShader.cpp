#include "MyShader.h"

MyShader::MyShader(std::string _vshpath, std::string _fshpath)
{
    vshpath = _vshpath;
    fshpath = _fshpath;

    initializeOpenGLFunctions();

    program = new QOpenGLShaderProgram();

    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, vshpath.c_str()))
    {
        qDebug() << "Vertex Shader Error " << program->log();
    }

    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, fshpath.c_str()))
    {
        qDebug() << "Fragment Shader Error " << program->log();
    }

    if (!program->link())
    {
        qDebug() << "link Error " << program->log();
    }

    if (!program->bind())
    {
        qDebug() << "bind Error " << program->log();
    }
}

MyShader::~MyShader()
{
}