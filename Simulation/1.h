#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <time.h>
#include <cmath>
#define pi 3.14159265359
using namespace std;
static int window;
static int menuid;
void drawPlane(int p, int i, int j, int size)
{
  float *arr[2];
  int n=p; //no of sides
  int x=i; //xpos
  int y=j; //ypos
  int r=size; //size
  arr[0] = new float[n];
  arr[1] = new float[n];

  float rad = pi/180;
  float angle = rad * (180/n); //angle of rotation of a polygon of side n
  float t=0;

  for(int i=0; i<n; i++)
  {
    arr[0][i]=x+r*cos(t);  //xpos of vertex
    arr[1][i]=y+r*sin(t);  //ypos of vertex
    t+=2*angle;            //updation of t till the next vertex
  }
  glColor3f(0.2,0.2,0.2);
  glLineWidth(5);
  glBegin(GL_LINE_LOOP);

  for(int i=0; i<n; i++)
    glVertex2f(arr[0][i],arr[1][i]);

  glEnd();
  glFlush();

  glBegin(GL_LINES);
  glVertex2f(213,369);
  glVertex2f(-213,-369);
  glVertex2f(213,-369);
  glVertex2f(-213,369);
  glVertex2f(-426,0);
  glVertex2f(426,0);
  glEnd();

}

class Shapes
{
  int n;  //sides
  float x,y;  //x y position
  float *arr[2];  //array of vertices
  int r;  //size
  float angle;  //internal rotation angle
  float color[3];
public:

  void init(int p, float i, float j, int size)
  {
    n=p; //no of sides
    x=i; //xpos
    y=j; //ypos
    r=size; //size
    arr[0] = new float[n];
    arr[1] = new float[n];

    float rad = pi/180;
    angle = rad * (180/n);
    float t=angle;

    for(int i=0; i<n; i++)
    {
      arr[0][i]=x+r*cos(t);
      arr[1][i]=y+r*sin(t);
      t+=2*angle;
    }

    color[0]=(float)(rand()%10000)/10000;  //random float value for color
    color[1]=(float)(rand()%10000)/10000;
    color[2]=(float)(rand()%10000)/10000;

  }

  void draw()
  {

    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_POLYGON);
    for(int i=0; i<n; i++) //original piece
      glVertex2f(arr[0][i],arr[1][i]);
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0; i<n; i++) //reflection on x axis
      glVertex2f(arr[0][i],-arr[1][i]);
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0; i<n; i++) //reflection on lower left segment
      glVertex2f(arr[0][i]*sin(-pi/6)+arr[1][i]*cos(-pi/6),arr[0][i]*cos(-pi/6)-arr[1][i]*sin(-pi/6));
    glEnd();

    glBegin(GL_POLYGON);
    for(int i=0; i<n; i++) //reflection on top left segment
      glVertex2f(-(arr[0][i]*cos(pi/3)-arr[1][i]*sin(pi/3)),-(arr[0][i]*sin(pi/3)+arr[1][i]*cos(pi/3)));
    glEnd();

    glBegin(GL_POLYGON);
    for(int i=0; i<n; i++) //reflection on lower right segment
      glVertex2f(arr[0][i]*cos(-2*pi/3)+arr[1][i]*sin(-2*pi/3), arr[0][i]*sin(-2*pi/3)-arr[1][i]*cos(-2*pi/3));
    glEnd();

    glBegin(GL_POLYGON);
    for(int i=0; i<n; i++) //reflection on upper right segment
      glVertex2f(arr[0][i]*cos(2*pi/3)-arr[1][i]*sin(2*pi/3), arr[0][i]*sin(2*pi/3)+arr[1][i]*cos(2*pi/3));
    glEnd();
    glFlush();
  }

  void display()
  {
    cout<<"No. of sides : "<<n;
    cout<<"\nPosition : ("<<x<<','<<y<<")\n";
    cout<<"Coordinates : \n";
    for(int i=0; i<n; i++)
      cout<<'('<<arr[0][i]<<','<<arr[1][i]<<')'<<" ";
    cout<<endl;
    cout<<"Size : "<<r<<endl;
    cout<<"Angle of rotation : "<<angle<<endl;
    cout<<"Color : "<<"("<<color[0]<<color[1]<<color[2]<<")"<<endl;
  }

  void shuffle(float p, float q)  //to change just the x,y coordinate of the shape and redraw it
  {
    x=p;
    y=q;
    float rad = pi/180;
    angle = rad * (180/n);
    float t=angle;

    for(int i=0; i<n; i++)
    {
      arr[0][i]=x+r*cos(t);
      arr[1][i]=y+r*sin(t);
      t+=2*angle;
    }
  }
};

class Kaleidoscope
{
  Shapes *s;
  int n;
public:
  Kaleidoscope(int x)
  {
    n=x;
    s= new Shapes[n];  //array of shapes

    for(int i=0; i<n; i++)
    {
      int w=(int(rand()))%7+3;  //no of sides
      float y = -rand()%320-10;
      float x = y*0.577+rand()%390;

      int z=(int(rand()))%20+3;     //size
      s[i].init(w,x,y,z);    //initialise shape with the given specification
    }
  }

  void drawShapes()
  {
    for(int i=0; i<n; i++)
    {
      //s[i].display();
      s[i].draw();    //main draw function to draw all shapes
    }

    glFlush();
  }

  void shuffle()
  {
    for(int i=0; i<n; i++)
    {
      float y = -rand()%320-10  ;   //repositioning the shapes again to simulate shuffling
      float x = y*0.577+rand()%390;
      s[i].shuffle(x,y);

    }
  }
};

Kaleidoscope k(120);
void shuffle(Kaleidoscope &k)
{
  k.shuffle();
}
void mouse(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPlane(6,0,0,426);
    k.drawShapes();
    shuffle(k);
    k.drawShapes();
  }
}

void menu(int num){
  if(num == 0)
  {
    glutDestroyWindow(window);
    exit(0);
  }
  glutPostRedisplay();
}
void createMenu(void)
{
    menuid = glutCreateMenu(menu);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyboard(unsigned char key, int x, int y)
{
  if(key == 27)
  {
    glutDestroyWindow(window);
    exit(0);
  }
}
