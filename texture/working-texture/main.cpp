#include<windows.h>
#include<bits/stdc++.h>
using namespace std;
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "imageloader.h"
/* GLUT callback Handlers */

float posL1=0.8f;
float posL2=0.8f;
float posL3=0.8f;
float R=0,G=0.4,B=1.0;
float skyAngle = 360;
float _angle = -0.0f;
float Rangle = 0.0f;

int flag_count, flag, change_flag_time;

int ii;


//##################################################################################################################
//##################################################################################################################
//##################################################################################################################

GLuint _textureIdGrass;
GLuint _textureIdDay;
GLuint _textureIdNight;
GLuint _textureIdBrick;
GLuint _textureIdWall;
GLuint _textureIdTreeBody;
GLuint _textureIdPlatform;
GLuint Black_monument;
GLuint flag_stand;
GLuint Floor;


// ------------------------------------------------------------------------------------------------------------------------
GLuint water_tex[10];
int water_count, water, change_water_time;

GLuint leaf_tex[10];
int lea_count, leaf, change_leaf_time;

GLuint flag_tex[10];
//int flag_count, flag, change_flag_time;
// ------------------------------------------------------------------------------------------------------------------------
GLuint makeaTree;
float x,y,z;

void makeCylinder(float height, float base){
GLUquadric *obj = gluNewQuadric();
//gluQuadricDrawStyle(obj, GLU_LINE);
glColor3f(0.0f, 1, 0.16f);glPushMatrix();
glRotatef(-90, 1.0,0.0,0.0);
gluCylinder(obj, base,base-(0.2*base), height, 20,20);
glPopMatrix();
glutSwapBuffers();
}

void makeTree(float height, float base){

float angle;
makeCylinder(height, base); glTranslatef(0.0, height, 0.0);
height -= height*.2; base-= base*0.3;
for(int a= 0; a<3; a++){
angle = rand()%50+20;
if(angle >48)
angle = -(rand()%50+20);
if (height >1){
glPushMatrix();
glRotatef(angle,1,0.0,1);
makeTree(height,base);
glPopMatrix();

}
 //else glColor3f(0.0,1.0/a,0.0);glutSolidSphere(.2,10,10); add like fruits...
}

}

GLuint loadTexture(Image* image)
{
    GLuint textureId;

    glGenTextures(1, &textureId); // 1 = # of texture we need

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}
float angle(float deg)
{
    float r = (deg / 180.0f) * 3.141592653589793f;
    return r;
}


//GLuint makeaTree;







void initrendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
//    t3dInit();
    makeaTree=glGenLists(1);
    glNewList(makeaTree, GL_COMPILE);
    makeTree(4,0.2);
    glEndList();

    Image* image = loadBMP("grass.bmp");
    _textureIdGrass = loadTexture(image);
    delete image;
    image = loadBMP("day.bmp");
    _textureIdDay = loadTexture(image);
    delete image;

    image = loadBMP("brick1.bmp");
    _textureIdBrick = loadTexture(image);
    delete image;


    image = loadBMP("platform.bmp");
    _textureIdPlatform = loadTexture(image);
    delete image;
    //##################################################################

    //###############################################################################################################
    image = loadBMP("f1.bmp");
    flag_tex[0] = loadTexture(image);
    delete image;
    image = loadBMP("f2.bmp");
    flag_tex[1] = loadTexture(image);
    delete image;
    image = loadBMP("f3.bmp");
    flag_tex[2] = loadTexture(image);
    delete image;
    image = loadBMP("f4.bmp");
    flag_tex[3] = loadTexture(image);
    delete image;
    image = loadBMP("f5.bmp");
    flag_tex[4] = loadTexture(image);
    delete image;
    image = loadBMP("f6.bmp");
    flag_tex[5] = loadTexture(image);
    delete image;
    image = loadBMP("f7.bmp");
    flag_tex[6] = loadTexture(image);
    delete image;
    image = loadBMP("f8.bmp");
    flag_tex[7] = loadTexture(image);
    delete image;
    image = loadBMP("f9.bmp");
    flag_tex[8] = loadTexture(image);
    delete image;

    flag_count = 9;
    flag = 0;
    change_flag_time = 100;
    image = loadBMP("wall.bmp");
    flag_stand = loadTexture(image);
    delete image;


    //##################################################################################################################
    image = loadBMP("1.bmp");
    water_tex[0] = loadTexture(image);
    delete image;
    image = loadBMP("2.bmp");
    water_tex[1] = loadTexture(image);
    delete image;
    image = loadBMP("3.bmp");
    water_tex[2] = loadTexture(image);
    delete image;
    image = loadBMP("4.bmp");
    water_tex[3] = loadTexture(image);
    delete image;
    image = loadBMP("5.bmp");
    water_tex[4] = loadTexture(image);
    delete image;
    image = loadBMP("6.bmp");
    water_tex[5] = loadTexture(image);
    delete image;
    image = loadBMP("7.bmp");
    water_tex[6] = loadTexture(image);
    delete image;
    image = loadBMP("8.bmp");
    water_tex[7] = loadTexture(image);
    delete image;
    image = loadBMP("9.bmp");
    water_tex[8] = loadTexture(image);
    delete image;
    image = loadBMP("10.bmp");
    water_tex[9] = loadTexture(image);
    delete image;
    water_count = 10;
    water = 0;
    change_water_time = 100;

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<MONUMENT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    image = loadBMP("monument.bmp");
    Black_monument= loadTexture(image);
    delete image;

    image = loadBMP("floor.bmp");
    Floor= loadTexture(image);
    delete image;
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<grasses>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //###############################################################################################################
    image = loadBMP("l1.bmp");
    leaf_tex[0] = loadTexture(image);
    delete image;
    image = loadBMP("l2.bmp");
    leaf_tex[1] = loadTexture(image);
    delete image;
    image = loadBMP("l3.bmp");
    leaf_tex[2] = loadTexture(image);
    delete image;
    image = loadBMP("l4.bmp");
    leaf_tex[3] = loadTexture(image);
    delete image;

    lea_count = 4;
    leaf = 0;
    change_leaf_time = 100;

}

GLfloat trans[3] = {0.1,0.1,0.1};
GLfloat viewangle = 0,tipangle = 5;
float i1=.5,i2=.5,i3=.5;
float view_x=0,view_z=-5;
float _scale;

void brickWall()
{

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureIdBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1.0,1.0,1.0);
    //glBegin(GL_QUADS);

    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.5,-2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.5,2,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.5,2,0.0);

    glEnd();

    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1); //front
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.5,-2,-10.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.5,-2,-10.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.5,2,-10.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.5,2,-10.0);

    glEnd();

    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1); //front
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.5,-2,-10.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.5,2,-10.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.5,2,0.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1); //front
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.5,-2,-10.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.5,2,-10.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.5,2,0.0);

    glEnd();

    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1); //front
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.5,2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.5,2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.5,2,-10.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.5,2,-10.0);

    glEnd();



}

