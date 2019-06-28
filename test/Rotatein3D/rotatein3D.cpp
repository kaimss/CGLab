#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glutSolidCube(2);
	glutSwapBuffers();
}

/* Change these values for a different transformation  */
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void mouse(int button, int state, int x, int y)
{

	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realy;  /*  OpenGL y coordinate position  */
	GLdouble wx, wy, wz;  /*  returned world x, y, z coords  */
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			printf("Coordinates (%4d, %4d)\n", x, y);
			printf("Coordinates (%4d, %4d)\n", x, 500 - y);
			glGetIntegerv(GL_VIEWPORT, viewport);
			cout << "viewport martrix is :";
			for (int i = 0; i < 4; i++)
			{
				cout << viewport[i] << "  ";
			}
			cout << endl;
			glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
			glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

			realy = viewport[3] - (GLint)y - 1;

			//double zi = 0.0, zj = 1.0, ztemp;
			//while (1)
			//{
			//	gluUnProject((GLdouble)x, (GLdouble)realy, 0.0,
			//		mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
			//	if(wz)
			//}

			printf("Coordinates at cursor are (%4d, %4d)\n", x, realy);
			for (float z = 0.0; z < 1.0; z+=0.1)
			{
				
				gluUnProject((GLdouble)x, (GLdouble)realy, z,
					mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
				cout << "World coords at z = " << z << " are ( " << wx << " , " << wy << " , " << wz << " )" << endl;
				//printf("World coords at z=%f are (%f, %f, %f)\n", wz, wx, wy, wz);
			}
			
;

			//gluUnProject((GLdouble)x, (GLdouble)realy, 0.4,
			//	mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
			//printf("World coords at z=0.4 are (%f, %f, %f)\n", wx, wy, wz);

			//gluUnProject((GLdouble)x, (GLdouble)realy, 0.8,
			//	mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
			//printf("World coords at z=0.8 are (%f, %f, %f)\n", wx, wy, wz);


			gluUnProject((GLdouble)x, (GLdouble)realy, 1.0,
				mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
			printf("World coords at z=1.0 are (%f, %f, %f)\n", wx, wy, wz);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			exit(0);
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

/*

*  Open window, register input callback functions

*/

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}