#include <gl/glut.h>  //引用相关包

int w = 600, h = 600;

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);  //清空颜色缓冲区
	//glColor3f(1, 1, 1);   //置颜色为白色

	glViewport(0, 0, w, h);

	/*glBegin(GL_LINES);
	glVertex2f(0, -2.0);
	glVertex2f(0, 2.0);
	glEnd();*/

	glColor3f(0, 1, 1);   //置颜色为蓝绿色

	glViewport(0, 0, w/2, h);
	glLoadIdentity();   //清空矩阵
	glTranslatef(0, 0, -5); //将物体沿X轴正方向平移x个单位(x是有符号数)，沿Y轴正方向平移y个单位(y是有符号数)，沿Z轴正方向平移z个单位(z是有符号数)
	glRotatef(30, 0, 1, 0);//将物体沿着从(0,0,0)到(x,y,z)的直线旋转angle度(右手定则)
	glScalef(1, 2, 1);  //将物体沿X轴放大x倍，沿Y轴放大y倍，沿Z轴放大z倍

	//glScalef(1, 2, 1);
	//gluLookAt(0,0,5,0,0,0,0,2,0); //观测位置在(0,0,5)，看向位置(0,0,0)，脑袋朝向(0,2,0)

	glutWireCube(1.0); //绘制实心立方体和线框立方体

	glViewport(w/2, 0, w/2, h);
	//glLoadIdentity();
	//glTranslatef(-2, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(1.5, 0.0);
	glEnd();



	glFlush();   //刷新窗口以显示当前绘制图形
}
void init(void)
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT); //选择平面明暗模式或光滑明暗模式
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);   //设置机口
	glMatrixMode(GL_PROJECTION);  //指定哪一个矩阵是当前矩阵
	glLoadIdentity();
	gluPerspective(60, 1, 1.5, 20);   //创建透视投影矩阵(fovy,aspect,zNear,zFar);
	//glFrustum(-1,1,-1,1,1.5,20.0);  //用透视矩阵乘以当前矩阵(left,Right,bottom,top,near,far);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv); //固定格式
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
	glutInitWindowSize(w, h);    //显示框的大小
	glutInitWindowPosition(400, 400); //确定显示框左上角的位置
	glutCreateWindow("绘制立方体和三角形");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop(); //进人GLUT事件处理循环
	return 0;
}
