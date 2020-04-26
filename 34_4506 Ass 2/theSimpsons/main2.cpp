//
//  main.cpp
//  theSimpsons
//
//  Created by Amr Ali on 1711//17.
//  Copyright © 2017 Amr Ali. All rights reserved.
//

#include <iostream>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include "TextureBuilder.h"
//#include "Windows.h"



#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
#define PI 3.14159
#define SPACEBAR 32

//Animation Flags
bool startAnim = false;
bool topViewFlag = false;
bool rotateRoom = true;
double theta1  =0;
// Minion 1
float Minion1x;
float Minion1y;
float Minion1z;
float Minion1RotationX;
float Minion1RotationY;
float Minion1RotationZ;
float Minion1RightArmX;
float Minion1RightArmY;
float Minion1RightArmZ;
float Minion1LeftArmX, Minion1LefttArmY, Minion1LeftArmZ;
float Minion1Scalex, Minion1ScaleY, Minion1ScaleZ=1.0f;
// Minion 1 Animation flags
bool minion1Up =false;
bool minion1Anim=true;

//bool down;
//Minion 2
float Minion2x;
float Minion2y;
float Minion2z;
float Minion2RotationX;
float Minion2RotationY;
float Minion2RotationZ;
float Minion2RightArmX;
float Minion2RightArmY;
float Minion2RightArmZ;
float Minion2LeftArmX;
float Minion2LefttArmY;
float Minion2LeftArmZ;
// Animation Flags
bool minion2Anim=true;

//Minion 3
float Minion3x;
float Minion3y;
float Minion3z;
float Minion3RotationX;
float Minion3RotationY;
float Minion3RotationZ;
float Minion3Scale=1;
float Minion3RightArmX;
float Minion3RightArmY;
float Minion3RightArmZ;
float Minion3LeftArmX;
float Minion3LefttArmY;
float Minion3LeftArmZ;
// Minion 3 Animation flags
bool Minion3ScaleFlag=true;
bool minion3Anim=true;

//Minion 4
float Minion4x;
float Minion4y;
float Minion4z;
float Minion4RotationX;
float Minion4RotationY;
float Minion4RotationZ;
float Minion4RightArmX;
float Minion4RightArmY;
float Minion4RightArmZ;
float Minion4LeftArmX;
float Minion4LefttArmY;
float Minion4LeftArmZ;

// Minion 4 Animation flags
bool minion4Anim=true;
bool Minion4AnimBack = false;
bool minion4Up =false;
int Anim4=0;

//Minion 5
float Minion5x;
float Minion5y;
float Minion5z;
float Minion5RotationX;
float Minion5RotationY;
float Minion5RotationZ;
float Minion5RightArmX;
float Minion5RightArmY;
float Minion5RightArmZ;
float Minion5LeftArmX;
float Minion5LefttArmY;
float Minion5LeftArmZ;
float Minion5HeadRotation;
// Minion 5 Animation flags
bool minion5Anim=true;
bool Minion5Head = false;

//Minion 6
float Minion6x;
float Minion6y;
float Minion6z;
float Minion6RotationX;
float Minion6RotationY;
float Minion6RotationZ;
float Minion6RightArmX;
float Minion6RightArmY;
float Minion6RightArmZ;
float Minion6LeftArmX;
float Minion6LefttArmY;
float Minion6LeftArmZ;
// Minion 6 Animation flags
bool minion6Anim=true;
bool Minion6Arm=true;

// Beziar
float t=0;
float p1[2]={0,0};
float p2[2]={2,0.5};
float p3[2]={.5,2};
float p4[2]={0.5,3};

//=======================
//  Functions declaretion
//=======================
void DrawArc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments);

class Vector3f {
public:
    float x, y, z;
    
    Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
        x = _x;
        y = _y;
        z = _z;
    }
    
    Vector3f operator+(Vector3f &v) {
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }
    
    Vector3f operator-(Vector3f &v) {
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }
    
    Vector3f operator*(float n) {
        return Vector3f(x * n, y * n, z * n);
    }
    
    Vector3f operator/(float n) {
        return Vector3f(x / n, y / n, z / n);
    }
    
    Vector3f unit() {
        return *this / sqrt(x * x + y * y + z * z);
    }
    
    Vector3f cross(Vector3f v) {
        return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
};

class Camera {
public:
    Vector3f eye, center, up;
    
    Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
         center = Vector3f(centerX, centerY, centerZ);
        eye = Vector3f(eyeX, eyeY, eyeZ);
        up = Vector3f(upX, upY, upZ);
    }
    
    
    void moveX(float d) {
        Vector3f right = up.cross(center - eye).unit();
        Vector3f temp = right * d;
        eye = eye + temp;
        temp = 0;
        temp = right * d;
        center = center +temp;
        temp = 0;
    }
    
    void moveY(float d) {
        Vector3f temp = up.unit() * d;
        eye = eye + temp;
        temp = 0;
        temp = up.unit() * d;
        center = center + temp;
    }
    
    void moveZ(float d) {
        Vector3f view = (center - eye).unit();
        Vector3f temp = view * d;
        eye = eye + temp ;
        temp = 0;
        temp = view * d;
        center = center + temp ;
    }
    
    void rotateX(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = up.cross(view).unit();
        Vector3f temp1 = view * cos(DEG2RAD(a));
        Vector3f temp2 = up * sin(DEG2RAD(a));
        view = temp1 + temp2;
        up = view.cross(right);
        center = eye + view;
    }
    
    void rotateY(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = up.cross(view).unit();
        Vector3f temp1 = view * cos(DEG2RAD(a));
        Vector3f temp2 = right * sin(DEG2RAD(a));
        view = temp1 + temp2;
        right = view.cross(up);
        center = eye + view;
    }
    
    void look() {
        gluLookAt(
                  center.x, center.y, center.z,
                  eye.x, eye.y, eye.z,
                  up.x, up.y, up.z
                  );
    }
};


