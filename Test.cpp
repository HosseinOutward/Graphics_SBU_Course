#include <vector>
#include "GLUT\freeglut.h"
#include "math.h"
#include "cstdio"
#include <iostream>
#include <cmath>
#include <vector>

int xrr = 0, yrr = 0;
double tick = 0;
bool autoAnim = false;
double steps = 0.025;

void arrow(float raito) {
	glPushMatrix();
	glScalef(raito, raito, raito);
	glScalef(0.65, 1, 0.65);
	glBegin(GL_TRIANGLES);

	glColor3f(1, 0, 0.0);
	glNormal3f(0.0, 1.0, 0);    glVertex3f(0.0, 1.0, 0);
	glNormal3f(-1.0, -1, -1.0); glVertex3f(-0.5, 0.5, -0.5);
	glNormal3f(-1.0, -1, 1.0);  glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(0.0, 1.0, 0.0);
	glNormal3f(0.0, 1.0, 0);    glVertex3f(0.0, 1.0, 0);
	glNormal3f(-1.0, -1, 1.0);  glVertex3f(-0.5, 0.5, 0.5);
	glNormal3f(1.0, -1, 1.0);   glVertex3f(0.5, 0.5, 0.5);

	glColor3f(0.0, 0, 1);
	glNormal3f(0.0, 1.0, 0);    glVertex3f(0.0, 1.0, 0);
	glNormal3f(-1.0, -1, -1.0); glVertex3f(0.5, 0.5, 0.5);
	glNormal3f(-1.0, -1, 1.0);  glVertex3f(0.5, 0.5, -0.5);

	glColor3f(1, 1.0, 0.0);
	glNormal3f(0.0, 1.0, 0);    glVertex3f(0.0, 1.0, 0);
	glNormal3f(-1.0, -1, -1.0); glVertex3f(0.5, 0.5, -0.5);
	glNormal3f(-1.0, -1, 1.0);  glVertex3f(-0.5, 0.5, -0.5);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(raito, raito, raito);
	glScalef(0.40, 0.9, 0.40);
	glBegin(GL_QUADS); // telling opengl what object is going to be described by vertex below
					   // GL_QUADS: creats Quadrilaterals (every 4 vertex turn into one Quadrilateral)

	glNormal3f(-1.0, -1.0, 1.6); glColor3f(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glNormal3f(-1.0, 1.0, 1.6);  glColor3f(1.0, 0.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glNormal3f(1.0, 1.0, 1.6);   glColor3f(1.0, 0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	glNormal3f(1.0, -1.0, 1.6);  glColor3f(1.0, 0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);

	glNormal3f(-1.0, -1.0, -1.6); glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
	glNormal3f(-1.0, 1.0, -1.6);  glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
	glNormal3f(1.0, 1.0, -1.6);   glColor3f(0.0, 1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
	glNormal3f(1.0, -1.0, -1.6);  glColor3f(0.0, 1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);

	glNormal3f(1.6, -1.0, -1.0); glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, -0.5, -0.5);
	glNormal3f(1.6, -1.0, 1.0);  glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
	glNormal3f(1.6, 1.0, 1.0);   glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
	glNormal3f(1.6, 1.0, -1.0);  glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, 0.5, -0.5);

	glNormal3f(-1.6, -1.0, -1.0); glColor3f(1.0, 0.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);
	glNormal3f(-1.6, -1.0, 1.0);  glColor3f(1.0, 0.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
	glNormal3f(-1.6, 1.0, 1.0);   glColor3f(1.0, 0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
	glNormal3f(-1.6, 1.0, -1.0);  glColor3f(1.0, 0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);

	glNormal3f(-1.0, 1.6, -1.0); glColor3f(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
	glNormal3f(-1.0, 1.6, 1.0);  glColor3f(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glNormal3f(1.0, 1.6, 1.0);   glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	glNormal3f(1.0, 1.6, -1.0);  glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);

	glNormal3f(-1.0, -1.6, -1.0); glColor3f(0.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);
	glNormal3f(-1.0, -1.6, 1.0);  glColor3f(0.0, 1.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
	glNormal3f(1.0, -1.6, 1.0);   glColor3f(0.0, 1.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
	glNormal3f(1.0, -1.6, -1.0);  glColor3f(0.0, 1.0, 1.0); glVertex3f(0.5, -0.5, -0.5);

	glEnd(); // telling opengl this is the end of glBegin
	glPopMatrix();
}

float getPt(float n2, float n1, float perc) { return n1 + ((n2 - n1) * perc); }

double* bezier(double** points, float t, int size) {
	if (size == 1)
		return points[0];

	const int new_size = size - 1;
	double** next_points = new double*[new_size];
	for (int i = 0; i < new_size; i += 1)
	{
		next_points[i] = new double[3];
		next_points[i][0] = getPt(points[i + 1][0], points[i][0], t);
		next_points[i][1] = getPt(points[i + 1][1], points[i][1], t);
		next_points[i][2] = getPt(points[i + 1][2], points[i][2], t);
	}
	return bezier(next_points, t, new_size);
}
double* bezier(double points_temp[][3], float t, int size) {
	double** points = new double*[size];
	for (int i = 0; i < size; i += 1) points[i] = points_temp[i];
	return bezier(points, t, size);
}

double dotpro(double a[3], double b[3], int i) {
	return a[i] * b[i] + a[(i + 1) % 3] * b[(i + 1) % 3];
}
double crosspro(double a[3], double b[3], int i) {
	return a[i] * b[(i + 1) % 3] - a[(i + 1) % 3] * b[i];
}
double norm(double a[3], int i) {
	if (i == -1) return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	return sqrt(a[i] * a[i] + a[(i + 1) % 3] * a[(i + 1) % 3]);
}

void rotate_to_align(double ret[], double det[]) {
	double vect_B[3] = { -0.001,1,0 };
	double vect_A[3] = { det[0] - ret[0], det[1] - ret[1], det[2] - ret[2] };

	double x_y_dot = acos(dotpro(vect_A, vect_B, 0) / (norm(vect_A, 0)*norm(vect_B, 0)));
	double y_z_dot = acos(dotpro(vect_A, vect_B, 1) / (norm(vect_A, 1)*norm(vect_B, 1)));
	double x_z_dot = acos(dotpro(vect_A, vect_B, 2) / (norm(vect_A, 2)*norm(vect_B, 2)));

	if (dotpro(vect_A, vect_B, 0) * crosspro(vect_A, vect_B, 0) >= 0.5) x_y_dot *= -1;
	if (dotpro(vect_A, vect_B, 1) * crosspro(vect_A, vect_B, 1) <= 1) y_z_dot *= -1;
	if (dotpro(vect_A, vect_B, 2) * crosspro(vect_A, vect_B, 2) >= 0.5) x_z_dot *= -1;

	//glRotatef(54.75, 1, 0, -1);
	//glRotatef(y_z_dot * 180 / 3.1416, 1, 0, 0);
	glRotatef(x_z_dot * 180 / 3.1416, 0, 1, 0);
	glRotatef(x_y_dot * 180 / 3.1416, 0, 0, 1);
}

double s(std::vector<double> arc, double t) {
	double min_v = t; double new_v; int i;
	for (i = 1; i*steps < 1; i += 1) {
		new_v = abs(t - arc[i] / arc.back());
		if (new_v < min_v) min_v = new_v;
		else break;
	}
	if (i != 0) i--;
	if (i == 0) return steps / (arc[1] / arc.back())*t;

	if (abs(t - arc[i + 1] / arc.back()) < abs(t - arc[i - 1] / arc.back()))
		return i * steps + steps / ((arc[i + 1] - arc[i]) / arc.back())*(t - arc[i] / arc.back());
	else
		return (i - 1)*steps + steps / ((arc[i] - arc[i - 1]) / arc.back())*(t - arc[i - 1] / arc.back());

}

double easeinout(double t) { return sin(t*3.1416 - 3.1416 / 2) / 2 + 0.5; }

void render(void) // the function that will run to display items
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // wipe the drawing surface's color and depth buffer
														// GL_DEPTH_BUFFER_BIT: buffer to store how close object's pixels are releative to the viewer
														// GL_COLOR_BUFFER_BIT: buffer to store what color the object's pixels are

	//...
	glPushMatrix();
	glRotatef(xrr, 1, 0, 0); // function to rotate the matrix by xrr degree in x axis 
	glRotatef(yrr, 0, 1, 0);
	glScalef(0.6, 0.6, 0.6);

	double points[][3] = { {1,-1.5,-1},{-1,-1,-1},{-1,1,-0.5},{1,1,0},{1,-1,0.5},{-1,-1,1},{-1,1,1.5} };

	glBegin(GL_LINES);
	double* bez = bezier(points, 0, sizeof(points) / sizeof(points[0]));
	double* bez2;
	std::vector<double> arc_table;
	arc_table.push_back(0);
	for (double t = 0; t < 1; t += steps)
	{
		glVertex3f(bez[0], bez[1], bez[2]);
		bez2 = bezier(points, t + steps, sizeof(points) / sizeof(points[0]));
		glVertex3f(bez2[0], bez2[1], bez2[2]);

		double dif[3] = { bez2[0] - bez[0], bez2[1] - bez[1], bez2[2] - bez[2] };
		arc_table.push_back(arc_table.back() + norm(dif, -1));

		bez = bez2;
	}
	glEnd();

	glPushMatrix();
	bez = bezier(points, s(arc_table, easeinout(tick)), sizeof(points) / sizeof(points[0]));
	glTranslatef(bez[0], bez[1], bez[2]);
	glPushMatrix();
	rotate_to_align(bez, bezier(points, s(arc_table, easeinout(tick + 0.01)), sizeof(points) / sizeof(points[0])));
	arrow(0.2);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	//...
	glutSwapBuffers(); // swap the back buffer (which has been prepared) with front buffer, telling gpu to write the new frame

}

void reshape(int, int) {

}

void keyboard(unsigned char key, int, int) {
	switch (key) {
	case 32:
		if (autoAnim) { autoAnim = false; }
		else { autoAnim = true; }
		break;
	case 'W':
	case 'w':
		xrr -= 5;
		autoAnim = false;
		break;

	case 'A':
	case 'a':
		yrr -= 5;
		autoAnim = false;
		break;

	case 'S':
	case 's':
		xrr += 5;
		autoAnim = false;
		break;

	case 'D':
	case 'd':
		yrr += 5;
		autoAnim = false;
		break;
	}
	xrr %= 360, yrr %= 360;
}

void mouseMove(int x, int y) {
	double width = glutGet(GLUT_WINDOW_WIDTH);
	double height = glutGet(GLUT_WINDOW_HEIGHT);
	float fx = (x - width / 2) / width, fy = (-y + height / 2) / height;
	GLfloat lightPosition[] = { fx, fy, -2, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

}

void delay(int) {}
void idle(void) {
	if (autoAnim) {
		xrr += 1, yrr += 1;
	}
	tick += 0.001;
	tick -= (int)tick;
	glutPostRedisplay(); // re-calling the display (render in this case) function and remake the buffer
	glutTimerFunc(1000 / 60, delay, 0); // wait 1000/60 ms to (re-)call the function (limit to at most 60 fps)
}

void init() {
	// changing aspect ratio and settinf matrix mode
	double width = glutGet(GLUT_WINDOW_WIDTH);
	double height = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	float aspect = (float)width / (float)height;

	// initilizing camera 
	gluPerspective(60.0, aspect, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -3);
	glEnable(GL_DEPTH_TEST);
}

void initLighting()
{
	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Set lighting intensity and color
	GLfloat ambientLight[] = { 0.3, 0.2, 0.1, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	GLfloat diffuseLight[] = { 0.5, 0.5, 0.5, 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	GLfloat specularLight[] = { 0.3, 0.2, 0.1, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glMaterialf(GL_FRONT, GL_SHININESS, 1);

	// Set the light position
	GLfloat lightPosition[] = { 0.5, 0.1, -1, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// Set lighting intensity and color
	GLfloat ambientLight1[] = { 0.3, 0.2, 0.1, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	GLfloat diffuseLight1[] = { 0.5, 0.5, 0.5, 0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	GLfloat specularLight1[] = { 0.3, 0.2, 0.1, 1.0 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
	glMaterialf(GL_FRONT, GL_SHININESS, 1);
	GLfloat lightPosition1[] = { 0.5, 0.1, 1, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv); // initilize OpenGL GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // enable double buffering and RGBA color spectrum
	glutInitWindowPosition(100, 100); // set the top left corner point of window that's to be displayed
	glutInitWindowSize(1200, 800); // set the size for window that's to be displayed
	glutCreateWindow("app"); // set the name for window

	init(); // custome initilizing
	initLighting();

	glutDisplayFunc(render); // set the function to be used to display items
	glutReshapeFunc(reshape); // set the fun. to be called when window size changes
	glutMotionFunc(mouseMove); // set the fun. to be called when mouse is clicked
	glutKeyboardFunc(keyboard); // set the fun. to be called when a key is pressed
	glutIdleFunc(idle); // sets the fun. that is called when no events are happening

	glutMainLoop(); // starts glut main loop (which responds to events and etc.)
}
