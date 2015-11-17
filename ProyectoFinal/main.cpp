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
char title[] = "Space Capitán";
char jugar[] = "Jugar";
char instr[] = "Instrucciones";
char salir[] = "Salir";
bool menuJugar = false, menuInstr = false, menuSalir = false;
int botonJugar = 400, botonInstr = 280, botonSalir = 150;
static GLuint texName[2];
int spacePositionX = 400, spacePositionY = 250;
string rootPath;
GLMmodel model[1];
string fullPath = __FILE__;
size_t found = fullPath.find_last_of("/\\");
string path = fullPath.substr(0,found+1);

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
                spacePositionX = spacePositionX - 5;

            }
            break;
        case 'd':
        case 'D':
            
            if (spacePositionX < 480) {
                spacePositionX = spacePositionX + 5;
                
            }
            break;
        case 'w':
        case 'W':
            if (spacePositionY < 350) {
                spacePositionY = spacePositionY + 5;
                
            }
            break;
        case 's':
        case 'S':
            if (spacePositionY > 250) {
                spacePositionY = spacePositionY - 5;
                
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
    Image* image;
    rootPath = path + "img/background.bmp";
    image = loadBMP(&rootPath[0]);loadTexture(image, i++);
    delete image;
}

void initModels(){
    rootPath = path + "models/manzana.obj";
    model[0] = *glmReadOBJ(&rootPath[0]);
    glmUnitize(&model[0]);
    glmVertexNormals(&model[0], 90.0, GL_TRUE);
}

void myMouse(int button, int state, int x, int y)
{
    y = height-y;
    cout<<"x: "<<x<<"| y: "<<y<<endl;
    if (state == GLUT_DOWN)
    {
        //Si el usuario oprime el boton izq del mouse
        if (button == GLUT_LEFT_BUTTON)
        {
            if (y >= botonJugar-40 && y<= botonJugar+40 && x >= 400-150 && x <= 400+150 && globalState == 0 ) {
                menuJugar = true;
                globalState = 1;
            } else {
                menuJugar = false;
            }
            
            if (y >= botonInstr-40 && y<= botonInstr+40 && x >= 400-150 && x <= 400+150 && globalState == 0 ) {
                menuInstr = true;
                globalState = 2;
            } else {
                menuInstr = false;
            }
            
            if (y >= botonSalir-40 && y<= botonSalir+40 && x >= 400-150 && x <= 400+150 && globalState == 0 ) {
                menuSalir = true;
                globalState = 3;
            } else {
                menuSalir = false;
            }
            
            glutPostRedisplay();
        }
    }
    if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
    {
        menuJugar = false;
        menuInstr = false;
        menuSalir = false;
        glutPostRedisplay();
    }
    
}

void drawText(char *text, int x, int y)
{
    char *p;
    glTranslatef(x, y, 0);
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
    glScaled(0.7, 0.7, 0.0);
    drawText(title, 130, 700);
    glPopMatrix();
    
    // JUGAR
    glPushMatrix();
    glPushMatrix();
    glLineWidth(1.0);
    glScaled(0.4, 0.4, 0.0);
    drawText(jugar, 900, 930);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(400,botonJugar, -1);
    glScaled(350,80, 1);
    if (menuJugar) {
        glColor3d(0, 0, .9);
    } else {
        glColor3d(0, 0, .3);
    }
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
    glScaled(0.4, 0.4, 0.0);
    drawText(instr, 720, 630);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(400,botonInstr, -1);
    glScaled(350,80, 1);
    if (menuInstr) {
        glColor3d(0, 0, .9);
    } else {
        glColor3d(0, 0, .3);
    }
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
    glScaled(0.4, 0.4, 0.0);
    drawText(salir, 800, 350);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(400,botonSalir, -1);
    glScaled(350,80, 1);
    if (menuSalir) {
        glColor3d(0, 0, .9);
    } else {
        glColor3d(0, 0, .3);
    }
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
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f,  -5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 800.0f, 0.0f,  -5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 800.0f,  600.0f,  -5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f,  600.0f,  -5.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawShip()
{
    
    glPushMatrix();
    glTranslatef (spacePositionX, spacePositionY, 500);
    glScalef(30,30,30);
    //glRotatef(0,0,0,6);
    glmDraw(&model[0], GLM_COLOR);
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
    cout<<globalState<<endl;
    switch (globalState) {
        case 0:
            menu();
            break;
        case 1:
            drawShip();
            break;
        case 2:
            break;
        case 3:
            exit(0);
            break;
            
        default:
            break;
    }
    
    glutSwapBuffers();//ya tiene integrado el glFlush
    
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

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(300,300);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Space");
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    initRendering();
    initModels();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);
    glutReshapeFunc(resize);
    //glutTimerFunc(100, timer, 1);
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

