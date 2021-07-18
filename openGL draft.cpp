#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
float angleAlpha = 0.5f, angleBeta = 0.5f, radius = 15.0f;
int cord_x = -1, cord_y = -1;
int show_axis;

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can’t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void Axis() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}

void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();
	gluLookAt(cos(angleBeta) * sin(angleAlpha) * radius, sin(angleBeta) * radius, cos(angleBeta) * cos(angleAlpha) * radius,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	if (show_axis) Axis();

	// put drawing instructions here

	// End of frame
	glutSwapBuffers();
}

void menu(int value) {
	switch (value) {
	case 1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 3:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 4:
		if (show_axis) show_axis = 0;
		else show_axis = 1;
	default:
		break;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ('w'):
		radius -= 0.3f;
		break;
	case ('s'):
		radius += 0.3f;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void special_keyboard(int key_code, int x, int y) {
	switch (key_code) {
	case GLUT_KEY_LEFT:
		angleAlpha -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:
		angleAlpha += 0.1f;
		break;
	case GLUT_KEY_UP:
		if (angleBeta < M_PI / 2)
			angleBeta += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		if (angleBeta > -M_PI / 2)
			angleBeta -= 0.1f;
		break;
	}

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			cord_x = x;
			cord_y = y;
		}
		else {
			cord_x = -1.0f;
			cord_y = -1.0f;
		}
	}
}

void motion_mouse(int x, int y) {
	if (cord_x >= 0) {
		angleAlpha = (x + cord_x) * 0.01f;
		if (angleBeta < M_PI / 2) {
			angleBeta = (y - cord_y) * 0.01f;
		}
		if (angleBeta > -M_PI / 2) {
			angleBeta = (y - cord_y) * 0.01f;
		}
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM-Fase1");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion_mouse);

	//menu com as opções de desenho
	glutCreateMenu(menu);
	glutAddMenuEntry("Dotted", 1);
	glutAddMenuEntry("Lines", 2);
	glutAddMenuEntry("Filled", 3);
	if (!show_axis) glutAddMenuEntry("Show Axis", 4);
	else glutAddMenuEntry("Hide Axis", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}