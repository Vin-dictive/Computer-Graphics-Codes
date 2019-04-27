#include <math.h>
#include <GL/glut.h>
int flag;
struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
};
class Point {
public:
	GLint x;
	GLint y;
	void draw_dda(Point,Point);
	void floodFill(GLint x, GLint y, Color oldColor, Color newColor);
	void draw(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
}p;

void Point::draw_dda(Point p1, Point p2) {
	GLfloat dx = p2.x - p1.x;
	GLfloat dy = p2.y - p1.y;

	GLfloat x1 = p1.x;
	GLfloat y1 = p1.y;

	GLfloat step = 0;

	if(abs(dx) > abs(dy)) {
		step = abs(dx);
	} else {
		step = abs(dy);
	}

	GLfloat xInc = dx/step;
	GLfloat yInc = dy/step;

	for(float i = 1; i <= step; i++) {
		glVertex2i(x1, y1);
		x1 += xInc;
		y1 += yInc;
	}
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
	//glRotatef(45,0,0,1);
}

Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void Point::floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
	Color color;
	color = getPixelColor(x, y);

	if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
	{
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
	}
	return;
}

void onMouseClick(int button, int state, int x, int y)
{
	Color newColor = {1.0f, 0.0f, 0.0f};
	Color oldColor = {1.0f, 1.0f, 1.0f};
}

void Point::draw(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4) {
	Point p1 = {x1, y1}, // bottom-right
		p2 = {x2, y2}, // bottom-left
		p3 = {x3, y3}, // top-right
		p4 = {x4, y4}; // top-left

	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		draw_dda(p1, p2);
		draw_dda(p2, p3);
		draw_dda(p3, p4);
		draw_dda(p4, p1);
	glEnd();
	glFlush();

		if(flag==0)
    {
        Color newColor = {0.0f, 0.0f, 0.0f};
	Color oldColor = {1.0f, 1.0f, 1.0f};
        floodFill((x1+x3)/2,(y1+y3)/2, oldColor, newColor);
    }
    flag=flag^1;

}

void display()
{

	GLint x,y;
	int x1=200,y1=200;
	for(int i=0 ; i<8 ; i++)
	{
	    x=x1;
	    y=y1;
		for( int j=0 ; j<8 ; j++)
		{

			p.draw(x,y,x+18,y+18,x+36,y,x+18,y-18);
			x+=18;
			y-=18;
		}
		x1+=18;
		y1+=18;
        flag=flag^1;
	}

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}