//Camera camera (2,0,2,2,0,2.5,0,1,0);
//Camera camera (0.5,0,0.5,0.5,0.5,2.5,0,1,0);
Camera camera(1.0f,-0.1f,1.0f,2.9f,0.5f,1.0f,0.0f,1.0f,0.0f);
//Camera topView(1.0f,5.0f,1.0f,1.0f,0.0f,1.0f,-1.0f,0.0f,0.0f);
Camera topView(1.0f,0.0f,1.0f,1,5.0f,1.0f,-1,0,0);
float cameraRy=0.0f;

//====================
//      The models
//====================

// The one with a single eye
void drawMinion1(void){
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    
    //Body
    glPushMatrix();
    glTranslated(0, 0, 0.5f);
    glTranslated(Minion1x, Minion1y, Minion1z);
    glRotated(45.0f, 0, 1, 0);
    glRotated(180.0f, 0, 1, 0);
    glRotated(Minion1RotationX, 1, 0, 0);
    glRotated(Minion1RotationY, 0, 1, 0);
    glRotated(Minion1RotationZ, 0, 0, 1);
    //    glScaled(Minion1Scalex, Minion1Scalex, Minion1Scalex);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.15f, 0.15f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right Arm
    glPushMatrix();
    //Handling Right Arm         ====== NOT FINISHED YET ======
    glRotated(10, 1, 0, 0);
    
    //Right shoulder
    glPushMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glutSolidSphere(0.015f, 100, 100); //fix the remaining arms
    glPopMatrix();
    
    //Right upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0.11f, -0.375, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //Left Arm
    glPushMatrix();
    //Handling Left Arm      ====== NOT FINISHED YET ======
    glRotated(-10, 1, 0, 0);
    
    //Left shoulder
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glutSolidSphere(0.015f, 100, 100);
    glPopMatrix();
    
    //Left upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //    //Left lower arm
    //    glPushMatrix();
    //    glColor3f(1, 1, 0);
    //    glTranslated(-0.02f, -0.08f-0.15f, 0.16f);
    //    glRotated(90, 1, 0, 0);
    //    gluCylinder(qobj, 0.015f, 0.015f, 0.15f, 100, 100);
    //    glPopMatrix();
    
    //Left hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(-0.09f, -0.375f, 0.11f);
    
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    
    //  Hair
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3d(0, 0, -0.03);
    glVertex3d(0, 0.2,-0.03);
    glVertex3d(0, 0, -0.02);
    glVertex3d(0, 0.2,-0.02);
    glVertex3d(0, 0, -0.01);
    glVertex3d(0, 0.2,-0.01);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0.2, 0);
    glVertex3d(0, 0, 0.01);
    glVertex3d(0, 0.2,0.01);
    glVertex3d(0, 0, 0.02);
    glVertex3d(0, 0.2,0.02);
    glVertex3d(0, 0, 0.03);
    glVertex3d(0, 0.2,0.03);
    glEnd();
    glPopMatrix();
    
    //Head
    glPushMatrix();
    glColor3f(1, 1, 0);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    
    // =======
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(-0.006f, 0.0f, -0.006f);
    glRotated(-90, 1, 0, 0);
    glutSolidTorus(0.01f, 0.15f, 100, 100);
    glPopMatrix();
    
    //eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.055f, 0.0f, 0.055f);
    gluSphere(qobj, 0.08f, 100, 100);
    
    //Eye ball
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.04f, 0.00f, 0.04f);
    gluSphere(qobj, 0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    
    // Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.1f, 0.01f, 0.1f);
    glRotated(45, 0, 1, 0);
    glutSolidTorus(0.01f, 0.055f, 100, 100);
    glPopMatrix();
    
    //mouth
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.0f, 0.4f, 0.55f);
    glScaled(0.5f, 0.5f, 0.5f);
    glRotated(55.0f, 1, 0, 0);
//    DrawArc(0.0f, 0.0f, 1.0f, 0.0f, 50.0f, 3);
    glPopMatrix();
    
    //bottom
    glPushMatrix();
    glColor3f(0,0 , 1);
    glTranslated(0.0f, -0.25f, 0.0f);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    
    //Right Leg
    glPushMatrix();
    //Handling Right leg
    //    glTranslated(-0.08f, 0, -0.005f);
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.08f, -0.3f, 0.005f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    
    //Right Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.08f, -0.45f, 0.005f);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    
    //Left Leg
    glPushMatrix();
    //Handling Left leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.005f, -0.3f, 0.105);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    
    //Left Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.005f, -0.45f, 0.105);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void drawMinion2(void){
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    
    //Body
    glPushMatrix();
//    glTranslated(0.5f, 0, 0.5f);
    glRotated(45.0f, 0, 1, 0);
    glTranslated(Minion2x, Minion2y, Minion2z);
    glRotated(Minion2RotationX, 1, 0, 0);
    glRotated(Minion2RotationY, 0, 1, 0);
    glRotated(Minion2RotationZ, 0, 0, 1);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.15f, 0.15f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right Arm
    glPushMatrix();
    //Handling Right Arm         ====== NOT FINISHED YET ======
    glRotated(10, 1, 0, 0);
    
    //Right shoulder
    glPushMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glutSolidSphere(0.015f, 100, 100); //fix the remaining arms
    glPopMatrix();
    
    //Right upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0.11f, -0.375, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //Left Arm
    glPushMatrix();
    //Handling Left Arm      ====== NOT FINISHED YET ======
    glRotated(-10, 1, 0, 0);
    
    //Left shoulder
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glutSolidSphere(0.015f, 100, 100);
    glPopMatrix();
    
    //Left upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //    //Left lower arm
    //    glPushMatrix();
    //    glColor3f(1, 1, 0);
    //    glTranslated(-0.02f, -0.08f-0.15f, 0.16f);
    //    glRotated(90, 1, 0, 0);
    //    gluCylinder(qobj, 0.015f, 0.015f, 0.15f, 100, 100);
    //    glPopMatrix();
    
    //Left hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(-0.09f, -0.375f, 0.11f);
    
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    
    
    //Head
    glPushMatrix();
    glColor3f(1, 1, 0);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    // Hair
    glPushMatrix();
    glBegin(GL_LINES);
