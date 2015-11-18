//
//  main.cpp
//  ProyectoFinal
//
//  Created by Juan Paulo Lara on 10/28/15.
//  Copyright © 2015 Juan Paulo Lara. All rights reserved.
//

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>

#include "Imageloader.h"
#include "glm.h"

using namespace std;

int width = 800, height = 600;
int bgCounter = 0;
char title[] = "Space Capitan";
char jugar[] = "Jugar";
char instr[] = "Instrucciones";
char salir[] = "Salir";
char scoreLblBase[] = "Score: ";
char scoreLbl[] = "Score: ";
string highScoreLblBase = "High Score: ";
char highScoreLbl[] = "";
char back[] = "Volver<---------";
char siguente[] = "Siguiente";
char instructions[] = "Esquiva estos objetos son malos";
char instructions2[] = "Estos son buenos mejoran tu puntaje";
int botonJugar = 400, botonInstr = 280, botonSalir = 150;
static GLuint texName[30];
int spacePositionX = 400, spacePositionY = 250;
string rootPath;
GLMmodel model[2];
string fullPath = __FILE__;
size_t found = fullPath.find_last_of("/\\");
string path = fullPath.substr(0,found+1);
int zIndexGood = 0;
int zIndexBad = -300;
int badX, badY, goodX, goodY;
int score = 0;
int speed = 50;
int goodImage;
int badImage;
int livesCount = 3;
int hightScore = 0;

/*
 * 0 = Menu
 * 1 = Jugar
 * 2 = Instr
 * 3 = salir
 */
int globalState = 0;

void myKeyboard(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 'a':
        case 'A':
            if (spacePositionX > 320) {
                spacePositionX = spacePositionX - 10;

            }
            break;
        case 'd':
        case 'D':
            
            if (spacePositionX < 480) {
                spacePositionX = spacePositionX + 10;
                
            }
            break;
        case 'w':
        case 'W':
            if (spacePositionY < 350) {
                spacePositionY = spacePositionY + 10;
                
            }
            break;
        case 's':
        case 'S':
            if (spacePositionY > 250) {
                spacePositionY = spacePositionY - 10;
                
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
    
}

//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{
    
    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    
}
void initRendering()
{
    GLuint i=0;
    glGenTextures(30, texName); //Make room for our texture
    Image* image;
    rootPath = path + "img/space_500-1 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-2 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-3 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-4 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-5 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-6 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-7 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-8 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-9 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-10 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-11 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-12 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-13 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-14 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-15 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-16 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-17 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/space_500-18 (dragged).bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    // Texture
    rootPath = path + "img/metal.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    //BAD things 19-24
    rootPath = path + "img/bad1.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/bad2.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/bad3.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/bad4.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/bad5.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    // GOD things 25-29
    rootPath = path + "img/good1.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/good2.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/good3.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/good4.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    rootPath = path + "img/good5.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    delete image;
}
void initModels(){
    rootPath = path + "models/aircraft.obj";
    model[0] = *glmReadOBJ(&rootPath[0]);
    glmUnitize(&model[0]);
    glmVertexNormals(&model[0], 90.0, GL_TRUE);
    
    rootPath = path + "models/Heart.obj";
    model[1] = *glmReadOBJ(&rootPath[0]);
    glmUnitize(&model[1]);
    glmVertexNormals(&model[1], 90.0, GL_TRUE);
}

void myMouse(int button, int state, int x, int y)
{
    y = height - y;
    cout << "x: " << x << "| y: " << y << endl;
    if (state == GLUT_DOWN)
    {
        
        //Si el usuario oprime el boton izq del mouse
        if (button == GLUT_LEFT_BUTTON)
        {
            int segmentYLen = height / 5;
            int segmentXLen = width / 4;
            // Start Game
            if (y >= segmentYLen * 3 && y <= segmentYLen * 4 && x >= segmentXLen * 1 && x <= segmentXLen*3  && globalState == 0) {
                globalState = 1;
            }
            
            // inst menu
            if (y >= segmentYLen * 2 && y <= segmentYLen * 3 && x >= segmentXLen * 1 && x <= segmentXLen * 3 && globalState == 0) {
                globalState = 2;
            }
            
            // back to HOME
            if (y >= 0 && y <= segmentYLen && x >= 0 && x <= segmentXLen && globalState == 2) {
                globalState = 0;
            }
            
            // close
            if (y >= segmentYLen * 1 && y <= segmentYLen * 2 && x >= segmentXLen * 1 && x <= segmentXLen*3 && globalState == 0) {
                globalState = 3;
            }
            
            glutPostRedisplay();
        }
    }
    
}

void drawText(char *text, int x, int y, float scale)
{
    char *p;
    glTranslatef(x, y, 0);
    glScaled(scale, scale, 0.0);
    for (p = text; *p; p++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    }
}

