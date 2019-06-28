#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

// 练习6.1 基本图形的组合绘制

void render();
void initGL();

void main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 150);
	glutInitWindowSize(320, 320);
	glutCreateWindow("模拟时钟");
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

//根据长度创建表针
void createClockPointer(float size)
{
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(size, 0);
	glEnd();
}

GLfloat hR = 20; //时针长度
GLfloat mR = 30; //分针长度
GLfloat sR = 45; //秒针长度
GLfloat cR = 57; //表盘半径

GLfloat doublePI = 2 * 3.1415936; //2π
GLfloat step = doublePI / 24; //绘制圆形的角度切分

GLfloat Hstep = doublePI / 12; //小时刻度的角度切分
GLfloat Sstep = doublePI / 60; //分秒刻度的角度切分

GLfloat Sangle; //秒针旋转的角度
GLfloat Mangle; //分针旋转的角度
GLfloat Hangle; //时针旋转的角度

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//绘制外盘
	glBegin(GL_POLYGON);
	for (GLfloat angle = 0.0; angle < doublePI + step; angle += step)
	{
		glColor3f(0.6f, 0.4f, 0.12f);
		GLfloat y = cR * sin(angle);
		GLfloat x = cR * cos(angle);
		glVertex2f(x, y);
	}
	glEnd();

	//绘制内盘
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

	//绘制秒针刻度
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

	//绘制刻度
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

	//绘制秒针
	glPushMatrix();
	glRotatef(Sangle, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	createClockPointer(sR);
	glPopMatrix();

	//绘制分针
	glPushMatrix();
	glRotatef(Mangle, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	createClockPointer(mR);
	glPopMatrix();

	//绘制时针
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