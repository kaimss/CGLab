#include <GL/glut.h>
#include <iostream>
using namespace std;
#define PI 3.1415926535
static double theta1 = 0, theta2 = 0;
static int mx = 0, my = 0;
static double rx = 4.0, ry = 0;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);


	glPushMatrix();

	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef(theta1, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(1.0, 0.0, 0.0);
	glRotatef(theta2, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

/* Change these values for a different transformation  */
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void mouse(int button, int state, int x, int y)
{

	
	switch (button) {
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	default:
		break;
	}
}
void mouseMove(int x, int y)
{
	float px = x - mx;//计算平移量
	float py = y - my;
	mx = x, my = y;//更新mx与my

	cout << x << "," << y << endl;


}
void keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	case 27:
		break;
	}
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);//鼠标移动事件监听，按下并移动


	glutMainLoop();
	return 0;
}