void menu()
{
    glClearColor(0, 0, 0, 1.0);
    glColor3f(1, 1, 1);
    
    // Titulo
    glPushMatrix();
    glLineWidth(3.0);
    drawText(title, 100, 490, 0.7);
    glPopMatrix();
    
    // JUGAR
    glPushMatrix();
    glPushMatrix();
    glLineWidth(1.0);
    drawText(jugar, 350, 375, 0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(400,botonJugar, -1);
    glScaled(350,80, 1);
    glColor3d(0, 0, .3);
    glRotated(20, 1.0, 1.0, 0);
    glutSolidCube(1);
    glColor3d(1, 1, 1);
    glLineWidth(3);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    
    // INSTR
    glPushMatrix();
    glColor3f(1, 1, 1);
    glPushMatrix();
    glLineWidth(1.0);
    drawText(instr, 280, 250, 0.4);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(400,botonInstr, -1);
    glScaled(350,80, 1);
    glColor3d(0, 0, .3);
    glRotated(15, 1.0, 1.0, 1.0);
    glutSolidCube(1);
    glColor3d(1, 1, 1);
    glLineWidth(3);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    
    // SALIR
    glPushMatrix();
    glColor3f(1, 1, 1);
    glPushMatrix();
    glLineWidth(1.0);
    drawText(salir, 320, 140, 0.4);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(400,botonSalir, -1);
    glScaled(350,80, 1);
    glColor3d(0, 0, .3);
    glRotated(-20, 1.0, 1.0, 0);
    glutSolidCube(1);
    glColor3d(1, 1, 1);
    glLineWidth(3);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
}

void paintBackground()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName[bgCounter]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f,  -10.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 800.0f, 0.0f,  -10.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 800.0f,  600.0f,  -10.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f,  600.0f,  -10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawShip()
{
    glPushMatrix();
    
    // habilita la textura
    glEnable(GL_TEXTURE_2D);
    
    // hbailitar esto tambien
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[18]);
    glPushMatrix();
    glTranslatef(spacePositionX, spacePositionY, 500);
    glScalef(35, 35, 35);
    glRotatef(20, 5, 0, 0);
    glmDraw(&model[0], GLM_TEXTURE);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
    
    
}

void displayInstructions()
{
    glClearColor(0, 0, 0, 1.0);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glLineWidth(3.0);
    drawText(instr, 140, 490, 0.7);
    glPopMatrix();
    
    // Back button
    glPushMatrix();
    glPushMatrix();
    glLineWidth(1.0);
    drawText(back, 100, 70, 0.4);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(150,100, -1);
    glScaled(150,80, 1);
    glRotated(20, 1.0, 1.0, 0);
    glColor3d(0, 0, .3);
    glutSolidCube(1);
    glColor3d(1, 1, 1);
    glLineWidth(3);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    
    // TEXT
    glPushMatrix();
    drawText(instructions, 60, 430, 0.2);
    glPopMatrix();
    glPushMatrix();
    drawText(instructions2, 60, 280, 0.2);
    glPopMatrix();
    
}

void randomBadPosition()
{
    // X 300 - 500
    badX = rand() % 200 + 300;
    // Y 250 - 365
    badY = rand() % 115 + 250;
    // randomize image
    badImage = rand() % 5 + 19;
}

void randomGoodPosition()
{
    // X 300 - 500
    goodX = rand() % 200 + 300;
    // Y 250 - 360
    goodY = rand() % 110 + 250;
    // randomize image
    goodImage = rand() % 5 + 24;
}

void drawBadSphera()
{
    glPushMatrix();

    // habilita la textura
    glEnable(GL_TEXTURE_2D);
    
    // hbailitar esto tambien
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[badImage]);
    glPushMatrix();
    if (zIndexBad == 0) {
        randomBadPosition();
    }
    glTranslatef(badX, badY, zIndexBad);
    
    glutSolidSphere(10, 100, 100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
    
}

void drawGoodSphera()
{
    glPushMatrix();
    
    // habilita la textura
    glEnable(GL_TEXTURE_2D);
    
    // hbailitar esto tambien
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[goodImage]);
    glPushMatrix();
    if (zIndexGood == 0) {
        randomGoodPosition();
    }
    glTranslatef(goodX, goodY, zIndexGood);
    
    glutSolidSphere(10, 100, 100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
    
}

void drawScore()
{
    strcpy (scoreLbl,scoreLblBase);
    char integer_string3[10];
    sprintf(integer_string3, "%d", score/10);
    strcat(scoreLbl, integer_string3);
    glClearColor(0, 0, 0, 1.0);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glLineWidth(3.0);
    drawText(scoreLbl, 450, 520, 0.3);
    glPopMatrix();
}

void drawInstImages()
{
    glPushMatrix();
    
    // habilita la textura
    glEnable(GL_TEXTURE_2D);
    
    // hbailitar esto tambien
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    for (int i = 0; i<5; i++) {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texName[19+i]);
        glPushMatrix();
        glTranslatef(300+i*50, 330, 300);
        glutSolidSphere(20, 100, 100);
        glPopMatrix();
    }
    for (int i = 0; i<5; i++) {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texName[24+i]);
        glPushMatrix();
        glTranslatef(300+i*50, 250, 300);
        glutSolidSphere(20, 100, 100);
        glPopMatrix();
    }
    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
}

