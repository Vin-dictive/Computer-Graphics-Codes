
#include <GL/glut.h>
#include <math.h>
class kcurve{
public:
	GLfloat oldx,oldy;
	kcurve()
	{
		oldx=100;
		oldy=300;
	}
	void drawkoch(GLfloat dir,GLfloat len,GLint iter);
	void dda_line(int,int,int,int);
}k;
void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
}
void kcurve::dda_line(int xini,int yini,int xend,int yend)
{
    glPointSize(1.0);
    double dx=(xend-xini);
    double dy=(yend-yini);
    double steps;
    float xInc,yInc,x=xini,y=yini;
    steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
    xInc=dx/(float)steps;
    yInc=dy/(float)steps;
    glLineWidth(10.0);
    glVertex2f(x,y);
    int k;
    for(k=0;k<steps;k++)
    {
      x+=xInc;
      y+=yInc;
     glVertex2f(x,y);
  }
}
void kcurve::drawkoch(GLfloat dir,GLfloat len,GLint iter) {
	GLdouble dirRad = 0.0174533 * dir;
	GLfloat newX = oldx + len * cos(dirRad);
	GLfloat newY = oldy + len * sin(dirRad);
	if (iter==0) {
		k.dda_line(oldx,oldy,newX,newY);
		oldx = newX;
		oldy = newY;
	}
	else {
		iter--;
		drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
		dir -= 120.0;
		drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
	}
}

void mydisplay(){
	 glClear( GL_COLOR_BUFFER_BIT );
	 glBegin(GL_POINTS);
	 glColor3f(0.0, 0.0, 1.0); 
	 k.drawkoch(0.0,10,3);
	 k.drawkoch(-120.0,10,3);
	 k.drawkoch(120.0,10,3);
	 glEnd();
	 glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Koch Snowflake");
	init();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
