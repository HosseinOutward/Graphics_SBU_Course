#include "GLUT\freeglut.h"
#include "math.h"
#include "cstdio"
#include <iostream>
#include <cmath>

int xrr = 0, yrr = 0;
int xlr = 0, ylr = 0;
double r = 0.25;
int curr_box = 0;
GLuint earthTextureData;
void materialColorSet(GLfloat r, GLfloat g, GLfloat b);

GLuint LoadTexture(const char* imagepath)
{
	printf("Reading image %s\n", imagepath);
	unsigned int outWidth = -1;
	unsigned int outHeight = -1;
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;

	FILE* file;
	if (errno_t err = fopen_s(&file, imagepath, "rb") != 0) {
		perror("Can't Open file");
		return 0;
	}

	// If less than 54 byes are read, problem
	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		return NULL;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return NULL;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    return NULL; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    return NULL; }

	// Read the information about the image
	dataPos = *(int*)&(header[0x0A]);
	outWidth = *(int*)&(header[0x12]);
	outHeight = *(int*)&(header[0x16]);
	imageSize = *(int*)&(header[0x22]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = outWidth * outHeight * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	// Read the actual data from the file into the buffer
	unsigned char* data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file wan be closed
	fclose(file);

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, outWidth, outHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (GLvoid*)data);

	return tex;
}

float* return_matrix(float x, float y, float z) {
	GLfloat* a = new GLfloat[16]();
	glGetFloatv(GL_MODELVIEW_MATRIX, a);

	float b[4] = { x,y,z,1 };
	float* c = new float[3]();
	for (int i = 0; i < 3; i++) {
		c[i] = 0;
		for (int j = 0; j < 4; j++)
			c[i] += (a[i * 4 + j] * b[j]);
	}
	return c;
}

void sphere() {
	GLUquadric* q = gluNewQuadric();
	gluQuadricTexture(q, true);
	gluSphere(q, 1, 50, 50);
}

void cube() {
	glBegin(GL_QUADS); // telling opengl what object is going to be described by vertex below
					   // GL_QUADS: creats Quadrilaterals (every 4 vertex turn into one Quadrilateral)

	glNormal3f(-1.0, -1.0, 1.6); glColor3f(1.0, 0.0, 0.0); glVertex3f(0, 0, 1);
	glNormal3f(-1.0, 1.0, 1.6);  glColor3f(1.0, 0.0, 0.0); glVertex3f(0, 1, 1);
	glNormal3f(1.0, 1.0, 1.6);   glColor3f(1.0, 0.0, 0.0); glVertex3f(1, 1, 1);
	glNormal3f(1.0, -1.0, 1.6);  glColor3f(1.0, 0.0, 0.0); glVertex3f(1, 0, 1);

	glNormal3f(-1.0, -1.0, -1.6); glColor3f(0.0, 1.0, 0.0); glVertex3f(0, 0, 0);
	glNormal3f(-1.0, 1.0, -1.6);  glColor3f(0.0, 1.0, 0.0); glVertex3f(0, 1, 0);
	glNormal3f(1.0, 1.0, -1.6);   glColor3f(0.0, 1.0, 0.0); glVertex3f(1, 1, 0);
	glNormal3f(1.0, -1.0, -1.6);  glColor3f(0.0, 1.0, 0.0); glVertex3f(1, 0, 0);

	glNormal3f(1.6, -1.0, -1.0); glColor3f(0.0, 0.0, 1.0); glVertex3f(1, 0, 0);
	glNormal3f(1.6, -1.0, 1.0);  glColor3f(0.0, 0.0, 1.0); glVertex3f(1, 0, 1);
	glNormal3f(1.6, 1.0, 1.0);   glColor3f(0.0, 0.0, 1.0); glVertex3f(1, 1, 1);
	glNormal3f(1.6, 1.0, -1.0);  glColor3f(0.0, 0.0, 1.0); glVertex3f(1, 1, 0);

	glNormal3f(-1.6, -1.0, -1.0); glColor3f(1.0, 0.0, 1.0); glVertex3f(0, 0, 0);
	glNormal3f(-1.6, -1.0, 1.0);  glColor3f(1.0, 0.0, 1.0); glVertex3f(0, 0, 1);
	glNormal3f(-1.6, 1.0, 1.0);   glColor3f(1.0, 0.0, 1.0); glVertex3f(0, 1, 1);
	glNormal3f(-1.6, 1.0, -1.0);  glColor3f(1.0, 0.0, 1.0); glVertex3f(0, 1, 0);

	glNormal3f(-1.0, 1.6, -1.0); glColor3f(1.0, 1.0, 0.0); glVertex3f(0, 1, 0);
	glNormal3f(-1.0, 1.6, 1.0);  glColor3f(1.0, 1.0, 0.0); glVertex3f(0, 1, 1);
	glNormal3f(1.0, 1.6, 1.0);   glColor3f(1.0, 1.0, 0.0); glVertex3f(1, 1, 1);
	glNormal3f(1.0, 1.6, -1.0);  glColor3f(1.0, 1.0, 0.0); glVertex3f(1, 1, 0);

	glNormal3f(-1.0, -1.6, -1.0); glColor3f(0.0, 1.0, 1.0); glVertex3f(0, 0, 0);
	glNormal3f(-1.0, -1.6, 1.0);  glColor3f(0.0, 1.0, 1.0); glVertex3f(0, 0, 1);
	glNormal3f(1.0, -1.6, 1.0);   glColor3f(0.0, 1.0, 1.0); glVertex3f(1, 0, 1);
	glNormal3f(1.0, -1.6, -1.0);  glColor3f(0.0, 1.0, 1.0); glVertex3f(1, 0, 0);

	glEnd(); // telling opengl this is the end of glBegin
}