//    glVertex3f(<#GLfloat x#>, <#GLfloat y#>, <#GLfloat z#>)
    glEnd();
    glPopMatrix();
    // ===== EYES ====
    //left eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.048f, 0.0f, 0.10f);
    gluSphere(qobj, 0.05f, 100, 100);
    glPopMatrix();
    //Right eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.10f, 0.0f, 0.048f);
    gluSphere(qobj, 0.05f, 100, 100);
    glPopMatrix();
    //Left Eye ball
    glPushMatrix();
//    glColor3f(0.52f, 0.3f, 0.02f);
    glColor3f(0, 0, 0);
    glTranslated(0.068f, 0.0f, 0.13f);
    gluSphere(qobj, 0.02f, 100, 100);
    glPopMatrix();
    //Right Eye ball
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0.13f, 0.0f, 0.068f);
    gluSphere(qobj, 0.02f, 100, 100);
    glPopMatrix();
    // left Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.06f, 0.005f, 0.13f);
    glRotated(30, 0, 1, 0);
    glutSolidTorus(0.01f, 0.044f, 100, 100);
    glPopMatrix();
    // Right Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.13f , 0.005f,0.06f);
    glRotated(65, 0, 1, 0);
    glutSolidTorus(0.01f, 0.044f, 100, 100);
    glPopMatrix();
    // ======= GOGGLES BELT
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(-0.009f, 0.0f, -0.009f);
    glRotated(-90, 1, 0, 0);
    glutSolidTorus(0.01f, 0.15f, 100, 100);
    glPopMatrix();
    // ==== END OF GOGGLES ====
    //mouth
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.0f, 0.4f, 0.55f);
    glScaled(0.5f, 0.5f, 0.5f);
    glRotated(55.0f, 1, 0, 0);
//    DrawArc(0.0f, 0.0f, 1.0f, 0.0f, 50.0f, 3);
    glPopMatrix();
    //bottom
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.0f, -0.25f, 0.0f);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    //Right Leg
    glPushMatrix();
    //Handling Right leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.08f, -0.3f, 0.005f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Right Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.08f, -0.45f, 0.005f);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    //Left Leg
    glPushMatrix();
    //Handling Left leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.005f, -0.3f, 0.105);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Left Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.005f, -0.45f, 0.105);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void drawMinion3(void){
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    
    //Body
    glPushMatrix();
    glTranslated(0, 0, -0.5);
    glTranslated(Minion3x, Minion3y, Minion3z);
    glRotated(45.0f, 0, 1, 0);
    glRotated(Minion3RotationX, 1, 0, 0);
    glRotated(Minion3RotationY, 0, 1, 0);
    glRotated(Minion3RotationZ, 0, 0, 1);
    glScaled(Minion3Scale, 1, Minion3Scale);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.15f, 0.15f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right Arm
    glPushMatrix();
    //Handling Right Arm         ====== NOT FINISHED YET ======
    glRotated(10, 1, 0, 0);
    
    //Right shoulder
    glPushMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glutSolidSphere(0.015f, 100, 100); //fix the remaining arms
    glPopMatrix();
    
    //Right upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0.11f, -0.375, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //Left Arm
    glPushMatrix();
    //Handling Left Arm      ====== NOT FINISHED YET ======
    glRotated(-10, 1, 0, 0);
    
    //Left shoulder
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glutSolidSphere(0.015f, 100, 100);
    glPopMatrix();
    
    //Left upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //    //Left lower arm
    //    glPushMatrix();
    //    glColor3f(1, 1, 0);
    //    glTranslated(-0.02f, -0.08f-0.15f, 0.16f);
    //    glRotated(90, 1, 0, 0);
    //    gluCylinder(qobj, 0.015f, 0.015f, 0.15f, 100, 100);
    //    glPopMatrix();
    
    //Left hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(-0.09f, -0.375f, 0.11f);
    
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    
    //Head
    glPushMatrix();
    glColor3f(1, 1, 0);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    // ===== EYES ====
    //left eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.048f, 0.0f, 0.10f);
    gluSphere(qobj, 0.05f, 100, 100);
    glPopMatrix();
    //Right eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.10f, 0.0f, 0.048f);
    gluSphere(qobj, 0.05f, 100, 100);
    glPopMatrix();
    //Left Eye ball
    glPushMatrix();
    glColor3f(0.44f, 0.52f, 0.99f);
    glTranslated(0.068f, 0.0f, 0.13f);
    gluSphere(qobj, 0.02f, 100, 100);
    glPopMatrix();
    //Right Eye ball
    glPushMatrix();
    glColor3f(0.296875f, 0.60546875f, 0.2890625f);
    glTranslated(0.13f, 0.0f, 0.068f);
    gluSphere(qobj, 0.02f, 100, 100);
    glPopMatrix();
    // left Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.06f, 0.005f, 0.13f);
    glRotated(30, 0, 1, 0);
    glutSolidTorus(0.01f, 0.044f, 100, 100);
    glPopMatrix();
    // Right Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.13f , 0.005f,0.06f);
    glRotated(65, 0, 1, 0);
    glutSolidTorus(0.01f, 0.044f, 100, 100);
    glPopMatrix();
    // ======= GOGGLES BELT
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(-0.009f, 0.0f, -0.009f);
    glRotated(-90, 1, 0, 0);
    glutSolidTorus(0.01f, 0.15f, 100, 100);
    glPopMatrix();
    // ==== END OF GOGGLES ====
    //mouth
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.0f, 0.4f, 0.55f);
    glScaled(0.5f, 0.5f, 0.5f);
    glRotated(55.0f, 1, 0, 0);
