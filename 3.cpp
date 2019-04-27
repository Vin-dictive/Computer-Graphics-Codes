#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;
const int MAX=10;
int n=0;
class transformation
{
public:
	float sx,sy,tx,ty;
	float temp[MAX][3] , tran[MAX][3] , res[MAX][3];
	float theta;
	int a;
	void loadidentity();
	void multiply();
	void translate();
	void scale();
	void rotate();
	void draw();
	void shear();
	void dda_line(int,int,int,int);
}p;
void transformation::loadidentity()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			if(i!=j)
				tran[i][j]=0;
			else
				tran[i][j]=1;
		}
}
void transformation::dda_line(int xini,int yini,int xend,int yend)
{
	glPointSize(1.0);
	double dx=(xend-xini);
	double dy=(yend-yini);
	double steps;
	float xInc,yInc,x=xini,y=yini;
	steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  	xInc=dx/(float)steps;
  	yInc=dy/(float)steps;
	//glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(10.0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
  	int k;
  	for(k=0;k<steps;k++)
  	{
  	  x+=xInc;
  	  y+=yInc;
   	 glVertex2f(x,y);
  }
  glEnd();
  glFlush();
}
void transformation::multiply()
{
	for(int i=0;i<n;i++)
		for( int j=0;j<3;j++)
			res[i][j]=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				res[i][j]+=(temp[i][k] * tran[k][j]);
}
void transformation::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1);
	glColor3f(0,1,0);
	glBegin(GL_POINTS);
	for(int i=0;i<n-1;i++)
		p.dda_line(temp[i][0],temp[i][1],temp[i+1][0],temp[i+1][1]);
		//glVertex3f(temp[i][0] , temp[i][1] , temp[i][2]);
		p.dda_line(temp[n-1][0],temp[n-1][1],temp[0][0],temp[0][1]);
	glEnd();
	glFlush();
	glPointSize(1);
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
	for(int i=0;i<n-1;i++)
		p.dda_line(res[i][0],res[i][1],res[i+1][0],res[i+1][1]);
		//glVertex3f(res[i][0] , res[i][1] , res[i][2]);
		p.dda_line(res[n-1][0],res[n-1][1],res[0][0],res[0][1]);
	glEnd();
	glFlush();
}

void transformation::translate()
{
	cout<<"\nEnter the translation factor for x : ";
	cin>>tx;
	cout<<"\nEnter the translation factor for y : ";
	cin>>ty;
	for(int i=0;i<n;i++)
	{
		res[i][0] = temp[i][0]+tx;
		res[i][1] = temp[i][1]+ty;
	}
	draw();
}

void transformation::scale()
{
	cout<<"\nEnter the scaling factor for x : ";
	cin>>sx;
	cout<<"\nEnter the scaling factor for y : ";
	cin>>sy;
	loadidentity();
	tran[0][0] = sx;
	tran[1][1] = sy;
	multiply();
	draw();
}
void transformation::shear()
{
  int t;
  cout<<"choose from various options :"<<"\n";
  cout<<"1. for x-shear "<<"\n";
  cout<<"2. for y-shear "<<"\n";
  cin>>t;
  if(t==1)
  {
     cout<<"enter the x-shear factor"<<"\n";
     cin>>a;
    for(int i=0;i<n;i++)
    {
       res[i][0]=temp[i][0]+temp[i][1]*a;
       res[i][1]=temp[i][1];
       res[i][2]=temp[i][2];
    }
  }
  else
  {
    cout<<"enter the y-shear factor"<<"\n";
     cin>>a;
    for(int i=0;i<n;i++)
    {
       res[i][0]=temp[i][0];
       res[i][1]=temp[i][1]+temp[i][0]*a;
       res[i][2]=temp[i][2];
    }
  }
  draw();
}
void transformation::rotate()
{
	int clk;
	cout<<"\nEnter the angle of rotation : ";
	cin>>theta;
	cout<<"\nEnter 0 for ClockWise Rotation and 1 for anticlockwise Rotation :";
	cin>>clk;
	theta = (3.14/180)*theta;
	this->loadidentity();
	if(clk==0)
	{
	this->tran[0][0] = cos(theta);
	this->tran[0][1] = sin(theta);
	this->tran[1][0] = -sin(theta);
	this->tran[1][1] = cos(theta);
	}else
	{
	this->tran[0][0] = cos(theta);
	this->tran[0][1] = -sin(theta);
	this->tran[1][0] = sin(theta);
	this->tran[1][1] = cos(theta);
	}
	multiply();
	draw();
}
void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glColor3f(0.0,1.0,0.0);
	gluOrtho2D(0,640,480,0);
	glFlush();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	cout<<"\nChoose from the following options";
	cout<<"\nPress 't' : Translate\nPress 's' : Scaling\nPress 'r' : Rotation :\n";
}
void keyboard(unsigned char key , int x , int y)
{
	if(key=='t')
		p.translate();
	else if(key == 's')
		p.scale();
	else if(key == 'r')
		p.rotate();
	else if(key == 'S')
		p.shear();
}
void mymouse(int button , int state , int x , int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		p.temp[n][0] = (float)x;
		p.temp[n][1] = (float)y;
		p.temp[n][2] = 1;
		glPointSize(1);
		glBegin(GL_POINTS);
			glVertex2f(x,y);
		glEnd();
		n++;
		if(n>=2)
		{
			glPointSize(1);
			glColor3f(0,1,0);
			glBegin(GL_LINE_STRIP);
				glVertex2f(p.temp[n-2][0] , p.temp[n-2][1]);
				glVertex2f(p.temp[n-1][0] , p.temp[n-1][1]);
			glEnd();
		}
		glFlush();
	}
	else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		glPointSize(1);
		glColor3f(0,1,0);
		glBegin(GL_LINE_STRIP);
			glVertex2i(p.temp[n-1][0] , p.temp[n-1][1]);
			glVertex2i(p.temp[0][0] , p.temp[0][1]);
		glEnd();
		glFlush();
	}
}
int main(int argc , char *argv[])
{
	glutInit(&argc , argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("2-D transformation");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mymouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
