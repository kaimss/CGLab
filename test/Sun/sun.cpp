#include <GL/glut.h>
#include <iostream>
using namespace std;

static int year = 0, day = 0;
int i = 1;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{

	cout << "i = " << i << "\n";
	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f(1.0, 0.0, 1.0);//��ɫ
	glBegin(GL_LINES);//���������
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100.0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100.0);
	glVertex3f(0, 0, 0);
	glVertex3f(100.0, 0, 0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);//��ɫ
	glPushMatrix();
	glutSolidSphere(1.0, 20, 16);
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);


	glColor3f(0.0, 1.0, 1.0);//��ɫ
	glBegin(GL_LINES);//����������
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100.0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100.0);
	glVertex3f(0, 0, 0);
	glVertex3f(100.0, 0, 0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);//��ɫ
	glutSolidSphere(0.2, 10, 8);






	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':
		day = (day + 10) % 360;
		glutPostRedisplay();
		break;
	case 'D':
		day = (day - 10) % 360;
		glutPostRedisplay();
		break;
	case 'y':
		i++;
		year = (year + 5) % 360;
		glutPostRedisplay();
		break;
	case 'Y':
		year = (year - 5) % 360;
		glutPostRedisplay();
		break;
	default:
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
	glutMainLoop();
	return 0;
}