//    DrawArc(0.0f, 0.0f, 1.0f, 0.0f, 50.0f, 3);
    glPopMatrix();
    //bottom
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.0f, -0.25f, 0.0f);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    //Right Leg
    glPushMatrix();
    //Handling Right leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.08f, -0.3f, 0.005f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Right Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.08f, -0.45f, 0.005f);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    //Left Leg
    glPushMatrix();
    //Handling Left leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.005f, -0.3f, 0.105);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Left Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.005f, -0.45f, 0.105);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void drawMinion4(void){
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    
    //Body
    glPushMatrix();
    glTranslated(Minion4x-1.5, Minion4y, Minion4z-1.5);
    glTranslated(1, 0, 0.5f);
    glRotated(45.0f, 0, 1, 0);
    glRotated(Minion4RotationX, 1, 0, 0);
    glRotated(Minion4RotationY, 0, 1, 0);
    glRotated(Minion4RotationZ, 0, 0, 1);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.15f, 0.15f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right Arm
    glPushMatrix();
    //Handling Right Arm         ====== NOT FINISHED YET ======
    glRotated(10, 1, 0, 0);
    
    //Right shoulder
    glPushMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glutSolidSphere(0.015f, 100, 100); //fix the remaining arms
    glPopMatrix();
    
    //Right upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0.11f, -0.375, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //Left Arm
    glPushMatrix();
    //Handling Left Arm      ====== NOT FINISHED YET ======
    glRotated(-10, 1, 0, 0);
    glRotated(Minion4LeftArmX, 1, 0, 0);
    glRotated(Minion4LefttArmY, 0, 1, 0);
    glRotated(Minion4LeftArmZ, 0, 0, 1);
    //Left shoulder
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glutSolidSphere(0.015f, 100, 100);
    glPopMatrix();
    
    //Left upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //    //Left lower arm
    //    glPushMatrix();
    //    glColor3f(1, 1, 0);
    //    glTranslated(-0.02f, -0.08f-0.15f, 0.16f);
    //    glRotated(90, 1, 0, 0);
    //    gluCylinder(qobj, 0.015f, 0.015f, 0.15f, 100, 100);
    //    glPopMatrix();
    
    //Left hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(-0.09f, -0.375f, 0.11f);
    
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    
    //Head
    glPushMatrix();
    glColor3f(1, 1, 0);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    // ===== EYES ====
    //left eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.048f, 0.0f, 0.10f);
    gluSphere(qobj, 0.05f, 100, 100);
    glPopMatrix();
    //Right eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.10f, 0.0f, 0.048f);
    gluSphere(qobj, 0.05f, 100, 100);
    glPopMatrix();
    //Left Eye ball
    glPushMatrix();
    glColor3f(0.44f, 0.52f, 0.99f);
    glTranslated(0.068f, 0.0f, 0.13f);
    gluSphere(qobj, 0.02f, 100, 100);
    glPopMatrix();
    //Right Eye ball
    glPushMatrix();
    glColor3f(0.296875f, 0.60546875f, 0.2890625f);
    glTranslated(0.13f, 0.0f, 0.068f);
    gluSphere(qobj, 0.02f, 100, 100);
    glPopMatrix();
    // left Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.06f, 0.005f, 0.13f);
    glRotated(30, 0, 1, 0);
    glutSolidTorus(0.01f, 0.044f, 100, 100);
    glPopMatrix();
    // Right Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.13f , 0.005f,0.06f);
    glRotated(65, 0, 1, 0);
    glutSolidTorus(0.01f, 0.044f, 100, 100);
    glPopMatrix();
    // ======= GOGGLES BELT
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(-0.009f, 0.0f, -0.009f);
    glRotated(-90, 1, 0, 0);
    glutSolidTorus(0.01f, 0.15f, 100, 100);
    glPopMatrix();
    // ==== END OF GOGGLES ====
    //mouth
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.0f, 0.4f, 0.55f);
    glScaled(0.5f, 0.5f, 0.5f);
    glRotated(55.0f, 1, 0, 0);