void drawLives()
{
    for (int i = 0; i < livesCount; i++) {
        glPushMatrix();
        glTranslatef(355+10*i, 330, 600);
        glScalef(10, 10, 10);
        glRotatef(90, 0, 1, 0);
        glmDraw(&model[1], GLM_NONE);
        glPopMatrix();
    }
}

void restart()
{
    spacePositionX = 400;
    spacePositionY = 250;
    zIndexGood = 0;
    zIndexBad = -300;
    speed = 50;
    livesCount = 3;
    globalState = 0;
    if (hightScore < score ) {
        hightScore = score/10;
    }
    score = 0;
}

void drawHighScore()
{
    cout<<highScoreLblBase<<endl;
    glPushMatrix();
    glClearColor(0, 0, 0, 1.0);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glLineWidth(3.0);
    drawText(&highScoreLblBase[0], 250, 30, 0.3);
    glPopMatrix();
    glPushMatrix();
    char integer_string[30];
    sprintf(integer_string, "%d", hightScore);
    strcpy(highScoreLbl, integer_string);
    glClearColor(0, 0, 0, 1.0);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glLineWidth(3.0);
    drawText(highScoreLbl, 550, 30, 0.3);
    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    
    //Draw backgroud
    paintBackground();
    
    // MENU
    switch (globalState) {
        case 0:
            menu();
            drawHighScore();
            break;
        case 1:
            if (livesCount == 0) {
                restart();
            }
            drawShip();
            drawBadSphera();
            drawGoodSphera();
            drawScore();
            drawLives();
            break;
        case 2:
            displayInstructions();
            drawInstImages();
            break;
        case 3:
            exit(0);
            break;
            
        default:
            break;
    }
    
    glutSwapBuffers();//ya tiene integrado el glFlush
    
}

void validateColission()
{
    // colission to bad sphere
    if (zIndexBad > 480 &&
        badX > spacePositionX - 35 && badY < spacePositionX + 35 &&
        badY > spacePositionY - 10 && badY < spacePositionY + 10) {
        speed = speed + 5;
        zIndexBad = 0;
        score = score - 1000;
        livesCount--;
    }
    // colission to good sphere
    if (zIndexGood > 480 &&
        goodX > spacePositionX - 35 && goodX < spacePositionX + 35 &&
        goodY > spacePositionY - 10 && goodY < spacePositionY + 10) {
        if (speed > 6) {
            speed = speed - 5;
        }
        zIndexGood = 0;
        score = score + 1000;
    }
}

void timer(int t)
{

    if (bgCounter == 17) {
        bgCounter = 0;
    }
    // GAME START
    if(globalState == 1) {
        glutTimerFunc(speed,timer,0);
        score ++;
        zIndexBad = zIndexBad + 5;
        zIndexGood = zIndexGood + 5;
        if (zIndexBad >= 600) {
            zIndexBad = 0;
        }
        if (zIndexGood >= 600) {
            zIndexGood = 0;
        }
        validateColission();
    } else {
        // MENU
        glutTimerFunc(50,timer,0);
    }
    
    glutPostRedisplay();
    bgCounter++;
}

void resize(int w, int h)
{
    width = w;
    height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / (float)h, 1.0, 2000.0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(400, 300, 700, 400, 300, 0, 0, 1, -1);
}

void init()
{

}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Space");
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    initRendering();
    initModels();
    glShadeModel(GL_SMOOTH);

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);
    glutReshapeFunc(resize);
    glutTimerFunc(50, timer, 1);
    glutMainLoop();
    
    return 0;
}

/////////////////--------------------------

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{
    
}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
    //Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }
    
    //Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }
    
    //Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
    
    //Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }
    
    //Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
        array(array_), isReleased(false)
        {
        }
        
        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }
        
        T* get() const
        {
            return array;
        }
        
        T &operator*() const
        {
            return *array;
        }
        
        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        T* operator->() const
        {
            return array;
        }
        
        T* release()
        {
            isReleased = true;
            return array;
        }
        
        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }
        
        T* operator+(int i)
        {
            return array + i;
        }
        
        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);
    
    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
        case 40:
            //V3
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            //OS/2 V1
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        case 64:
            //OS/2 V2
            assert(!"Can't load OS/2 V2 bitmaps");
            break;
        case 108:
            //Windows V4
            assert(!"Can't load Windows V4 bitmaps");
            break;
        case 124:
            //Windows V5
            assert(!"Can't load Windows V5 bitmaps");
            break;
        default:
            assert(!"Unknown bitmap format");
    }
    
    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);
    
    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }
    
    input.close();
    return new Image(pixels2.release(), width, height);
}

