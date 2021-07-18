#include <stdlib.h>
#define _USE_MATH_DEFINES
//#define GL_GLEXT_PROTOTYPES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


using namespace std;

float angleAlpha = 0, angleBeta = 0, radiusW = 80;
int cord_x = -1, cord_y = -1;
int show_axis;
int sin_it = 10;
int slices = 40, slices2 = 140;
float rand_sin;
float LAX = 0, LAY = 0, LAZ = 0;

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can�t make a window with zero width).
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
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();
}

void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();
	//angleAlpha += 0.001f;
	gluLookAt(LAX + cos(angleBeta) * sin(angleAlpha) * radiusW, LAY + sin(angleBeta) * radiusW, LAZ + cos(angleBeta) * cos(angleAlpha) * radiusW,
		LAX + 0.0f, LAY + 0.0f, LAZ + 0.0f,
		0.0f, 1.0f, 0.0f);

	if (show_axis) Axis();

	// put drawing instructions here
	float angle_alpha = 6.28 / slices;
	float angle_beta = 3.14 / slices;
	int radius = 15;

	float angle_alpha2 = 6.28 / slices2;
	float angle_beta2 = 3.14 / slices2;
	int radius2 = 27;

	for (int i = 0; i < slices; i++) {
		float beta = -(3.14 / 2) + i * angle_beta;
		float y1 = sin(beta + angle_beta);
		float y2 = sin(beta);
		float pi = 0;
		for (int j = 0; j < slices; j++) {
			pi += angle_alpha;
			float alpha = j * angle_alpha;
			float x1 = cos(beta + angle_beta) * sin(alpha);
			float x2 = cos(beta) * sin(alpha);
			float x3 = cos(beta) * sin(alpha + angle_alpha);
			float x4 = cos(beta + angle_beta) * sin(alpha + angle_alpha);
			float z1 = cos(beta + angle_beta) * cos(alpha);
			float z2 = cos(beta) * cos(alpha);
			float z3 = cos(beta) * cos(alpha + angle_alpha);
			float z4 = cos(beta + angle_beta) * cos(alpha + angle_alpha);

			int time = glutGet(GLUT_ELAPSED_TIME);
			glPushMatrix();
			glRotatef(time * 0.01f, 0, -1, 0);
			//glTranslatef(50, 0, 0);
			glBegin(GL_LINE_STRIP);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glVertex3f(radius * x1 - 2 * sin(alpha) - 5 * sin(pi), radius * y1 - 2 * cos(alpha) - 5 * sin(pi), radius * z1);
			glVertex3f(radius * x2 - 2 * sin(alpha) - 5 * sin(pi), radius * y2 - 2 * cos(alpha) - 5 * sin(pi), radius * z2);
			glVertex3f(radius * x3 - 2 * sin(alpha) - 5 * sin(pi), radius * y2 - 2 * cos(alpha) - 5 * sin(pi), radius * z3);

			glVertex3f(radius * x1 - 2 * sin(alpha) - 5 * sin(pi), radius * y1 - 2 * cos(alpha) - 5 * sin(pi), radius * z1);
			glVertex3f(radius * x3 - 2 * sin(alpha) - 5 * sin(pi), radius * y2 - 2 * cos(alpha) - 5 * sin(pi), radius * z3);
			glVertex3f(radius * x4 - 2 * sin(alpha) - 5 * sin(pi), radius * y1 - 2 * cos(alpha) - 5 * sin(pi), radius * z4);
			glEnd();
			glPopMatrix();
		}
	}

	for (int i = 0; i < slices2; i++) {
		float beta = -(3.14 / 2) + i * angle_beta2;
		float y1 = sin(beta + angle_beta2);
		float y2 = sin(beta);
		float pi = 0;
		for (int j = 0; j < slices2; j++) {
			pi += angle_alpha2;
			float alpha = j * angle_alpha2;
			float x1 = cos(beta + angle_beta2) * sin(alpha);
			float x2 = cos(beta) * sin(alpha);
			float x3 = cos(beta) * sin(alpha + angle_alpha2);
			float x4 = cos(beta + angle_beta2) * sin(alpha + angle_alpha2);
			float z1 = cos(beta + angle_beta2) * cos(alpha);
			float z2 = cos(beta) * cos(alpha);
			float z3 = cos(beta) * cos(alpha + angle_alpha2);
			float z4 = cos(beta + angle_beta2) * cos(alpha + angle_alpha2);

			sin_it++;
			if (sin_it >= 350000) {
				sin_it = 0;
				rand_sin = ((float) rand()) / (float) RAND_MAX;
			}


			if (!(j % 4) && sin(j * i) <= rand_sin) {
				int time = glutGet(GLUT_ELAPSED_TIME);
				glPushMatrix();
				glRotatef(time * 0.01f, 1, 1, 0);
				//glTranslatef(-50, 0, 0);
				glBegin(GL_TRIANGLES);
				//outer
				glColor4f(0.6f, 0.0f, 0.0f, 0.5f);
				glVertex3f(radius2 * x1, radius2 * y1, radius2 * z1);
				glVertex3f(radius2 * x2, radius2 * y2, radius2 * z2);
				glVertex3f(radius2 * x3, radius2 * y2, radius2 * z3);

				glVertex3f(radius2 * x1, radius2 * y1, radius2 * z1);
				glVertex3f(radius2 * x3, radius2 * y2, radius2 * z3);
				glVertex3f(radius2 * x4, radius2 * y1, radius2 * z4);

				//inner
				glColor4f(0.3f, 0.0f, 0.0f, 0.5f);
				glVertex3f(radius2 * x1, radius2 * y1, radius2 * z1);
				glVertex3f(radius2 * x3, radius2 * y2, radius2 * z3);
				glVertex3f(radius2 * x2, radius2 * y2, radius2 * z2);
				

				glVertex3f(radius2 * x1, radius2 * y1, radius2 * z1);
				glVertex3f(radius2 * x4, radius2 * y1, radius2 * z4);
				glVertex3f(radius2 * x3, radius2 * y2, radius2 * z3);
				
				glEnd();
				glPopMatrix();
			}
		}
	}

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
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ('+'):
		radiusW -= 0.3f;
		break;
	case ('-'):
		radiusW += 0.3f;
		break;
	case ('w'):
		LAY += 1;
		break;
	case ('s'):
		LAY -= 1;
		break;
	case ('a'):
		LAX -= 1;
		break;
	case ('d'):
		LAX += 1;
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
		if (angleBeta < 3.14 / 2)
			angleBeta += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		if (angleBeta > -3.14 / 2)
			angleBeta -= 0.1f;
		break;
	case GLUT_KEY_PAGE_UP:
		slices += 10;
		printf("slices %d", slices);
		break;
	case GLUT_KEY_PAGE_DOWN:
		slices -= 10;
		break;
	case GLUT_KEY_HOME:
		slices2 += 10;
		break;
	case GLUT_KEY_END:
		slices2 -= 10;
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
		if (angleBeta < 3.14 / 2) {
			angleBeta = (y - cord_y) * 0.01f;
		}
		if (angleBeta > -3.14 / 2) {
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
	glutCreateWindow("sphere deconstruction");

	// Required callback registry
	glEnable(GL_BLEND);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion_mouse);

	//menu com as op��es de desenho
	glutCreateMenu(menu);
	glutAddMenuEntry("Dotted", 1);
	glutAddMenuEntry("Lines", 2);
	glutAddMenuEntry("Filled", 3);
	glutAddMenuEntry("Show/hide axis", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}