//    DrawArc(0.0f, 0.0f, 1.0f, 0.0f, 50.0f, 3);
    glPopMatrix();
    //bottom
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.0f, -0.25f, 0.0f);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    //Right Leg
    glPushMatrix();
    //Handling Right leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.08f, -0.3f, 0.005f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Right Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.08f, -0.45f, 0.005f);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    //Left Leg
    glPushMatrix();
    //Handling Left leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.005f, -0.3f, 0.105);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Left Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.005f, -0.45f, 0.105);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void drawMinion5(void){
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    
    //Body
    glPushMatrix();
    glTranslated(Minion5x, Minion5y, Minion5z);
    glTranslated(1, 0, 0);
    glRotated(45.0f, 0, 1, 0);
    glRotated(Minion5RotationX, 1, 0, 0);
    //    glRotated(Minion5RotationY, 0, 1, 0);
    glRotated(Minion5RotationZ, 0, 0, 1);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.15f, 0.15f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right Arm
    glPushMatrix();
    //Handling Right Arm         ====== NOT FINISHED YET ======
    glRotated(10, 1, 0, 0);
    
    //Right shoulder
    glPushMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glutSolidSphere(0.015f, 100, 100); //fix the remaining arms
    glPopMatrix();
    
    //Right upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0.11f, -0.375, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //Left Arm
    glPushMatrix();
    //Handling Left Arm      ====== NOT FINISHED YET ======
    glRotated(-10, 1, 0, 0);
    
    //Left shoulder
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glutSolidSphere(0.015f, 100, 100);
    glPopMatrix();
    
    //Left upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //    //Left lower arm
    //    glPushMatrix();
    //    glColor3f(1, 1, 0);
    //    glTranslated(-0.02f, -0.08f-0.15f, 0.16f);
    //    glRotated(90, 1, 0, 0);
    //    gluCylinder(qobj, 0.015f, 0.015f, 0.15f, 100, 100);
    //    glPopMatrix();
    
    //Left hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(-0.09f, -0.375f, 0.11f);
    
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    
    //Head
    glPushMatrix();
    glRotated(Minion5HeadRotation, 0, 1, 0 );
    
    glPushMatrix();
    glBegin(GL_LINES);
//    glVertex3d(0, 0, -0.03);
//    glVertex3d(0, 0.2,-0.03);
//    glVertex3d(0, 0, -0.02);
//    glVertex3d(0, 0.2,-0.02);
//    glVertex3d(0, 0, -0.01);
//    glVertex3d(0, 0.2,-0.01);
    
    glVertex3d(0, 0.14, 0);
    glVertex3d(0, 0.17, 0.1);
    glVertex3d(0.01, 0.14, 0);
    glVertex3d(0.01, 0.17,0.1);
    glVertex3d(0.02, 0.14, 0);
    glVertex3d(0.02, 0.17,0.1);
    glVertex3d(0.03, 0.14, 0);
    glVertex3d(0.03, 0.17,0.1);
    glVertex3d(0.04, 0.14, 0);
    glVertex3d(0.04, 0.17,0.1);
    glVertex3d(0.05, 0.14, 0);
    glVertex3d(0.05, 0.17,0.1);
    glVertex3d(0.06, 0.14, 0);
    glVertex3d(0.06, 0.17,0.1);
    glVertex3d(0.07, 0.14, 0);
    glVertex3d(0.07, 0.17,0.1);
    
    glVertex3d(0, 0.14, 0);
    glVertex3d(0, 0.17, -0.1);
    glVertex3d(0.01, 0.14, 0);
    glVertex3d(0.01, 0.17,-0.1);
    glVertex3d(0.02, 0.14, 0);
    glVertex3d(0.02, 0.17,-0.1);
    glVertex3d(0.03, 0.14, 0);
    glVertex3d(0.03, 0.17,-0.1);
    glVertex3d(0.04, 0.14, 0);
    glVertex3d(0.04, 0.17,-0.1);
    glVertex3d(0.05, 0.14, 0);
    glVertex3d(0.05, 0.17,-0.1);
    glVertex3d(0.06, 0.14, 0);
    glVertex3d(0.06, 0.17,-0.1);
    glVertex3d(0.07, 0.14, 0);
    glVertex3d(0.07, 0.17,-0.1);
    glEnd();
    
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    // =======
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(-0.006f, 0.0f, -0.006f);
    glRotated(-90, 1, 0, 0);
    glutSolidTorus(0.01f, 0.15f, 100, 100);
    glPopMatrix();
    //eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.055f, 0.0f, 0.055f);
    gluSphere(qobj, 0.08f, 100, 100);
    //Eye ball
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.04f, 0.00f, 0.04f);
    gluSphere(qobj, 0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    // Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.1f, 0.01f, 0.1f);
    glRotated(45, 0, 1, 0);
    glutSolidTorus(0.01f, 0.055f, 100, 100);
    glPopMatrix();
    //mouth
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.0f, 0.4f, 0.55f);
    glScaled(0.5f, 0.5f, 0.5f);
    glRotated(55.0f, 1, 0, 0);
