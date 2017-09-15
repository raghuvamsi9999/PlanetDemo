
#include <windows.h>  // This header file will be needed for some windows compilers
#include <GL/glu.h>
#include <GL/glut.h>  // glut (gl utility toolkit) basic windows functions, keyboard, mouse.
#include <stdlib.h>   // standard library (set of standard C functions
#include <math.h>     // Math library (Higher math functions )
#include<vector>
#include<iostream>

using namespace std;
GLsizei MOUSEx = 0, MOUSEy = 0;
GLfloat BLUE[3] = { 0,0,1 };
GLfloat GREEN[3] = { 0, 1, 0 };
GLfloat point = 5;
enum DrawingOptions {
	LINES, RECTANGLES, CIRCLES, POLYGON, TRANSFORM, ERASE, EXIT
};
int window_1, window_2, window_3, window_4;
//static int view_state = 0, light_state = 0;
GLfloat xRotated, yRotated, zRotated;
int shape, ch;
GLfloat obSize = 1.0;
GLint tmp[3] = { 0, 0, 0 };

GLint window_size[2] = { 800, 600 };

float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 10.0f, z = 20.0f;// the key states. These variables will be zero
						   //when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
float radious = -10;
int w1, h1;
float ratio;

//coordinates for HALF PRISM
GLfloat points[5][3] = { { 1,0,0 },{ 0,3,0 },{ -1,0,0 },{ 0,0,1 },{ 0,0,0 } };

//coordinates for neck
GLfloat points2[4][3] = { { 0.5,4 },{ 0.5,5 },{ -0.5,5 },{ -0.5,4 } };

//coordinates for body
GLfloat points3[4][3] = { { 2,-3.4 },{ 2,4 },{ -2,4 },{ -2,-4 } };

//coordinates for character's left leg
GLfloat points4[4][3] = { { 2,-7 },{ 2,0 },{ 1,0 },{ -0.005, -7 } };


void pressKey(int key, int xx, int yy)
{
	switch (key) {
	case GLUT_KEY_LEFT: angle += -0.1f; break;
	case GLUT_KEY_RIGHT: angle += 0.1f; break;
	case GLUT_KEY_UP: radious += 1.0f; break;
	case GLUT_KEY_DOWN: radious += -1.0f; break;
	}
	x = radious*sin(angle);
	z = radious*-cos(angle);
	cout << "X:" << x << " Z:" << z << " R:" << radious << endl;
}

//Drawing a half prism for Window1
void drawCubeSphere()
{

static float yangle = 0.0f;
yangle+=0.3f;

	//Draw Sphere
	glColor3d(0, 1, 1);
	glTranslatef(0.0f, 0.0f, -10.0f);
	glutSolidSphere(5.0f, 100, 100);
	
	//Draw Cube
	glColor3f(1.0f, 0.0f, 0.0f);
	glRotatef(yangle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -30.0f);
	glutSolidCube(1.0f);

	glutPostRedisplay();
}
void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);  // When screen cleared, use black.
	glShadeModel(GL_SMOOTH);  

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0f,ratio,0.1f,100.0f);
glMatrixMode(GL_MODELVIEW);

}
void reshape_1(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	ratio = 1.0f * w / h;
	gluPerspective(45, ratio, 0.1, 1000);
}
void display_Character(void)
{
	char *p;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Clear the screen
   
glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Clear the model matrix

	gluLookAt(0.0, 0.0, radious,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	//drawHprimid1();//Draws half prism

	//Drawing character
	drawCubeSphere();
	glutSwapBuffers();
}


// Main program
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window_size[0], window_size[1]);
	init();
	//glutTimerFunc(10, TimeEvent, 1);

	//orthographic view
	glutInitWindowPosition(100, 0);
	window_1 = glutCreateWindow(argv[0]);
	glutSetWindowTitle("Character");
	glutDisplayFunc(display_Character);
	glutReshapeFunc(reshape_1);
	//glutKeyboardFunc(keyboard);
	//glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	// here are the new entries
	/*glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);*/
	glEnable(GL_DEPTH_TEST);   // Check depth when rendering
	
	glutMainLoop();
	return 0;
}