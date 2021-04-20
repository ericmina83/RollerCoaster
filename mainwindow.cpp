#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myOpenGLWidget = new MyOpenGLWidget();

    setGeometry(100, 25, 1000, 768);

    ui->mainLayout->layout()->addWidget(myOpenGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