//    DrawArc(0.0f, 0.0f, 1.0f, 0.0f, 50.0f, 3);
    glPopMatrix();
    glPopMatrix();
    
    //bottom
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.0f, -0.25f, 0.0f);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    //Right Leg
    glPushMatrix();
    //Handling Right leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.08f, -0.3f, 0.005f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Right Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.08f, -0.45f, 0.005f);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    //Left Leg
    glPushMatrix();
    //Handling Left leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.005f, -0.3f, 0.105);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Left Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.005f, -0.45f, 0.105);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void drawMinion6(void){
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    
    //Body
    glPushMatrix();
    glTranslated(1, 0, -0.5);
    glTranslated(Minion6x, Minion6y, Minion6z);
    glRotated(45.0f, 0, 1, 0);
    glRotated(Minion6RotationX, 1, 0, 0);
    //    glRotated(Minion6RotationY, 0, 1, 0);
    glRotated(Minion6RotationZ, 0, 0, 1);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.15f, 0.15f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right Arm
    glPushMatrix();
    //Handling Right Arm         ====== NOT FINISHED YET ======
    glRotated(10, 1, 0, 0);
    
    //Right shoulder
    glPushMatrix();
    glTranslated(0.11f, -0.125f, -0.08f);
    glRotated(Minion6RightArmZ, 0, 0, 1);
    glTranslated(-0.11f, +0.125f, +0.08f);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glutSolidSphere(0.015f, 100, 100); //fix the remaining arms
    glPopMatrix();
    
    //Right upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0.11f, -0.125f, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //Right hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0.11f, -0.375, -0.08f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //Left Arm
    glPushMatrix();
    //Handling Left Arm      ====== NOT FINISHED YET ======
    glRotated(-10, 1, 0, 0);
    
    //Left shoulder
    glPushMatrix();
    glTranslated(-0.09f, -0.125f, 0.11f);
    glRotated(Minion6LeftArmZ, 0, 0, 1);
    glTranslated(0.09f, 0.125f, -0.11f);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glutSolidSphere(0.015f, 100, 100);
    glPopMatrix();
    
    //Left upper arm
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-0.09f, -0.125f, 0.11f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.25f, 100, 100);
    glPopMatrix();
    
    //    //Left lower arm
    //    glPushMatrix();
    //    glColor3f(1, 1, 0);
    //    glTranslated(-0.02f, -0.08f-0.15f, 0.16f);
    //    glRotated(90, 1, 0, 0);
    //    gluCylinder(qobj, 0.015f, 0.015f, 0.15f, 100, 100);
    //    glPopMatrix();
    
    //Left hand
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(-0.09f, -0.375f, 0.11f);
    
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.014f, 0.02f, 0.05f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //  Hair
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3d(0, 0, -0.03);
    glVertex3d(0, 0.2,-0.03);
    glVertex3d(0, 0, -0.02);
    glVertex3d(0, 0.2,-0.02);
    glVertex3d(0, 0, -0.01);
    glVertex3d(0, 0.2,-0.01);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0.2, 0);
    glVertex3d(0, 0, 0.01);
    glVertex3d(0, 0.2,0.01);
    glVertex3d(0, 0, 0.02);
    glVertex3d(0, 0.2,0.02);
    glVertex3d(0, 0, 0.03);
    glVertex3d(0, 0.2,0.03);
    glEnd();
    glPopMatrix();
    
    //Head
    glPushMatrix();
    glColor3f(1, 1, 0);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    // ===== EYES ====
    //left eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.048f, 0.0f, 0.10f);
    gluSphere(qobj, 0.05f, 100, 100);
    glPopMatrix();
    //Right eye
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.10f, 0.0f, 0.048f);
    gluSphere(qobj, 0.05f, 100, 100);
    glPopMatrix();
    //Left Eye ball
    glPushMatrix();
    glColor3f(0.52f, 0.3f, 0.02f);
    glTranslated(0.068f, 0.0f, 0.13f);
    gluSphere(qobj, 0.02f, 100, 100);
    glPopMatrix();
    //Right Eye ball
    glPushMatrix();
    glColor3f(0.52f, 0.3f, 0.02f);
    glTranslated(0.13f, 0.0f, 0.068f);
    gluSphere(qobj, 0.02f, 100, 100);
    glPopMatrix();
    // left Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.06f, 0.005f, 0.13f);
    glRotated(30, 0, 1, 0);
    glutSolidTorus(0.01f, 0.044f, 100, 100);
    glPopMatrix();
    // Right Goggle
    glPushMatrix();
    glColor3f(0.5,0.5, 0.5);
    glTranslated(0.13f , 0.005f,0.06f);
    glRotated(65, 0, 1, 0);
    glutSolidTorus(0.01f, 0.044f, 100, 100);
    glPopMatrix();
    // ======= GOGGLES BELT
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(-0.009f, 0.0f, -0.009f);
    glRotated(-90, 1, 0, 0);
    glutSolidTorus(0.01f, 0.15f, 100, 100);
    glPopMatrix();
    // ==== END OF GOGGLES ====
    //mouth
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.0f, 0.4f, 0.55f);
    glScaled(0.5f, 0.5f, 0.5f);
    glRotated(55.0f, 1, 0, 0);
//    DrawArc(0.0f, 0.0f, 1.0f, 0.0f, 50.0f, 3);
    glPopMatrix();
    //bottom
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.0f, -0.25f, 0.0f);
    gluSphere(qobj, 0.15f, 100, 100);
    glPopMatrix();
    //Right Leg
    glPushMatrix();
    //Handling Right leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.08f, -0.3f, 0.005f);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Right Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.08f, -0.45f, 0.005f);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    //Left Leg
    glPushMatrix();
    //Handling Left leg
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslated(0.005f, -0.3f, 0.105);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 0.015f, 0.015f, 0.18f, 100, 100);
    glPopMatrix();
    //Left Shoe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslated(0.005f, -0.45f, 0.105);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}


