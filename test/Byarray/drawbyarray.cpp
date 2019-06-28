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



	GLfloat sun_light_position[] = { 0.0f, 3.0f, 3.0f, 1.0f }; //光源的位置在世界坐标系圆心，齐次坐标形式
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f }; //RGBA模式的环境光，为0
	GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBA模式的漫反射光，全白光
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //RGBA模式下的镜面光 ，全白光
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	//开启灯光
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	// a. 启用或叫激活数组, 有8种同类要启用的数组GL_COLOR_ARRAY，GL_VERTEX_ARRAY
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_DEPTH_TEST);

	// b. 把数据放入到数组中
	//glColorPointer(3, GL_FLOAT, 0, colors[0]);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
}

void display(void)
{
	cout << "display\n";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glPushMatrix();




	GLfloat sun_light_position[] = { -2.0f, 2.0f, -2.0f, 1.0f }; //光源的位置，齐次坐标形式

	glPushMatrix();
	//glRotatef(spin, 0.0, 1.0, 0.0);
	glTranslatef(lx, ly, lz);//局部坐标系的移动
	glutSolidSphere(0.1, 40, 32);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glPopMatrix();


	 //定义太阳的材质并绘制太阳    
	{
		GLfloat sun_mat_ambient[] = { 0.5f, 0.8f, 0.5f, 1.0f };  //定义材质的环境光颜色，为0
		GLfloat sun_mat_diffuse[] = { 0.5f, 0.5f, 0.8f, 1.0f };  //定义材质的漫反射光颜色，为0
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色，为0
		GLfloat sun_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为偏红色
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
	glTranslatef(0.25, 0.0, -0.25);//局部坐标系的移动
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

	cout << "重新绘制\n";
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLfloat)w / (GLfloat)h, 0.1, 3000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.8, 1.8, 1.8, 0.25, 0.25, -0.25, 0.0, 1.0, 0.0);
	//gluLookAt(18.8, 18.8, 18.8, 0.25, 0.25, -0.25, 0.0, 1.0, 0.0);
}


//键盘按键监听函数
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
// 鼠标按下并移动事件 
void myMouseMove(int x, int y)
{
	float px = x - mx;//计算平移量
	float py = y - my;
	mx = x, my = y;//更新mx与my

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
	glutKeyboardFunc(myKeyboard);//键盘点击事件监听
	glutMotionFunc(myMouseMove);//鼠标移动事件监听，按下并移动
	glutMainLoop();
}
