/*

Author: Stoica Alexandru ( Al3xDev )
Contact al3xdev@gmail.com
License: GPL v2.0, see LICENSE file

*/
#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GLEW_STATIC
    #include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <SOIL/SOIL.h>
#include "Terrain.h"
#include "Shader.h"
#include <QGLWidget>
#include <QWidget>
#include <QMouseEvent>
#include <QGLFormat>
#include <QTimer>
#include <QCursor>

class GLWidget : public QGLWidget
{
Q_OBJECT
public slots:
    void Control();
public:
    GLWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    QWidget *_parent;
    QTimer timer;
    uint16_t delta_time;
    Shader shader;
    Terrain terrain;
    PointEdit pointEdit;
    glm::vec3 Camera_Pos;
    glm::vec3 Camera_Dir;
    glm::vec3 Sec_Camera_Dir;
    glm::vec3 Camera_Up;
    glm::mat4 projection;
    glm::mat4 view;
    QPoint last_pos;
    bool reset_last_point;
    GLfloat yaw;
    GLfloat pitch;
    GLfloat sec_yaw;
    GLfloat sec_pitch;
    bool keys[4];
    bool edit;

};
#endif // GLWIDGET_H