void drawWall(double thickness) {
    glPushMatrix();
    glTranslated(0.5, 0.5 * thickness, 0.5);
    glScaled(1.0, thickness, 1.0);
    glutSolidCube(2);
    glPopMatrix();
}
void drawTableLeg(double thick, double len) {
    glPushMatrix();
    glTranslated(0, len / 2, 0);
    glScaled(thick, len, thick);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawJackPart() {
    glPushMatrix();
    glScaled(0.2, 0.2, 1.0);
    glutSolidSphere(1, 15, 15);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, 0, 1.2);
    glutSolidSphere(0.2, 15, 15);
    glTranslated(0, 0, -2.4);
    glutSolidSphere(0.2, 15, 15);
    glPopMatrix();
}
void drawJack() {
    glPushMatrix();
    drawJackPart();
    glRotated(90.0, 0, 1, 0);
    drawJackPart();
    glRotated(90.0, 1, 0, 0);
    drawJackPart();
    glPopMatrix();
}
void drawTable(double topWid, double topThick, double legThick, double legLen){
    glPushMatrix();
    glTranslated(0, legLen, 0);
    glScaled(topWid, topThick, topWid);
    glutSolidCube(1.0);
    glPopMatrix();
    
    double dist = 0.95*topWid / 2.0 - legThick / 2.0;
    glPushMatrix();
    glTranslated(dist, 0, dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(-2 * dist, 0, 2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    glPopMatrix();
}

void DrawArc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments)
{
    float theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
    
    float tangetial_factor = tanf(theta);
    
    float radial_factor = cosf(theta);
    
    
    float x = r * cosf(start_angle);//we now start at the start angle
    float y = r * sinf(start_angle);
    
    glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
    for(int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy);
        
        float tx = -y;
        float ty = x;
        
        x += tx * tangetial_factor;
        y += ty * tangetial_factor;
        
        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}
float* bezier(float t, float* p0,float* p1,float* p2,float* p3)
{
    float res[2];
    res[0]=pow((1-t),3)*p0[0]+3*t*pow((1-t),2)*p1[0]+3*pow(t,2)*(1-t)*p2[0]+pow(t,3)*p3[0];
    res[1]=pow((1-t),3)*p0[1]+3*t*pow((1-t),2)*p1[1]+3*pow(t,2)*(1-t)*p2[1]+pow(t,3)*p3[1];
    return res;
}

void setupLights() {
    GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
    GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
    GLfloat shininess[] = { 50 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glShadeModel(GL_SMOOTH);
    
    GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
    GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 640 / 480, 0.001, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if(topViewFlag){
        topView.look();
    }else{
        camera.look();
    }
}

void fakeAxes(void){
    //Fake axes
    glPushMatrix();
    glPushMatrix();
    // X axis The red line
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0, 0);
    glVertex3f(20.0f, 0, 0);
    glEnd();
    // Y axis The Green one
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 20, 0);
    glEnd();
    // Z axis The yellow one
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 20);
    glEnd();
    glPopMatrix();
    glPopMatrix();
    
}

void drawScene(void){
    // ========== The room =========
    //Ground
    glPushMatrix();
    glScaled(2.0f, 1.0, 2.0f);
    glPushMatrix();
    glColor3f(1, 0.5, 0.5 );
    glTranslated(0.0f, -0.5f, 0.0f);
    drawWall(0.02);
    glPopMatrix();
    
    // Z axis SIDE VIEW LEFT
    glPushMatrix();
    glColor3f(0.5, 1, 0.5 );
    glTranslated(-0.5f, 0, 0);
    glRotated(90, 0, 0, 1.0);
    drawWall(0.02);
    glPopMatrix();
    
    // Z axis SIDE VIEW RIGHT
    glPushMatrix();
    glColor3f(1, 0.5, 1 );
    glTranslated(1.50f, 0, 0);
    glRotated(90, 0, 0, 1.0);
    drawWall(0.02);
    glPopMatrix();
    
    // X axis FRONT VIEW rear
    glPushMatrix();
    glTranslated(0, 0, -0.5);
    glRotated(-90, 1.0, 0.0, 0.0);
    drawWall(0.02);
    glPopMatrix();
    
    // X axis FRONT VIEW
    glPushMatrix();
    glTranslated(0, 0, 1.5);
    glRotated(-90, 1.0, 0.0, 0.0);
    drawWall(0.02);
    glPopMatrix();
    glPopMatrix();
}
void Display() {
    setupCamera();
    setupLights();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawScene();
//    fakeAxes();
    
    //Rotating the camera
    if(rotateRoom){
        glPushMatrix();
        camera.rotateY(3);
        glPopMatrix();
        
    }
    
    // ====== DRAWING THE MINIONS ========
    
    glPushMatrix();
    glTranslated(0.5, 0, 1);
    glScaled(0.4,0.4,0.4);
//    glRotated(45.0f, 0, 1, 0);
    drawMinion1();
    drawMinion2();
    drawMinion3();
    drawMinion4();
    drawMinion5();
    drawMinion6();
    glPopMatrix();
    
    glutSwapBuffers();
}



