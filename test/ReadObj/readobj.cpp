#include <stdio.h>
#include <gl/glut.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#pragma warning(disable:4996)
#define WIDTH 400
#define HEIGHT 400
float vertex[2904][3];
float vertexcolor[2904][3];
int   face[5804][3];
int m, i;





void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (m = 0; m<5804; m++)
	{
		glBegin(GL_TRIANGLES);
		for (i = 0; i<3; i++)
		{
			glColor3fv(vertexcolor[face[m][i] - 1]);
			glVertex3fv(vertex[face[m][i] - 1]);
		}
	}
	glEnd();

	glFlush();

}


int main(int argc, char* argv[])
{
	
	FILE* fp = fopen("C:\\Users\\Administrator\\Desktop\\cow_color.obj", "r");
	if (fp == NULL)
	{
		printf("无文件");
		return -1;
	}

	for (i = 0; i<2904; i++)
	{
		fscanf(fp, "v");
		for (j = 0; j<3; j++)
		{
			fscanf(fp, "%f", &vertex[i][j]);
		}
		fscanf(fp, "\n");
	}
	for (i = 0; i<2904; i++)
	{
		fscanf(fp, "vc");
		for (j = 0; j<3; j++)
		{
			fscanf(fp, "%f", &vertexcolor[i][j]);
		}
		fscanf(fp, "\n");
	}
	for (i = 0; i<5804; i++)
	{
		fscanf(fp, "f");
		for (j = 0; j<3; j++)
		{
			fscanf(fp, "%d", &face[i][j]);
		}
		fscanf(fp, "\n");
	}

	fclose(fp);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL 窗口");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}