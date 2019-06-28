#include <gl/glut.h>
#include <iostream>
using namespace std;
float mx = 0, my = 0;
float r = 5;

void Init()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//���Դ
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_position_red[] = { -1.0, 1.0, 1.0, 0.0 };//��ɫ���Դ

	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	//Ϊ�����е����嶨��������ԣ���η�����ߣ����ϻ�����ɢ�䡢������ɫ������ȣ�
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//�����Դ��λ��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);//����ɢ���Ϊ��ɫ
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);//���徵���Ϊ��ɫ

	glLightfv(GL_LIGHT1, GL_POSITION, light_position_red);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);//����ģ�Ͳ�����ȫ�ֻ�����

	glEnable(GL_LIGHTING);//������Դ
	glEnable(GL_LIGHT0);//�����ض���Դ

	glEnable(GL_LIGHT1);

	glEnable(GL_DEPTH_TEST);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cout << "display\n";
	glutSolidSphere(0.5, 300, 16);//�������巨����
	glFlush();
}

void Reshape(int w, int h)
{
	cout << "reshape\n";
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//if (w <= h)
	//{
	//	glOrtho(-1.5, 1.5, -1.5 *(GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	//}
	//else
	//{
	//	glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	//}
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLfloat)w / (GLfloat)h, 0.1, 3000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
// ��갴�²��ƶ��¼� 
void myMouseMove(int x, int y)
{




	float px = x - mx;//����ƽ����
	float py = y - my;
	mx = x, my = y;//����mx��my

	glRotatef(10, 0, 1, 0);

	cout << "px " << px << " \n";
	glutPostRedisplay();

}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMotionFunc(myMouseMove);//����ƶ��¼����������²��ƶ�
	glutMainLoop();

	return 0;
}