void Animation(void){

    if(startAnim){
        
        // Minion 1
        if(minion1Anim){
            if(Minion1RotationY<=180.0f&&Minion1RotationY>=0.0f){
                Minion1RotationY++;
                if(Minion1RotationY<=181.0f&&Minion1RotationY>=179.0){
                    minion1Up = true;
                }
            }
            
            if(Minion1y>=0.0f&&Minion1y<=0.2f &&minion1Up){
                Minion1y+=0.007f;
            }else{
                minion1Up=false;
                Minion1y-=0.007f;
                if(Minion1y<0.0f){
                    Minion1y=0.0f;
                    minion1Up=true;
                }
            }
        }
        
        //Minion 2
        if(minion2Anim){
            if(Minion2RotationY<=90.0f&&Minion2RotationY>=0.0f){
                
            }
            Minion2RotationY++;
        }
        
        //Minion 3
        if(minion3Anim){
            if(Minion3Scale>=1.0f&& Minion3Scale<2.0f &&Minion3ScaleFlag){
                Minion3Scale+=0.01f;
            }else{
                Minion3ScaleFlag = false;
                Minion3Scale-=0.01f;
                if(Minion3Scale<=1.0f){
                    Minion3ScaleFlag = 1.0f;
                    Minion3ScaleFlag = true;
                }
            }
        }
        
        //Minion 4
        if(minion4Anim){
            
            switch (Anim4) {
                case 0:
                    if(t<=0.9&&!Minion4AnimBack){
                        float* p = bezier(t, p1, p2, p3, p4);
                        Minion4x=p[0];
                        Minion4z=p[1];
                        t+=0.005;
                    }
                    else{
                        Minion4AnimBack = true;
                    }
                    if(Minion4AnimBack&&t>=0.0){
                        float* p = bezier(t, p1, p2, p3, p4);
                        Minion4x=p[0];
                        Minion4z=p[1];
                        t-=0.005;
                    }else if(t<=0.0){
                        Minion4AnimBack = false;
                    }
                    
                    if(Minion4y>=0.0f&&Minion4y<=0.2f &&minion4Up){
                        Minion4y+=0.05f;
                    }else{
                        minion4Up=false;
                        Minion4y-=0.05f;
                        if(Minion4y<0.0f){
                            Minion4y=0.0f;
                            minion4Up=true;
                        }
                    }if(t<=0.9&&!Minion4AnimBack){
                        float* p = bezier(t, p1, p2, p3, p4);
                        Minion4x=p[0];
                        Minion4z=p[1];
                        t+=0.005;
                    }
                    else{
                        Minion4AnimBack = true;
                    }
                    if(Minion4AnimBack&&t>=0.0){
                        float* p = bezier(t, p1, p2, p3, p4);
                        Minion4x=p[0];
                        Minion4z=p[1];
                        t-=0.005;
                    }else if(t<=0.0){
                        Minion4AnimBack = false;
                    }
                    
                    if(Minion4y>=0.0f&&Minion4y<=0.2f &&minion4Up){
                        Minion4y+=0.05f;
                    }else{
                        minion4Up=false;
                        Minion4y-=0.05f;
                        if(Minion4y<0.0f){
                            Minion4y=0.0f;
                            minion4Up=true;
                        }
                    }break;
                case 1:
                    if(Minion4y>=0.0f&&Minion4y<=0.2f &&minion4Up){
                        Minion4y+=0.05f;
                    }else{
                        minion4Up=false;
                        Minion4y-=0.05f;
                        if(Minion4y<0.0f){
                            Minion4y=0.0f;
                            minion4Up=true;
                        }
                    }
                    break;
                case 2:
                    if(t<=0.9&&!Minion4AnimBack){
                        float* p = bezier(t, p1, p2, p3, p4);
                        Minion4x=p[0];
                        Minion4z=p[1];
                        t+=0.005;
                    }
                    else{
                        Minion4AnimBack = true;
                    }
                    if(Minion4AnimBack&&t>=0.0){
                        float* p = bezier(t, p1, p2, p3, p4);
                        Minion4x=p[0];
                        Minion4z=p[1];
                        t-=0.005;
                    }else if(t<=0.0){
                        Minion4AnimBack = false;
                    }
                default:
                    break;
            }
           
            
            
            
//            if(Minion4LeftArmX>=-60.0f){
//                glPushMatrix();
//                Minion4LeftArmX-=5;
//                glTranslated(<#GLdouble x#>, <#GLdouble y#>, <#GLdouble z#>)
//                glRotated(Minion4LeftArmX, 1, 0, 0 );
//                glPopMatrix();
//
//            }

        }
        //Minion 5
        if(minion5Anim){
            if(Minion5HeadRotation<=45 && Minion5Head){
                Minion5HeadRotation+=10;
            }else{
                Minion5Head=false;
                Minion5HeadRotation-=10;
                if(Minion5HeadRotation<=-45){
//                    Minion1y=0.0f;
                    Minion5Head=true;
                }
            }
            
        }
        //Minion 6
        if(minion6Anim){
            if(Minion6RightArmZ<=60 && Minion6Arm){
                Minion6RightArmZ+=10;
                Minion6LeftArmZ-=10;
            }else{
                Minion6Arm=false;
                Minion6RightArmZ-=10;
                Minion6LeftArmZ+=10;
                if(Minion6RightArmZ<=0){
                    //                    Minion1y=0.0f;
                    Minion6Arm=true;
                }
            }
            
        }
        
                cameraRy++;
        
        
    }
    glutPostRedisplay();
}
void Timer(int value){
    
    glutTimerFunc(30, Timer, 0);
}

void Keyboard(unsigned char key, int x, int y) {
    float d = 0.01;
    
    switch (key) {
        case 'w':
            camera.moveY(d);
            break;
        case 's':
            camera.moveY(-d);
            break;
        case 'a':
            camera.moveX(d);
            break;
        case 'd':
            camera.moveX(-d);
            break;
        case 'q':
            camera.moveZ(d);
            break;
        case 'e':
            camera.moveZ(-d);
            break;
        case 'c':
            topViewFlag = true;
            //            topView.look();
            break;
        
        case 'v':
            topViewFlag = false;
            camera.look();
            break;
        case 'b':
            rotateRoom =!rotateRoom;
            break;
        case SPACEBAR:
            // Stops or starts the Animation
            startAnim = !startAnim;
            break;
        case '1':
            minion1Anim =!minion1Anim;
            break;
        case '2':
            minion2Anim =!minion2Anim;
            break;
        case '3':
            minion3Anim =!minion3Anim;
            break;
        case '4':
            minion4Anim =!minion4Anim;
            Anim4++;
            if(Anim4==3){
                Anim4 =0;
            }
            break;
        case '5':
            minion5Anim =!minion5Anim;
            break;
        case '6':
            minion6Anim =!minion6Anim;
            break;
        case GLUT_KEY_ESCAPE:
            exit(EXIT_SUCCESS);
    }
    
    glutPostRedisplay();
}
void Special(int key, int x, int y) {
    float a = 1.0;
    
    switch (key) {
        case GLUT_KEY_UP:
            camera.rotateX(a);
            break;
        case GLUT_KEY_DOWN:
            camera.rotateX(-a);
            break;
        case GLUT_KEY_LEFT:
            camera.rotateY(a);
            break;
        case GLUT_KEY_RIGHT:
            camera.rotateY(-a);
            break;
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
//    PlaySound("banana.wav", NULL, SND_ASYNC); //SND_FILENAME or SND_LOOP
    
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    
    glutCreateWindow("The Minions");
    glutDisplayFunc(Display);
    glutTimerFunc(0,Timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Special);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glutIdleFunc(Animation);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel(GL_SMOOTH);
    
    glutMainLoop();
}

