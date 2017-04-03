#include "myWindow.h"
#include <QDebug>

myWindow::myWindow(QWidget *parent)
    : myGLWidget(1000, parent,(char *)"Equivalent Section Calculator")//10000
{
    //17x55x66

    float init[] = {-0.085,-0.275,0,
                  -0.085,0.275,0,
                   0.085,0.275,0,
                   0.085,-0.275,0,


                  -0.085, 0.275,0,
                  -0.02,  0.40,0,
                   0.02,  0.40,0,
                   0.085, 0.275,0,

                  -0.1+0,-0.275,0.32,
                  -0.1+0,0.32,0.32,
                   0.1+0,0.32,0.32,
                   0.1+0,-0.275,0.32,

                  -0.1+0, 0.32,0.32,
                  -0.02+0,  0.47,0.32,
                   0.02+0,  0.47,0.32,
                   0.1+0, 0.32,0.32,

                  -0.085+0,-0.275,0.64,
                  -0.085+0,0.275,0.64,
                   0.085+0,0.275,0.64,
                   0.085+0,-0.275,0.64,

                  -0.085+0, 0.275,0.64,
                  -0.02+0,  0.40,0.64,
                   0.02+0,  0.40,0.64,
                   0.085+0, 0.275,0.64,
                   };

    /*float init[] = {-0.085,-0.275,0,
                      -0.085,0.275,0,
                       0.085,0.275,0,
                       0.085,-0.275,0,


                      -0.085, 0.275,0,
                      -0.02,  0.40,0,
                       0.02,  0.40,0,
                       0.085, 0.275,0,

                      -0.1+0.25,-0.275,0.3,
                      -0.1+0.25,0.32,0.3,
                       0.1+0.25,0.32,0.3,
                       0.1+0.25,-0.275,0.3,

                      -0.1+0.25, 0.32,0.3,
                      -0.02+0.25,  0.47,0.3,
                       0.02+0.25,  0.47,0.3,
                       0.1+0.25, 0.32,0.3,
                       };
*/
    for(int i=0; i<4*3*NB_QUAD; i++)
        pts[i] = init[i];

    connect(t_Timer,SIGNAL(timeout()),this,SLOT(calcSection()));

    ntheta = 1;
    nphi = 0;
}
void myWindow::calcSection()
{
    float res;
    glLoadIdentity();
    glRotatef(ntheta*STEP_O,1,0,0);
    glRotatef(nphi*STEP_P,0,0,1);

    updateGL();
    GLubyte *data = new GLubyte[3*SIZE*SIZE];
    glReadPixels(0,0,SIZE,SIZE,GL_RGB,GL_UNSIGNED_BYTE,data);
    int c = 0;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j< SIZE; j++)
        {
            if(data[(i+SIZE*j)*3+1]>=50*NB_PLATE-1)
            {
                c++;
            }
        }
    }
    delete[] data;
    res = 1.0*c/(SIZE*SIZE)*4*W*W;

    Surf[nphi+NB_P*ntheta] = res;
    nphi++;
    if(nphi >= NB_P)
    {
        nphi -=NB_P;
        ntheta +=1;
    }
    if(ntheta>=NB_O)
    {
        integrate();
        ntheta = 0;
    }
}

void myWindow::integrate()
{
    //-------------------------------------------------------------------
    qDebug()<<"Pas de Phi : "<<STEP_P<<"°";
    qDebug()<<"Pas de Theta : "<<STEP_O<<"°";

    float res = 0;
    for(int i = 0; i < NB_P; i++)
    {
        for(int j = 0; j< NB_O; j++)
        {
            res+=Surf[i+NB_P*j]*qSin(j*STEP_O*PI/180)*STEP_P*PI/180*STEP_O*PI/180;
        }
    }

    res/=PI;
    qDebug()<<"Surface effective : "<<res<<"m²";
    qDebug()<<"Nombre moyen de detections en 100s : "<<res*10000/60*100;
    //-------------------------------------------------------------------


    this->close();
}

void myWindow::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,  GL_ONE);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void myWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-W,W,-W,W,-10,10);
    glTranslatef(0.0,0.0, -5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3ub(0,50,0);

    glBegin(GL_QUADS);
        for(int i=0;i<4*NB_QUAD;i++)
        {
            glVertex3f(pts[3*i], pts[3*i+1], pts[3*i+2]);
        }
    glEnd();
}









