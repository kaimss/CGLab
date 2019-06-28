#include <gl/glut.h>

static int shoulder = 0, elbow = 0;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);//白色
	glBegin(GL_LINES);//坐标轴绘制
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0.8, 0, 0);
	glEnd();

	glPushMatrix();

	glTranslatef(-1.0, 0.0, 0.0);//局部坐标系的移动
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);

	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	glColor3f(1.0, 0.0, 1.0);//紫色
	glBegin(GL_LINES);//坐标轴绘制
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100.0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100.0);
	glVertex3f(0, 0, 0);
	glVertex3f(100.0, 0, 0);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);


	glTranslatef(1.0, 0.0, 0.0);//局部坐标系的移动
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);

	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	glColor3f(1.0, 0.0, 1.0);//紫色
	glBegin(GL_LINES);//坐标轴绘制
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100.0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100.0);
	glVertex3f(0, 0, 0);
	glVertex3f(100.0, 0, 0);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);


	glTranslatef(1.0, 0.0, 0.0);//局部坐标系的移动
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);

	glPushMatrix();
	glScalef(0.8, 0.05, 0.05);
	glutWireCube(1.0);
	glPopMatrix();



	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;

	case 'S':
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;

	case 'e':
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;

	case 'E':
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;

	default:
		break;
	}

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
