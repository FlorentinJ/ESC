#ifndef MYWINDOW_H
#define MYWINDOW_H


#include "myGLWidget.h"


class myWindow : public myGLWidget
{
    Q_OBJECT
public:
    explicit myWindow(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    int ntheta;
    int nphi;
    float Surf[NB_O*NB_P];
    float pts[3*4*NB_QUAD];

public slots:
    void calcSection();
    void integrate();

};

#endif // MYWINDOW_H
