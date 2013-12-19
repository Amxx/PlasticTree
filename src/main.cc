#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <GL/glut.h>

#include "geometry/vec3.hh"
#include "geometry/base3.hh"
#include "objects/tree.hh"



static branch 	*tree[9];

static bbox			wall;

static double		distance_wall		= 10.;
static double		distance_camera	= -15.;
static double		phi							= -10;
static double		theta						= 30;

static bool			colision				= true;

static int 			mouse_status;
static int 			mouse_x;
static int 			mouse_y;



void display()
{
	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
	glTranslatef(0., 0., distance_camera);
	glRotatef(theta, 1.0, 0.0, 0.0);
	glRotatef(phi, 0.0, 1.0, 0.0);
	
	glClearColor(0.6, 0.8, 1.0 , 1.0);
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	
	for (int i=0; i<9; ++i)
		if (tree[i])
			tree[i]->display(vec3(	.5 + .2 * cos(1 + i),
															.3 + .2 * cos(1 + i),
															.2 + .2 * cos(1 + i) ));
	wall.display(vec3(.4, .4, .4), 0); //GL_LINE 
				
	glutSwapBuffers();
}

void reshape(int w,int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90., (float)w/(float)h, 0.1, 100.0); 
}

void idle(void)
{
	glutPostRedisplay();
}

void edited()
{
	wall = bbox(vec3(distance_wall - .5, -8., -8.), vec3(distance_wall + .5, 8., 8.));
	
	for (int i=0; i<9; ++i)
		if (tree[i]) 
			tree[i]->reset();
		
	if (colision)
		for (int i=0; i<9; ++i)
			if (tree[i]) 
			{
				branch::colid(tree[i], wall);
				for (int j=i+1; j<9; ++j)
					if (tree[j])
						branch::colid(tree[i], tree[j]);
			}
}









void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{		
		case 27: exit(0);
		case 32: colision = !colision; edited(); break;
		default: break;
	}
	idle();
}
void Special(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:		distance_wall 	-= .1; 	break;
		case GLUT_KEY_RIGHT:	distance_wall 	+= .1;	break;
		case GLUT_KEY_UP:			distance_camera += .1;	break;
		case GLUT_KEY_DOWN:		distance_camera -= .1;	break;
		default: break;
	}
	edited();
}
void Mouse(int button, int state, int x, int y)
{
	mouse_status = (button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN);
	mouse_x = x;
	mouse_y = y;
}
void Motion(int x, int y)
{
	if (mouse_status)
	{
		phi			+= 0.2 * (x - mouse_x);
		theta 	+= 0.2 * (y - mouse_y);
		mouse_x = x;
		mouse_y = y;
		glutPostRedisplay();
	}
}










int main(int argc, char* argv[])
{
  
	srand(time(NULL));
	
	for (int i=0; i<3; ++i)
		for (int j=0; j<3; ++j)
			{
				tree[i*3+j] = branch::make_branch(6);
				tree[i*3+j]->move(	1.0, //+((i==1)?0.3:0.0)+((j==1)?0.3:0.0),
														vec3(4*(i-1), -8., 4*(j-1)),
														base3(vec3(0., 1., 0.), vec3(0., 0., 1.), vec3(1., 0., 0.))
													);
														
			}
	edited();
				
				
	glutInit(&argc,argv);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(50,50);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow("PlasticTree");
  
	
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	
	glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
	
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
	
  return(0);
}