void materialColorSet(GLfloat r, GLfloat g, GLfloat b) {

	GLfloat a[] = { r, g, b, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
	GLfloat d[] = { 0.2f, 0.3f, 0.5f, 0.5f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
	GLfloat s[] = { r, g, b, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
}

class Arm {
public:
	double sx, sy, sz;
	double tx, ty, tz;
	int rx, ry, rz;
	double cr, cg, cb;
	bool selected = false;

	Arm(double ssx, double ssy, double ssz,
		double ttx, double tty, double ttz,
		double rrx, double rry, double rrz,
		double ccr, double ccg, double ccb
	) {
		sx = ssx; sy = ssy; sz = ssz;
		tx = ttx; ty = tty; tz = ttz;
		rx = rrx; ry = rry; rz = rrz;
		cr = ccr; cg = ccg; cb = ccb;
	}

	void draw() {
		glTranslatef(r*tx, r*ty, r*tz); // moves shapes by x horizontaly and by y verticaly
		glRotatef(rx, 1, 0, 0); // function to rotate the matrix by xrr degree in x axis 
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);

		glPushMatrix();
		glTranslatef(r*-0.5, 0, r*-0.5);
		glScalef(r*sx, r*sy, r*sz);
		color_decide();
		cube();
		glPopMatrix();
	}

	void color_decide() {
		if (selected)
			materialColorSet(0.7, 0.7, 0.7);
		else
			materialColorSet(cr, cg, cb);
	}

	void select(bool is_selected) { selected = is_selected; }

	void rotate(int rrx, int rry, int rrz) {
		rx += rrx; ry += rry; rz += rrz;
		rx %= 360; ry %= 360; rz %= 360;
	}
};

class Ball {
public:
	double s;
	double tx, ty, tz;
	double cr, cg, cb;
	bool falling = false;

	Ball(double ss,
		double ttx, double tty, double ttz,
		double ccr, double ccg, double ccb
	) {
		s = ss;
		tx = ttx; ty = tty; tz = ttz;
		cr = ccr; cg = ccg; cb = ccb;
	}

	void draw() {
		if (ty < 0.5 && falling) {
			ty = 0.5;
			falling = false;
		}
		else if (falling)
			ty -= 0.05;

		glTranslatef(r*tx, r*ty, r*tz);

		glPushMatrix();
		glTranslatef(r*-0.5, 0, r*-0.5);
		glScalef(r*s, r*s, r*s);
		materialColorSet(cr, cg, cb);
		sphere();
		glPopMatrix();
	}

	void fall() { falling = true; }
};

Arm arms[3] = {
	Arm(1, 3, 1 /**/, -0.5, 0, -0.5 /**/, 0, 0, 0 /**/, 0.0, 0.5, 0.0),
	Arm(1, 3, 1 /**/, 0, 3, 0 /**/, 0, 0, 0 /**/, 0.5, 0.0, 0.5),
	Arm(1, 3, 1 /**/, 0, 3, 0 /**/, 0, 0, 0 /**/, 0.0, 0.0, 0.5)
};
Ball ball = Ball(1 /**/, 7, 5.5, 0 /**/, 0.2, 0.3, 0.5);
void render(void) // the function that will run to display items
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // wipe the drawing surface's color and depth buffer
														// GL_DEPTH_BUFFER_BIT: buffer to store how close object's pixels are releative to the viewer
														// GL_COLOR_BUFFER_BIT: buffer to store what color the object's pixels are

	//...

	glPushMatrix();
	glRotatef(xrr, 1, 0, 0); // function to rotate the matrix by xrr degree in x axis 
	glRotatef(yrr, 0, 1, 0);

	//...

	glPushMatrix();
	for (int i = 0; i < sizeof(arms) / sizeof(arms[0]); i++)
		arms[i].draw();
	float* c1 = return_matrix(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earthTextureData);
	ball.draw();
	float* c2 = return_matrix(1, 1, 1);
	glPopMatrix();

	//...

	for (int i = 0; i < 3; i++)
		c1[i] -= c2[i];
	std::cout << abs(c1[0]) + abs(c1[1]) + abs(c1[2]) << " * ";

	glBegin(GL_QUADS);
	glNormal3f(-1.0, -1.0, 1.6); glColor3f(1.0, 0.0, 0.0); glVertex3f(-10, 0, -10);
	glNormal3f(-1.0, 1.0, 1.6);  glColor3f(1.0, 0.0, 0.0); glVertex3f(10, 0, -10);
	glNormal3f(1.0, 1.0, 1.6);   glColor3f(1.0, 0.0, 0.0); glVertex3f(10, 0, 10);
	glNormal3f(1.0, -1.0, 1.6);  glColor3f(1.0, 0.0, 0.0); glVertex3f(-10, 0, 10);
	glEnd();

	glPopMatrix();


	//...
	glutSwapBuffers(); // swap the back buffer (which has been prepared) with front buffer, telling gpu to write the new frame

}

void reshape(int, int) {

}

void keyboard(unsigned char key, int, int) {
	switch (key) {
	case 13:
		ball.fall();
		break;
	case 32:
		curr_box++;
		curr_box %= sizeof(arms) / sizeof(arms[0]);
		break;
	case 'W':
	case 'w':
		xrr -= 5;
		break;

	case 'A':
	case 'a':
		yrr -= 5;
		break;

	case 'S':
	case 's':
		xrr += 5;
		break;

	case 'D':
	case 'd':
		yrr += 5;
		break;

		//****************
	case 'o':
	case 'O':
		arms[curr_box].rotate(-5, 0, 0);
		break;

	case 'K':
	case 'k':
		arms[curr_box].rotate(0, 0, 5);
		break;

	case 'L':
	case 'l':
		arms[curr_box].rotate(5, 0, 0);
		break;

	case ':':
	case ';':
		arms[curr_box].rotate(0, 0, -5);
		break;
	}
	xrr %= 360, yrr %= 360;
}

void mouseMove(int x, int y) {
	double width = glutGet(GLUT_WINDOW_WIDTH);
	double height = glutGet(GLUT_WINDOW_HEIGHT);
	float fx = (x - width / 2)*2.0 / width, fy = (-y + height / 2)*2.0 / height;
	GLfloat lightPosition[] = { fx * 0.5, fy * 0.5, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

}

void delay(int) {}
void idle(void) {
	for (int i = 0; i < sizeof(arms) / sizeof(arms[0]); i++)
		arms[i].select(false);
	arms[curr_box].select(true);


	glutPostRedisplay(); // re-calling the display (render in this case) function and remake the buffer
	glutTimerFunc(1000 / 0.001, delay, 0); // wait 1000/60 ms to (re-)call the function (limit to at most 60 fps)
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
	glTranslatef(0, -1, -3.5);
	glEnable(GL_DEPTH_TEST);

	earthTextureData = LoadTexture("Texture/globe.bmp");
}

void initLighting()
{
	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set lighting intensity and color
	GLfloat ambientLight[] = { 0.3, 0.2, 0.1, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	GLfloat diffuseLight[] = { 0.5, 0.5, 0.5, 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	GLfloat specularLight[] = { 0.3, 0.2, 0.1, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glMaterialf(GL_FRONT, GL_SHININESS, 1);

	// Set the light position
	GLfloat lightPosition[] = { 0.5, 0.5, 1, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv); // initilize OpenGL GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // enable double buffering and RGBA color spectrum
	glutInitWindowPosition(100, 100); // set the top left corner point of window that's to be displayed
	glutInitWindowSize(1600, 900); // set the size for window that's to be displayed
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
