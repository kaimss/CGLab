#include <GL/glut.h>
#include <iostream>
using namespace std;

static GLfloat spin = 0.0;
GLfloat lx = 0, ly = 0, lz = 0;
#define PI 3.1415926
#define NULL 0
//GLint circle_points = 100;
GLfloat angle = 0;
int mx, my;
static GLfloat vertices[] =
{
	//100, 200, 0,
	//100, 100, 0,
	//200, 100, 0,
	//200, 200, 0

	0, 0, 0,
	0.5, 0, 0,
	0.5, 0, -0.5,
	0, 0, -0.5,
	0, 0.5, 0,
	0.5, 0.5, 0,
	0.5, 0.5, -0.5,
	0, 0.5, -0.5

};

static GLfloat colors[6][24] =
{
	1.0,1.0,1.0, 1.0,1.0,1.0, 1.0,1.0,1.0, 1.0,1.0,1.0,
	1.0,1.0,1.0, 1.0,1.0,1.0, 1.0,1.0,1.0, 1.0,1.0,1.0,

	1.0, 0.2, 0.2, 1.0, 0.2, 0.2, 1.0, 0.2, 0.2, 1.0, 0.2, 0.2,
	1.0, 0.2, 0.2, 1.0, 0.2, 0.2, 1.0, 0.2, 0.2, 1.0, 0.2, 0.2,

	0.8, 1.0, 0.2, 0.8, 1.0, 0.2, 0.8, 1.0, 0.2, 0.8, 1.0, 0.2,
	0.8, 1.0, 0.2, 0.8, 1.0, 0.2, 0.8, 1.0, 0.2, 0.8, 1.0, 0.2,

	0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75,
	0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75, 0.75,

	0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35,
	0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35,

	0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
	0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
};

//static GLubyte allIndices[] = { 0, 1, 2, 0, 2, 3 };
static GLubyte mallIndices[6][4] = {
	3,0,4,7,
	2,3,7,6,
	0,1,2,3,
	4,5,6,7,
	0,1,5,4,
	1,2,6,5
};

void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);



	GLfloat sun_light_position[] = { 0.0f, 3.0f, 3.0f, 1.0f }; //��Դ��λ������������ϵԲ�ģ����������ʽ
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f }; //RGBAģʽ�Ļ����⣬Ϊ0
	GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBAģʽ��������⣬ȫ�׹�
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //RGBAģʽ�µľ���� ��ȫ�׹�
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	//�����ƹ�
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	// a. ���û�м�������, ��8��ͬ��Ҫ���õ�����GL_COLOR_ARRAY��GL_VERTEX_ARRAY
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_DEPTH_TEST);

	// b. �����ݷ��뵽������
	//glColorPointer(3, GL_FLOAT, 0, colors[0]);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
}

void display(void)
{
	cout << "display\n";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glPushMatrix();




	GLfloat sun_light_position[] = { -2.0f, 2.0f, -2.0f, 1.0f }; //��Դ��λ�ã����������ʽ

	glPushMatrix();
	//glRotatef(spin, 0.0, 1.0, 0.0);
	glTranslatef(lx, ly, lz);//�ֲ�����ϵ���ƶ�
	glutSolidSphere(0.1, 40, 32);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glPopMatrix();


	 //����̫���Ĳ��ʲ�����̫��    
	{
		GLfloat sun_mat_ambient[] = { 0.5f, 0.8f, 0.5f, 1.0f };  //������ʵĻ�������ɫ��Ϊ0
		GLfloat sun_mat_diffuse[] = { 0.5f, 0.5f, 0.8f, 1.0f };  //������ʵ����������ɫ��Ϊ0
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //������ʵľ��淴�����ɫ��Ϊ0
		GLfloat sun_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //������ʵķ������ɫ��Ϊƫ��ɫ
		GLfloat sun_mat_shininess = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
		//glutSolidCube(3);
		//glutSolidSphere(3.0, 40, 32);
	}


	glPushMatrix();
	glTranslatef(0.25, 0.0, -0.25);//�ֲ�����ϵ���ƶ�
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(-0.25, 0.0, 0.25);	
	glutSolidCube(0.8);
	//glutSolidSphere(0.5, 300, 16);


	//for (int i = 0; i < 6; i++)
	//{
	//	//glColorPointer(3, GL_FLOAT, 0, colors[i]);
	//	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, mallIndices[i]);
	//}

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{

	cout << "���»���\n";
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLfloat)w / (GLfloat)h, 0.1, 3000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.8, 1.8, 1.8, 0.25, 0.25, -0.25, 0.0, 1.0, 0.0);
	//gluLookAt(18.8, 18.8, 18.8, 0.25, 0.25, -0.25, 0.0, 1.0, 0.0);
}


//���̰�����������
void myKeyboard(unsigned char key, int x, int y)
{

	switch (key)
	{

	case 'w':
		ly += 0.3;
		break;
	case 's':
		ly -= 0.3;
		break;
	case 'a':
		lx -= 0.3;
		break;
	case 'd':
		lx += 0.3;
		break;
	case 'z':
		lz += 0.3;
		break;
	case 'x':
		lz -= 0.3;
		
		break;
	default:
		break;
	}


	glutPostRedisplay();
}
// ��갴�²��ƶ��¼� 
void myMouseMove(int x, int y)
{
	float px = x - mx;//����ƽ����
	float py = y - my;
	mx = x, my = y;//����mx��my

	if (px > 0)
		angle += 0.5;
	else
		angle -= 0.5;

	glutPostRedisplay();
	cout << px << endl;
}


int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("drawbyarray");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(myKeyboard);//���̵���¼�����
	glutMotionFunc(myMouseMove);//����ƶ��¼����������²��ƶ�
	glutMainLoop();
}
