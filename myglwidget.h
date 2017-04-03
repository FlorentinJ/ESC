#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <GL/glu.h>
#include <qmath.h>

#define SIZE        800//2000//500
#define W           0.5
#define NB_P        90//360//37
#define NB_O        90//180//30
#define STEP_P      360/NB_P
#define STEP_O      90/NB_O
#define PI          3.141592653589793
#define NB_QUAD     6
#define NB_PLATE    3

class myGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit myGLWidget(int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;
    virtual void keyPressEvent( QKeyEvent *keyEvent );
    QTimer *t_Timer;


public slots:
    virtual void timeOutSlot();

};


#endif // MYGLWIDGET_H
