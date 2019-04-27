#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std ; 

double xmax = 400 , xmin = 100 , ymax = 300 , ymin = 100 ;
int k = 0 ;
void init() 
{
    glClear(GL_COLOR_BUFFER_BIT) ;
    glClearColor(0 , 0 , 0 , 0) ;
    glClear( GL_COLOR_BUFFER_BIT ) ;
    glMatrixMode(GL_PROJECTION) ; 
    gluOrtho2D(0 , 640 , 480 , 0 ) ;
}

class points
{
    public:
    double x , y , z ; 
    void setxy(int p , int  q) 
    {
        x = p ; 
        y = q ;
    }
    
    void operator = (points &p)
    {
        x = p.x ; 
        y = p.y ;
        z = p.z ;
    }
    int opcode(double,double);
    void clip(double x1 , double y1 , double x2 , double y2 );
    void dda_line(int,int,int,int);
}p;

points arr[10] ; 

int Top = 8 , Bottom  = 4 , Right  = 2 , Left = 1 ;

bool accept = false, done = false; 
void points::dda_line(int xini,int yini,int xend,int yend)
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
int points::opcode(double x1 , double y1) 
{
       int temp = 0 ;
       
       if(y1 > ymax ) 
       {
            temp = temp|Top ; 
       }
       else if(y1 < ymin )
       {
            temp = temp|Bottom ;  
       }
       else if(x1 > xmax ) 
       {
            temp = temp|Right ; 
       }
       else if(x1 < xmin ) 
       {
            temp = temp|Left ;  
       }
    
       return temp ;
       
}   
 
void points::clip(double x1 , double y1 , double x2 , double y2 )
{   
       accept = false ;
       done = false ;
       int outcode1 = opcode(x1 , y1 ) ;
       int outcode2 = opcode(x2 , y2 ) ;
       do
       {
            if(outcode1 == 0 && outcode2 == 0 ) 
            {
                done = true ; 
                accept = true ; 
            }
            else if(outcode1 & outcode2)
            {
                done = true ; 
                //accept =  false ; 
            }
            else
            {
                int outcode ; 
                if(outcode1)
                    outcode = outcode1 ;
                else
                    outcode = outcode2 ; 
                    
                double x , y  ;
                if(outcode == Top)
                {
                    y = ymax ; 
                    x = x1 + (ymax - y1) *((x2-x1)/(y2-y1)) ;
                }    
                else
                if(outcode == Bottom )
                {
                    y = ymin ;
                    x = x1 + (ymin - y1) * ((x2-x1)/(y2-y1)) ; 
                }        
                else
                if(outcode == Right ) 
                {
                    x = xmax ;
                    y = y1 + ((y2-y1 )/(x2-x1))*(xmax - x1) ;
                }
                else
                if(outcode == Left ) 
                {
                    x = xmin ;
                    y = y1 + ((y2-y1)/(x2-x1))* (xmin - x1 ); 
                }
                
                if(outcode1) 
                {
                    x1 = x ; 
                    y1 = y ; 
                    outcode1 = opcode( x1 , y1 ) ;
                }
                else
                {
                    x2 = x ;
                    y2 = y ;
                    outcode2 = opcode( x2 , y2 ) ;
                }
                
            }
            
       }while(!done) ;
       
       
       if(accept)
       {
            glClear(GL_COLOR_BUFFER_BIT) ;
            glPointSize(1) ;
            glColor3f(1 , 1 , 0 ) ;
            glBegin(GL_POINTS) ;
            	p.dda_line(xmin,ymin,xmax,ymin);
            	p.dda_line(xmax,ymin,xmax,ymax);
            	p.dda_line(xmax,ymax,xmin,ymax);
            	p.dda_line(xmin,ymax,xmin,ymin);
            glEnd() ;
            glFlush() ;
            
            glPointSize(1) ;
            glColor3f(0 , 1 , 1 ) ;
            glBegin(GL_POINTS) ;
            	p.dda_line(x1,y1,x2,y2);
            glEnd() ;
            glFlush() ;
       }  
       else
       {
            //glClear(GL_COLOR_BUFFER_BIT) ;
            glPointSize(1) ;
            glColor3f(1 , 1 , 0) ; 
            glBegin(GL_POINTS) ;
            	p.dda_line(xmin,ymin,xmax,ymin);
            	p.dda_line(xmax,ymin,xmax,ymax);
            	p.dda_line(xmax,ymax,xmin,ymax);
            	p.dda_line(xmin,ymax,xmin,ymin);
            glEnd() ;
            glFlush() ;
       }
           
}

void mouse(int button , int state , int x , int y)
{
    if(k!=2 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) 
    {
        arr[k++].setxy( (double)x , (double)y ) ; 
        glPointSize(8) ;
        glColor3f(1,0,0) ;
        glBegin(GL_POINT) ;
            glVertex2i(x , y) ;
        glEnd() ;
        glFlush() ;
 
 
        if( k > 1 ) 
        {
            glPointSize(1) ;
            glColor3f(0 , 1 , 0) ; 
            glBegin(GL_POINTS) ;
            	p.dda_line(arr[k-2].x,arr[k-2].y,arr[k-1].x,arr[k-1].y);
            glEnd() ;
            glFlush() ; 
        }
        
    }
    if(k == 2 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN ) 
    {
            p.clip(arr[k-2].x ,arr[k-2].y , arr[k-1].x , arr[k-1].y) ; 
            k = 0 ;  
    }
 
}

void display() 
{
    glColor3f( 1 , 0 , 0 ) ;
    glBegin(GL_POINTS) ;
            	p.dda_line(xmin,ymin,xmax,ymin);
            	p.dda_line(xmax,ymin,xmax,ymax);
            	p.dda_line(xmax,ymax,xmin,ymax);
            	p.dda_line(xmin,ymax,xmin,ymin); 
    glEnd() ;
    glFlush() ;
}

int main(int argc , char * argv[]) 
{
    glutInit(&argc , argv ) ; 
    glutInitWindowPosition(0 , 0 ) ;
    glutInitWindowSize( 640 , 480 ) ; 
    glutCreateWindow("Cohen Sutherland line clipping ") ; 
    init() ;   
    glutDisplayFunc(display) ;
    glutMouseFunc(mouse) ;
    glutMainLoop() ;
    return 0 ;  
}
