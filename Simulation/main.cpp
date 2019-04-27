#include "1.h"
int main(int argc, char **argv)
{
  srand(time(NULL));
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
  glutInitWindowSize(1280,720);
  window = glutCreateWindow("Kaleidoscope");
  gluOrtho2D(-640,640,-360,360);  //0 , 0 to be on the centre of the screen
  glClearColor(0.01,0.001,0.2,1);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  drawPlane(6,0,0,426);

  k.drawShapes();
  glutMouseFunc(mouse);
  createMenu();
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
