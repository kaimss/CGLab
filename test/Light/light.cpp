#include <gl/glut.h>
#include <iostream>
using namespace std;
float mx = 0, my = 0;
float r = 5;

void Init()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//点光源
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_position_red[] = { -1.0, 1.0, 1.0, 0.0 };//红色点光源

	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	//为场景中的物体定义材料属性：如何反射光线（材料环境、散射、镜面颜色、光泽度）
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//定义光源的位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);//定义散射光为白色
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);//定义镜面光为白色

	glLightfv(GL_LIGHT1, GL_POSITION, light_position_red);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);//光照模型参数：全局环境光

	glEnable(GL_LIGHTING);//驱动光源
	glEnable(GL_LIGHT0);//启动特定光源

	glEnable(GL_LIGHT1);

	glEnable(GL_DEPTH_TEST);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cout << "display\n";
	glutSolidSphere(0.5, 300, 16);//定义球体法向量
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
// 鼠标按下并移动事件 
void myMouseMove(int x, int y)
{




	float px = x - mx;//计算平移量
	float py = y - my;
	mx = x, my = y;//更新mx与my

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
	glutMotionFunc(myMouseMove);//鼠标移动事件监听，按下并移动
	glutMainLoop();

	return 0;
}