void PechonerWall()
{
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-15.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(15.5,-2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(15.5,2,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-15.5,2,0.0);

    glEnd();
    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-15.5,-2,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(15.5,-2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(15.5,2,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-15.5,2,-1.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-15.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-15.5,2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-15.5,2,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-15.5,-2,-1.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(15.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(15.5,2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(15.5,2,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(15.5,-2,-1.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-15.5,2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(15.5,2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(15.5,2,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-15.5,2,-1.0);

    glEnd();



    //.........................................
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-12.5,2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-6.5,2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-6.5,4,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-12.5,4,0.0);

    glEnd();
    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-12.5,2,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-6.5,2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-6.5,4,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-12.5,4,-1.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-12.5,2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-12.5,4,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-12.5,4,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-12.5,2,-1.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-6.5,2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-6.5,4,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-6.5,4,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-6.5,2,-1.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-12.5,4,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-6.5,4,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-6.5,4,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-12.5,4,-1.0);

    glEnd();

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&,,,,,, faka square,,,,,,,,,,,,,,,,,&&&&&&&&&&&&&&&&&&&&&&&
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-3.5,2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(12.5,2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(12.5,4,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-3.5,4,0.0);

    glEnd();
    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-3.5,2,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(12.5,2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(12.5,4,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-3.5,4,-1.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-3.5,2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-3.5,4,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-3.5,4,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-3.5,2,-1.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(12.5,2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(12.5,4,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(12.5,4,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(12.5,2,-1.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-3.5,4,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(12.5,4,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(12.5,4,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-3.5,4,-1.0);

    glEnd();

    //........................................................fakar upore.....................
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-12.5,4,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(12.5,4,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(12.5,5,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-12.5,5,0.0);

    glEnd();
    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-12.5,4,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(12.5,4,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(12.5,5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-12.5,5,-1.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-12.5,4,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-12.5,5,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-12.5,5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-12.5,4,-1.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(12.5,4,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(12.5,5,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(12.5,5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(12.5,4,-1.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-12.5,5,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(12.5,5,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(12.5,5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-12.5,5,-1.0);

    glEnd();

//.......................................********............akdom uporer................*****
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-9.5,5,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(9.5,5,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(9.5,7,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-9.5,7,0.0);

    glEnd();
    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-9.5,5,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(9.5,5,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(9.5,7,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-9.5,7,-1.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-9.5,5,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-9.5,7,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-9.5,7,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-9.5,5,-1.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(9.5,5,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(9.5,7,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(9.5,7,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(9.5,5,-1.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-9.5,7,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(9.5,7,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(9.5,7,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-9.5,7,-1.0);

    glEnd();





}
void ShamnerWall()
{
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-14.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-2.5,-2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-2.5,1,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-14.5,1,0.0);

    glEnd();

    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-14.5,-2,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-2.5,-2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-2.5,1,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-14.5,1,-1.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-14.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-14.5,1,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-14.5,1,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-14.5,-2,-1.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-2.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-2.5,1,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-2.5,1,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-2.5,-2,-1.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-14.5,1,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-2.5,1,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-2.5,1,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-14.5,1,-1.0);

    glEnd();
    //................................................Front wall right side............................


    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(2.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(14.5,-2,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(14.5,1,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(2.5,1,0.0);

    glEnd();

    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(2.5,-2,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(14.5,-2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(14.5,1,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(2.5,1,-1.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(2.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(2.5,1,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(2.5,1,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(2.5,-2,-1.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(14.5,-2,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(14.5,1,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(14.5,1,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(14.5,-2,-1.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(2.5,1,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(14.5,1,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(14.5,1,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(2.5,1,-1.0);

    glEnd();



    //`````````````````````````````````Majhkhaner Black part``````````````````````````````````
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Black_monument);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1,1,1);

    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-2.5,-2,0.20);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(2.5,-2,0.20);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(2.5,1.2,0.20);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-2.5,1.2,0.20);

    glEnd();

    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-2.5,-2,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(2.5,-2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(2.5,1.2,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-2.5,1.2,-1.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-2.5,-2,0.20);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-2.5,-2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-2.5,1.2,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-2.5,1.2,0.20);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(2.5,-2,0.20);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(2.5,-2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(2.5,1.2,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(2.5,1.2,0.20);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-2.5,1.2,0.20);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(2.5,1.2,0.20);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(2.5,1.2,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-2.5,1.2,-1.0);

    glEnd();


    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


}
void ShamnerFloor1()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Floor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1,1,1);
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-8,0,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(8,0,-2.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(8,2,-2.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-8,2,-2.0);

    glEnd();

    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-8,0,-5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(8,0,-5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(8,2,-5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-8,2,-5.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-8,0,-5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-8,0,-2.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-8,2,-2.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-8,2,-5.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(8,0,-5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(8,0,-2.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(8,2,-2.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(8,2,-5.0);

    glEnd();

    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-8,2,-5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(8,2,-5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(8,2,-2.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-8,2,-2.0);

    glEnd();
    //..........................................2nd part2

    glColor3f(1,1,1);
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-8,0,5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-6.5,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-6.5,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-8,2,5.0);

    glEnd();

    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-8,0,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-8,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-8,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-8,2,-2.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-6.5,0,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-6.5,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-6.5,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-6.5,2,-2.0);

    glEnd();

    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-8,2,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-6.5,2,-2.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-6.5,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-8,2,5.0);

    glEnd();

    //.......................................................3rd square......

    glColor3f(1,1,1);
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-6.5,0,3);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-4,0,3);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-4,2,3);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-6.5,2,3);

    glEnd();

    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-6.5,2,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-4,2,-2.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-4,2,3);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-6.5,2,3);

    glEnd();
    //..........................................................4th square
    glColor3f(1,1,1);
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-4,0,5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(4,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(4,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-4,2,5.0);

    glEnd();

    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-4,0,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-4,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-4,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-4,2,-2.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(4,0,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(4,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(4,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(4,2,-2.0);

    glEnd();

    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-4,2,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(4,2,-2.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(4,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-4,2,5.0);

    glEnd();

    //................................./......................5 th
    glColor3f(1,1,1);
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(4,0,3.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(6.5,0,3.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(6.5,2,3.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(4,2,3.0);

    glEnd();

    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(4,2,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(6.5,2,-2.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(6.5,2,3.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(4,2,3.0);

    glEnd();

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 6 th
    glColor3f(1,1,1);
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(6.5,0,5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(8,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(8,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(6.5,2,5.0);

    glEnd();

    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(6.5,0,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(6.5,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(6.5,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(6.5,2,-2.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(8,0,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(8,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(8,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(8,2,-2.0);

    glEnd();

    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(6.5,2,-2.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(8,2,-2.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(8,2,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(6.5,2,5.0);

    glEnd();


}
void ShamnerFloor1_14th()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Floor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1,1,1);
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-3,0,5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(3,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(3,1,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-3,1,5.0);

    glEnd();

    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-3,0,-5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-3,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-3,1,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-3,1,-5.0);

    glEnd();
    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(3,0,-5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(3,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(3,1,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(3,1,-5.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-3,1,5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(3,1,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(3,1,-5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-3,1,-5.0);

    glEnd();

}
void grass_square()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdBrick);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1,1,1);
    //lft wall front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,0,1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.8,0,1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.8,2.5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.0,2.5,1.0);

    glEnd();

    //lft wall back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,0,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.8,0,-1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(-0.8,2.5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.0,2.5,-1.0);

    glEnd();

    //lft wall left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,0,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-1,0,1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(-1,2.5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.0,2.5,-1.0);

    glEnd();
    //lft wall right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.8,0,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.8,0,1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(-0.8,2.5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.8,2.5,-1.0);

    glEnd();

    //lft wall top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,2.5,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-1,2.5,1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(-0.8,2.5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.8,2.5,-1.0);

    glEnd();
    //..................................right wall
    //r8 wall front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(1,0,1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.8,0,1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.8,2.5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(1.0,2.5,1.0);

    glEnd();

    //r8 wall back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(1,0,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.8,0,-1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(0.8,2.5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(1.0,2.5,-1.0);

    glEnd();

    //r8 wall left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(1,0,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,0,1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(1,2.5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(1.0,2.5,-1.0);

    glEnd();
    //r8 wall right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.8,0,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.8,0,1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(0.8,2.5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.8,2.5,-1.0);

    glEnd();

    //r8 wall top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(1,2.5,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,2.5,1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(0.8,2.5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.8,2.5,-1.0);

    glEnd();

    //..................................front wall
    //front wall front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,0,1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,0,1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(1,2.5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.0,2.5,1.0);

    glEnd();

    //front wall back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,0,0.8);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,0,0.8);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(1,2.5,0.8);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.0,2.5,0.8);

    glEnd();

    //front wall top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,2.5,1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,2.5,1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(1,2.5,0.8);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1,2.5,0.8);

    glEnd();

    //..................................back wall
    //back wall front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,0,-0.8);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,0,-0.8);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(1,2.5,-0.8);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.0,2.5,-0.8);

    glEnd();

    //back wall back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,0,-1);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,0,-1);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(1,2.5,-1);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.0,2.5,-1);

    glEnd();

    //back wall top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,2.5,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,2.5,-1.0);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(1,2.5,-0.8);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1,2.5,-0.8);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, leaf_tex[leaf]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1,1,1);


    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.8,2.3,-0.8);
    glTexCoord2f(0.8f,0.0f);
    glVertex3f(-0.8,2.3,0.8);
    glTexCoord2f(1.0f,-1.0f);
    glVertex3f(0.8,2.3,0.8);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.8,2.3,-0.8);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void SkyGrass(GLUquadric *quadric)
{
    glPushMatrix();
    glRotatef(0.0,0.0,0.0,1.0); // orbits the planet around the sun
    glTranslatef(1.40,0.0,0.0);        // sets the radius of the orbit
    glRotatef(skyAngle,0.0,1.0,1.0); // revolves the planet on its axis
    glColor3f(4.0, 4.0, 4.0);          // green

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, _textureIdDay);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluQuadricTexture(quadric, 20);
    //glutWireSphere(0.16,20,20);        // Earth
    gluSphere(quadric,75,40,40);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdGrass);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glBegin(GL_QUADS);
    glColor3f(.4,.7,0);  // all bottom green
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-100000,0,100000);
    glTexCoord2f(10000.0f,0.0f);
    glVertex3f(100000,0,100000);
    glTexCoord2f(10000.0f,10000.0f);
    glVertex3f(100000,0,-100000);
    glTexCoord2f(0.0f,10000.0f);
    glVertex3f(-100000,0,-100000);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void update(int val)
{
    water++;
    if(water >= water_count)
    {
        water = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(change_water_time,update,0);
}
void update2(int val)
{
    leaf++;
    if(leaf >= lea_count)
    {
        leaf = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(change_leaf_time,update2,0);
}
void update3(int val)
{
    flag++;
    if(flag >= flag_count)
    {
        flag = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(change_flag_time,update3,0);
}
void draw_flag()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, flag_tex[flag]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1,1,1);

    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0,0);
    glVertex3f(-1,2,-0.5);
    glTexCoord2f(1,0);
    glVertex3f(-1,3,-0.5);
    glTexCoord2f(1,1);
    glVertex3f(0.0,3,-0.5);
    glTexCoord2f(0,1);
    glVertex3f(0.0,2,-0.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^flag er stand^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, _textureIdwater2);
    glBindTexture(GL_TEXTURE_2D, flag_stand);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    //front
    glBegin(GL_QUADS);

    //front
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1.2,-2,-0.4);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-1,-2,-0.4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-1,3,-0.4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.2,3,-0.4);

    glEnd();



    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1.2,-2,-0.6);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-1,-2,-0.6);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-1,3,-0.6);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.2,3,-0.6);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1.2,-2,-0.6);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-1.2,-2,-0.4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-1.2,3,-0.4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.2,3,-0.6);

    glEnd();
    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1.0,-2,-0.6);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-1.0,-2,-0.4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-1.0,3,-0.4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.0,3,-0.6);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1.0,3,-0.6);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-1.2,3,-0.6);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-1.2,3,-0.4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1.0,3,-0.4);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void draw_water()
{
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, _textureIdwater2);
    glBindTexture(GL_TEXTURE_2D, water_tex[water]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-14.5,1.0,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(14.5,1.0,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(14.5,1.0,-10.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-14.5,1.0,-10.0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void draw_monument()
{
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, _textureIdwater2);
    glBindTexture(GL_TEXTURE_2D, Black_monument);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    //front
    glBegin(GL_QUADS);

    //front
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,-2,1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,-2,1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(1,5,1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1,5,1.0);

    glEnd();


    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,-2,-1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,-2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(1,5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1,5,-1.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,-2,1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-1,-2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-1,5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1,5,1.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(1,-2,1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,-2,-1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(1,5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(1,5,1.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-1,5,1.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1,5,1.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(1,5,-1.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-1,5,-1.0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void Stair1()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, _textureIdwater2);
    glBindTexture(GL_TEXTURE_2D, flag_stand);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.3,0.0,4);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.0,0.0,4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.0,1.8,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.3,1.8,4);

    glEnd();
    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.3,0.0,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.0,0.0,-5);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.0,1.8,-5);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.3,1.8,-5);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.3,0.0,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.3,0.0,4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.3,1.8,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.3,1.8,-5);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.3,1.8,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.0,1.8,-5);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.0,1.8,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.3,1.8,4);

    glEnd();
    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,2nd stair
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.6,0.0,4);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.3,0.0,4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.3,1.6,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.6,1.6,4);

    glEnd();
    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.6,0.0,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.3,0.0,-5);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.3,1.6,-5);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.6,1.6,-5);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.6,0.0,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.6,0.0,4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.6,1.6,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.6,1.6,-5);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.6,1.6,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.3,1.6,-5);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.3,1.6,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.6,1.6,4);

    glEnd();

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,3rd stair
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.9,0.0,4);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.6,0.0,4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.6,1.4,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.9,1.4,4);

    glEnd();
    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.9,0.0,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.6,0.0,-5);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.6,1.4,-5);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.9,1.4,-5);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.9,0.0,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.9,0.0,4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.9,1.4,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.9,1.4,-5);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.9,1.4,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.6,1.4,-5);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.6,1.4,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.9,1.4,4);

    glEnd();

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,4th stair
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.12,0.0,4);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.9,0.0,4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.9,1.0,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.12,1.0,4);

    glEnd();
    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.12,0.0,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.9,0.0,-5);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.9,1.0,-5);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.12,1.0,-5);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.12,0.0,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.12,0.0,4);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.12,1.0,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.12,1.0,-5);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.12,1.0,-5);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.9,1.0,-5);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.9,1.0,4);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.12,1.0,4);

    glEnd();


    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void Front_Floor1()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Floor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1,1,1);
    //front
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-15,0,5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(15,0,5.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(15,.1,5.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-15,.1,5.0);

    glEnd();

    //back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-15,0,0.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(15,0,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(15,.1,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-15,.1,0.0);

    glEnd();
    //left
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-15,0,5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-15,0,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-15,.1,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-15,.1,5.0);

    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(15,0,5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(15,0,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(15,.1,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(15,.1,5.0);

    glEnd();
    //top
    glBegin(GL_QUADS);
    glColor3f(1,1,1);  // all white
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-15,0.1,5.0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-15,0.1,0.0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(15,.1,0.0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(15,.1,5.0);

    glEnd();

}

void drawscene()
{
    GLUquadric *quadric;
    quadric = gluNewQuadric();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear before draw somethings
    glClearColor(R,G,B,1); // for background -- day night
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity();

    glTranslatef(.5,0,-20);


    GLfloat ambientColor[] = {i1,i2,i3,1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Light 0
    GLfloat lightColor0[] = {posL1, posL2, posL3, 1.0f};
    GLfloat lightPos0[] = {0.0f, 8.0f, -4.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);



    glRotatef (tipangle, 1,0,0);
    glRotatef(Rangle,0,1,0);
    glTranslatef(view_x,0,view_z);
    glRotatef(Rangle,0,1,0);
    glTranslatef(trans[0],trans[1],trans[2]);

    //*******************************************************---------SkyGrass Function******************************
    SkyGrass(quadric);

    glPushMatrix();
    glTranslatef(15.0,2.0,-20);
    brickWall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.0,2.0,-20);
    brickWall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,2.0,-30);
    PechonerWall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,2,-20);
    ShamnerWall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,0,-15);
    ShamnerFloor1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0,0,-15);
    ShamnerFloor1_14th();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.0,0,-15);
    ShamnerFloor1_14th();
    glPopMatrix();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    square GRASS      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    glPushMatrix();
    glTranslatef(8.0,0,-16);
    grass_square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0,0,-16);
    grass_square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0,0,-10);
    grass_square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0,0,-10);
    grass_square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.5,0,-16);
    grass_square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.5,0,-16);
    grass_square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.5,0,-10);
    grass_square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.5,0,-10);
    grass_square();
    glPopMatrix();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    FLAG      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    glPushMatrix();
    glTranslatef(5.5,2.5,-20);
    draw_flag();
    glPopMatrix();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    water      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    glPushMatrix();
    glTranslatef(0.0,1.0,-20);
    draw_water();
    glPopMatrix();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    monument      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    glPushMatrix();
    glTranslatef(5.0,2.0,-25);
    draw_monument();
    glPopMatrix();

//....................................................STAIRS.................................................

    glPushMatrix();
    glTranslatef(-8.0,0.0,-15);
    Stair1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.0,-1.0,-15);
    Stair1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0,0.0,-16);
    glRotatef(180,0.0,1.0,0.0);
    Stair1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.0,-1.0,-16);
    glRotatef(180,0.0,1.0,0.0);
    Stair1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0,0.0,-12);
    glRotatef(90,0.0,1.0,0.0);
    Stair1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.0,0.0,-12);
    glRotatef(90,0.0,1.0,0.0);
    Stair1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(11.0,0.0,-10);
    glScalef(.5,.5,.5);
    glRotatef(90,0.0,1.0,0.0);
    Stair1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.0,0.0,-10);
    glScalef(.5,.5,.5);
    glRotatef(90,0.0,1.0,0.0);
    Stair1();
    glPopMatrix();

    //???????????????????????????????????????????????????????????????front floor1
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    Front_Floor1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,0.0,1.0);
    glScalef(1,2,1);
    Front_Floor1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.0,0.0,3.0);
    glScalef(1,0.2,1);
    grass_square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,0.0,3.0);
    glScalef(1,0.2,1);
    grass_square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0,0.0,3.0);
    glScalef(1,0.2,1);
    grass_square();
    glPopMatrix();

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%     TREE............................
    glPushMatrix();

    glTranslatef(10.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(-30,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(10.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(-5,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(10.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(25,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(10.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(65,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%TREE............................//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%     TREE............................
    glPushMatrix();

    glTranslatef(0.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(-30,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(-5,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(25,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(65,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%TREE............................//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%     TREE............................
    glPushMatrix();

    glTranslatef(-10.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(-30,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(-10.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(-5,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(-10.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(25,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(-10.0,0.0,3.0);
    glScalef(.2,0.2,.2);
    glColor3f(0.0,1.0,0.0);
    glRotatef(65,0.0,1.0,0.0);
    glCallList(makeaTree);

    glPopMatrix();
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%TREE............................
    glutSwapBuffers();
}



void my_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 'D':
    case 'd':
        tipangle-=5;
        if(tipangle<5)
            tipangle=5;
        break;
    case 'u':
    case 'U':
        tipangle+=5;
        if(tipangle>90)
            tipangle=90;
        break;

    case 'a' :
        trans[0] = 0.1,trans[1] = 0.1,trans[2] = 0.1;
        viewangle = 0,tipangle = 5;
        view_x=0,view_z=-5;
        break;
    case 'r':
    case 'R':
        Rangle += 2.5f;
        if (Rangle > 360)
        {
            Rangle -= 360;
        }
        break;

    }
    glutPostRedisplay();
}



void special_key(int key,int x,int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT :
        view_x += .3;
        break;
    case GLUT_KEY_RIGHT:
        view_x -= .3;
        break;
    case GLUT_KEY_UP   :
        view_z += .3;
        break;
    case GLUT_KEY_DOWN :
        view_z -= .3;
        break;
    }
    glutPostRedisplay();
}








/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900,600);
    glutInitWindowPosition(100,200);

    glutCreateWindow("Intellectual Monument");

    initrendering();
    glutDisplayFunc(drawscene);
    glutKeyboardFunc(my_keyboard);
    glutSpecialFunc(special_key);
    glutTimerFunc(change_flag_time,update3,0);
    glutTimerFunc(change_leaf_time,update2,0);
    glutTimerFunc(change_water_time,update,0);


    R = 0.0,G = 0.4,B = 1.0;
    glClearColor (0.1, 0.4, 0.6, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60,1.5,1,100);
    glMatrixMode(GL_MODELVIEW);
    //glutPostRedisplay();
    glutMainLoop();

    return 0;
}
