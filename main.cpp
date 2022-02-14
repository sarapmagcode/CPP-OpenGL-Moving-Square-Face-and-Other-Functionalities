#include<GL/glut.h>
#include <GL/freeglut_ext.h>
#include<iostream>

using namespace std;

void display();
void keyboardMonitor(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void mouseMonitor(int button, int state, int x, int y);
void animateShape(int value);

float eye[][2] = {{0.2, 0.1}, {0.13, 0.23}, {0.06, 0.1}};
float x[] = {-1, 1, 1, -1};
float y[] = {-1, -1, 1, 1};
float body[] = {0.33, 0.33};
float mouth[] = {0.05, 0.033};
float moves[] = {0.0, 0.0};
float eye_colors[][3] = {{184, 223, 16}, {184, 223, 16}};
int seconds = 0;
bool checker = false;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Setup Test");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardMonitor);
	glutSpecialFunc(specialKey);
	glutMouseFunc(mouseMonitor);
	glutMainLoop();
	return 0;
}

void keyboardMonitor(unsigned char key, int x, int y) {
	switch (key) {
		case 'W': case 'w': {
			moves[1] += 0.2;
			break;
		}
		case 'S': case 's': {
			moves[1] -= 0.2;
			break;
		}
		case 'A': case 'a': {
			moves[0] -= 0.2;
			break;
		}
		case 'D': case 'd': {
			moves[0] += 0.2;
			break;
		}
		case (char) 27: { // escape key
			checker = true;
			break;
		}
	}
	glutPostRedisplay();
}

void specialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: {
			for (int i = 0; i < 3; i++) {
				eye_colors[0][i] = rand() % 255 + 1;
			}
			break;
		}
		case GLUT_KEY_RIGHT: {
			for (int i = 0; i < 3; i++) {
				eye_colors[1][i] = rand() % 255 + 1;
			}
			break;
		}
	}
	glutPostRedisplay();
}

void mouseMonitor(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON: {
			if (state == GLUT_UP) {
				for (int i = 0; i < 3; i++) {
					eye_colors[0][i] = rand() % 255 + 1;
				}
			}
			break;
		}
		case GLUT_RIGHT_BUTTON: {
			if (state == GLUT_UP) {
				for (int i = 0; i < 3; i++) {
					eye_colors[1][i] = rand() % 255 + 1;
				}
			}
			break;
		}
	}
	glutPostRedisplay();
}

void animateShape(int value) {
	moves[0] += 0.2;
	if (seconds == 5) {
		glutDestroyWindow(glutGetWindow());
	} else {
		glutPostRedisplay();
		seconds++;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	// border around body
	glLineWidth(4.0);
	glColor3ub(184, 223, 16);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex2f(body[0] * x[i] + moves[0], body[1] * y[i] + moves[1]);
	}
	glEnd();
	
	// square body
	glColor3f(0.10, 0.0, 0.2);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2f(body[0] * x[i] + moves[0], body[1] * y[i] + moves[1]);
	}
	glEnd();
	
	// mouth
	glColor3ub(184, 223, 16);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 2; i++) {
		glVertex2f(mouth[0] * x[i] + moves[0], mouth[1] * y[i] + moves[1]);
	}
	glEnd();
	
	// left and right eyes
	glBegin(GL_TRIANGLES);
	for (int rep = 0; rep < 2; rep++) {
		int temp = (rep == 0 ? -1 : 1);
		glColor3ub(eye_colors[rep][0], eye_colors[rep][1], eye_colors[rep][2]);
		for (int i = 0; i < 3; i++) {
			glVertex2f(eye[i][0] * temp + moves[0], eye[i][1] + moves[1]);
		}
	}
	glEnd();
	glFlush();
	
	if (checker) { // move 5 times (1 second each), then terminate
		glutTimerFunc(1000, animateShape, 1);
	}
}