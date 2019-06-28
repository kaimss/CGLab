#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

// ��ϰ6.1 ����ͼ�ε���ϻ���

void render();
void initGL();

void main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 150);
	glutInitWindowSize(320, 320);
	glutCreateWindow("ģ��ʱ��");
	glutDisplayFunc(render);
	glutIdleFunc(render);
	initGL();
	glutMainLoop();
}

void initGL()
{
	glViewport(0, 0, 320, 320);
	glOrtho(-100, 100, -100, 100, -100, 100);
	glClearColor(0, 0, 0, 1);
}

//���ݳ��ȴ�������
void createClockPointer(float size)
{
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(size, 0);
	glEnd();
}

GLfloat hR = 20; //ʱ�볤��
GLfloat mR = 30; //���볤��
GLfloat sR = 45; //���볤��
GLfloat cR = 57; //���̰뾶

GLfloat doublePI = 2 * 3.1415936; //2��
GLfloat step = doublePI / 24; //����Բ�εĽǶ��з�

GLfloat Hstep = doublePI / 12; //Сʱ�̶ȵĽǶ��з�
GLfloat Sstep = doublePI / 60; //����̶ȵĽǶ��з�

GLfloat Sangle; //������ת�ĽǶ�
GLfloat Mangle; //������ת�ĽǶ�
GLfloat Hangle; //ʱ����ת�ĽǶ�

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//��������
	glBegin(GL_POLYGON);
	for (GLfloat angle = 0.0; angle < doublePI + step; angle += step)
	{
		glColor3f(0.6f, 0.4f, 0.12f);
		GLfloat y = cR * sin(angle);
		GLfloat x = cR * cos(angle);
		glVertex2f(x, y);
	}
	glEnd();

	//��������
	glBegin(GL_POLYGON);
	float angle = 0.0;
	for (angle = 0.0; angle < doublePI + step; angle += step)
	{
		glColor3f(0, 0, 0);
		GLfloat y = (cR - 2) * sin(angle);
		GLfloat x = (cR - 2) * cos(angle);
		glVertex2f(x, y);
	}
	glEnd();

	//��������̶�
	glBegin(GL_LINES);
	for (angle = 0.0; angle < doublePI + Sstep; angle += Sstep)
	{
		glColor3f(0.6f, 0.4f, 0.12f);
		GLfloat y = (cR - 2) * sin(angle);
		GLfloat x = (cR - 2) * cos(angle);

		GLfloat y2 = (cR - 4) * sin(angle);
		GLfloat x2 = (cR - 4) * cos(angle);

		glVertex2f(x2, y2);
		glVertex2f(x, y);
	}
	glEnd();

	//���ƿ̶�
	glBegin(GL_LINES);
	for (angle = 0.0; angle < doublePI + Hstep; angle += Hstep)
	{
		glColor3f(0.6f, 0.4f, 0.12f);
		GLfloat y = (cR - 4) * sin(angle);
		GLfloat x = (cR - 4) * cos(angle);

		GLfloat y2 = (cR - 7) * sin(angle);
		GLfloat x2 = (cR - 7) * cos(angle);

		glVertex2f(x2, y2);
		glVertex2f(x, y);
	}
	glEnd();

	//��������
	glPushMatrix();
	glRotatef(Sangle, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	createClockPointer(sR);
	glPopMatrix();

	//���Ʒ���
	glPushMatrix();
	glRotatef(Mangle, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	createClockPointer(mR);
	glPopMatrix();

	//����ʱ��
	glPushMatrix();
	glRotatef(Hangle, 0, 0, 1);
	glColor3f(0.0f, 0.0f, 1.0f);
	createClockPointer(hR);
	glPopMatrix();

	glutSwapBuffers();
	glFlush();

	Sangle -= 1.8;
	Mangle -= 0.3;
	Hangle -= 0.05;
}