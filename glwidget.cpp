/*

Author: Stoica Alexandru ( Al3xDev )
Contact al3xdev@gmail.com
License: GPL v2.0, see LICENSE file

*/

#include "glwidget.h"
GLWidget::GLWidget(QWidget *parent)
    :QGLWidget(parent),Camera_Pos(glm::vec3(0,5,0)),Camera_Dir(glm::vec3(1,-0.2,1)),yaw(90.0),pitch(0.0),
    delta_time(30),reset_last_point(true),sec_pitch(0.0),sec_yaw(90.0)
{
    ///Camera
    Camera_Dir=glm::normalize(Camera_Dir);
    Sec_Camera_Dir=Camera_Dir;
    Camera_Up=glm::vec3(0.0,1.0,0.0);
    ///KeyBoard
    keys[0]=false;
    keys[1]=false;
    keys[2]=false;
    keys[3]=false;
    ///EditPoint
    pointEdit.x=-1.0;
    pointEdit.z=-1.0;
    edit=false;
    connect(&timer,SIGNAL(timeout()),this,SLOT(Control()));
    timer.start(delta_time);

    _parent=parent;


    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::ClickFocus);
}
void GLWidget::initializeGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glewExperimental=GL_TRUE;
    if(glewInit()!=GLEW_OK)
    {
    std::cerr<<"glewInit()!= GLEW_OK\n";
    }
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    projection=glm::perspective(45.0f,float(this->width())/float(this->height()),0.1f,1000.0f);
    shader.Create();
    shader.LoadShaderFromFile("Terrain.vs",GL_VERTEX_SHADER);
    shader.LoadShaderFromFile("Terrain.fg",GL_FRAGMENT_SHADER);
    shader.Link();

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    projection=glm::perspective(45.0f,float(this->width())/float(this->height()),0.1f,1000.0f);
}

void GLWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    view=glm::lookAt(Camera_Pos,Camera_Pos+Camera_Dir,Camera_Up);
    shader.Use();
    shader.SetMatrix4("p",projection);
    shader.SetMatrix4("v",view);
    shader.SetFloat("x",float(pointEdit.x));
    shader.SetFloat("z",float(pointEdit.z));
    shader.SetFloat("ray",terrain.ray);
    terrain.Draw();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        edit=true;
    }

}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        edit=false;
    }
    else
        if(event->button() == Qt::RightButton)
        {
            QPoint WinPos=_parent->pos();
            WinPos.setX(width()/2+WinPos.x());
            WinPos.setY(height()/2+WinPos.y());
            QCursor cursor;
            cursor.setPos(WinPos);
            setCursor(cursor);
            Sec_Camera_Dir=Camera_Dir;
        }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!reset_last_point)
    {
        GLfloat xoffset = event->x()-last_pos.x();
        GLfloat yoffset = last_pos.y()-event->y();
        if(event->buttons()== Qt::RightButton )
        {
            xoffset*=0.3;
            yoffset*=0.3;

            yaw+=xoffset;
            pitch+=yoffset;
            if(pitch > 89.0f)
                pitch = 89.0f;
            if(pitch < -89.0f)
                pitch = -89.0f;

            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            Camera_Dir = glm::normalize(front);
            sec_pitch=pitch;
            sec_yaw=yaw;
            Sec_Camera_Dir=Camera_Dir;
        }
        else
        {
            xoffset*=float(180)/std::min(width(),height())*0.3;
            yoffset*=float(180)/std::min(width(),height())*0.3;
            sec_yaw+=xoffset;
            sec_pitch+=yoffset;
            if(sec_pitch > 89.0f)
                sec_pitch = 89.0f;
            if(sec_pitch < -89.0f)
                sec_pitch = -89.0f;
            glm::vec3 front;
            front.x = cos(glm::radians(sec_yaw)) * cos(glm::radians(sec_pitch));
            front.y = sin(glm::radians(sec_pitch));
            front.z = sin(glm::radians(sec_yaw)) * cos(glm::radians(sec_pitch));
            Sec_Camera_Dir = glm::normalize(front);

        }
        last_pos=event->pos();
    }
    else
    {
        last_pos=event->pos();
        reset_last_point=false;
        Sec_Camera_Dir=Camera_Dir;
    }
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_W)
            keys[0]=true;
    if (e->key() == Qt::Key_S)
            keys[1]=true;
    if (e->key() == Qt::Key_A)
            keys[2]=true;
    if (e->key() == Qt::Key_D)
            keys[3]=true;
}
void GLWidget::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_W)
            keys[0]=false;
    if (e->key() == Qt::Key_S)
            keys[1]=false;
    if (e->key() == Qt::Key_A)
            keys[2]=false;
    if (e->key() == Qt::Key_D)
            keys[3]=false;
}

void GLWidget::Control()
{
    if(terrain.alive)
    {
        if(!this->underMouse())
        {
            reset_last_point=true;
            std::cerr<<" !underMouse() \n";
        }

        if (keys[0])
                Camera_Pos+=Camera_Dir;
        if (keys[1])
                Camera_Pos-=Camera_Dir;
        if (keys[2])
                Camera_Pos-=glm::normalize(glm::cross(Camera_Dir, Camera_Up));
        if (keys[3])
                Camera_Pos+=glm::normalize(glm::cross(Camera_Dir, Camera_Up));
        std::cerr<<edit<<"\n";
        pointEdit = terrain.Tracing(Camera_Pos,Sec_Camera_Dir,edit);

        updateGL();
    }
}
