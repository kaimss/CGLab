
#include <GL/GLUT.H>
#include <iostream>
#include <math.h>

const int n = 10;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;

using namespace std;

int xs = 0.0;
int ys = 0.0;
int xe = 0.0;
int ye = 0.0;
int temp;
int w = 500, h = 500;
//数值微分法
void LineDDA(int x0, int y0, int x1, int y1)
{
	if (x1 < x0)
	{
		temp = x1, x1 = x0, x0 = temp;
		temp = y1, y1 = y0, y0 = temp;
	}
	float dx, dy, x, y, k;

	dx = x1 - x0;
	dy = y1 - y0;

	
	if (dx != 0)
	{//斜率存在
		k = dy / dx;
		if (k <= 1 && k >= -1)
		{
			y = y0;
			for (x = x0; x <= x1; x++)
			{
				glVertex2i(x, int(y + 0.5));
				y += k;
				cout << "( " << int(x + 0.5) << " , " << y << " ) \n";
			}

		}
		if (k > 1 || k < -1)
		{
			/*k = 1 / k;
			y = x0;
			for (x = y0; x <= x1; x++)
			{
				glVertex2i(int(y + 0.5), x);
				y += k;
			}*/
			k = 1 / k;
			x = x0;
			for (y = y0; y <= y1; y++)
			{
				glVertex2i(int(x + 0.5), y);
				x += k;
				cout << "( " << int(x + 0.5) << " , " << y << " ) \n";
			}
			
		}
	}
	else
	{//斜率不存在
		int x = x0, y;
		int ymin = (y0 <= y1) ? y0 : y1;
		int ymax = (y0 <= y1) ? y1 : y0;
		for (y = ymin; y <= ymax; y++)
		{
			glVertex2i(x, y);
			y++;
		}
	}
}
//中点画线法，保证x0 < x1
void LineMidpoint(int x0, int y0, int x1, int y1)
{
	if (x1 < x0)
	{
		temp = x1, x1 = x0, x0 = temp;
		temp = y1, y1 = y0, y0 = temp;
	}
	if (x1 - x0 != 0)
	{//斜率存在

		int a, b, d1, d2, d, x, y;
		a = y0 - y1, b = x1 - x0;
		

		if (b <= -a && -a <= 1)
		{//斜率[0,1]

			d = 2 * a + b, d1 = 2 * a, d2 = 2 * (a + b);
			x = x0, y = y0;
			glVertex2i(x, y);
			while (x < x1)
			{
				if (d < 0)
				{
					x++, y++, d += d2;
				}
				else
				{
					x++, d += d1;
				}
				cout << "( " << x << " , " << y << " ) \n";
				glVertex2i(x, y);
			}
		}
		else if (-b <= -a && -a < 0)
		{//斜率[-1,0)
			d = 2 * a - b, d1 = 2 * a, d2 = 2 * (a - b);
			x = x0, y = y0;
			glVertex2i(x, y);
			while (x < x1)
			{
				if (d < 0)
				{
					x++, d += d1;
				}
				else
				{
					x++, y--, d += d2;
				}
				cout << "( " << x << " , " << y << " ) \n";
				glVertex2i(x, y);
			}
		}
		else if (-a > b)
		{//斜率>1
			d = a + 2 * b, d1 = 2 * b, d2 = 2 * (a + b);
			x = x0, y = y0;
			glVertex2i(x, y);
			while (y < y1)
			{
				if (d < 0)
				{
					y++, d += d1;
				}
				else
				{
					x++, y++, d += d2;
				}
				cout << "( " << x << " , " << y << " ) \n";
				glVertex2i(x, y);
			}

		}
		else
		{//斜率<-1

			d = a - 2 * b, d1 = -2 * b, d2 = 2 * (a - b);
			x = x0, y = y0;
			glVertex2i(x, y);
			while (y > y1)
			{
				if (d < 0)
				{
					x++, y--, d += d2;
				}
				else
				{

					y--, d += d1;
				}
				cout << "( " << x << " , " << y << " ) \n";
				glVertex2i(x, y);
			}
		}
		
	}
	else
	{//斜率不存在
		int y, x = x0, d;
		y = (y0 <= y1) ? y0 : y1;
		d = fabs((double)(y0 - y1));
		while (d >= 0)
		{
			glVertex2i(x, y);
			y++;
			d--;
		}

	}
	
}

void LineBresenham(int x0, int y0, int x1, int y1)
{
	if (x1 < x0)
	{
		temp = x1, x1 = x0, x0 = temp;
		temp = y1, y1 = y0, y0 = temp;
	}
	int x, y, dx, dy, e, i;
	dx = x1 - x0, dy = y1 - y0;
	x = x0, y = y0;

	if (dx != 0)
	{//斜率存在
		if (0 <= dy && dy <= dx)
		{//斜率[0,1]
			e = -dx;
			for (i = 0; i <= dx; i++)
			{
				glVertex2i(x, y);
				cout << "( " << x << " , " << y << " ) \n";
				x++, e = e + 2 * dy;
				if (e >= 0)
				{
					y++;
					e = e - 2 * dx;
				}
			}
		}
		else if (-dx <= dy && dy <= 0)
		{//斜率[-1,0)
			e = dx;
			for (i = 0; i <= dx; i++)
			{
				glVertex2i(x, y);
				cout << "( " << x << " , " << y << " ) \n";
				x++, e = e + 2 * dy;
				if (e < 0)
				{
					y--;
					e = e + 2 * dx;
				}
			}
		}
		else if (dy > dx)
		{//斜率>1
			e = -dy;
			for (i = 0; i <= dy; i++)
			{
				glVertex2i(x, y);
				cout << "( " << x << " , " << y << " ) \n";
				y++, e = e + 2 * dx;
				if (e >= 0)
				{
					x++;
					e = e - 2 * dy;
				}
			}
		}
		else
		{//斜率<-1
			e = dy;
			for (i = 0; i <= -dy; i++)
			{
				glVertex2i(x, y);
				cout << "( " << x << " , " << y << " ) \n";
				y--, e = e + 2 * dx;
				if (e > 0)
				{
					x++;
					e = e + 2 * dy;
				}
			}
		}
	}
	else
	{//斜率不存在

		int d;
		y = (y0 <= y1) ? y0 : y1;
		d = fabs((double)(y0 - y1));
		while (d >= 0)
		{
			glVertex2i(x, y);
			y++;
			d--;
		}
	}
	


}

void circlepoints(int x0, int y0, int x, int y)
{
	
	glVertex2i(x + x0, y + y0);
	glVertex2i(x + x0, -y + y0);
	glVertex2i(-x + x0, y + y0);
	glVertex2i(-x + x0, -y + y0);
	glVertex2i(y + y0, x + x0);
	glVertex2i(-y + y0, x + x0);
	glVertex2i(y + y0, -x + x0);
	glVertex2i(-y + y0, -x + x0);
}
//中点画圆法，(x0,y0)为圆心坐标，r为半径
void CircleMidPoint(int x0, int y0, int r)
{
	int x, y;
	float d;
	x = 0, y = r , d = 1.25 - r;
	circlepoints(x0, y0, x, y);


	while (x <= y)
	{
		if (d < 0)
		{
			d = d + 2 * x + 3;
		}
		else
		{
			d = d + 2 * (x - y) + 5;
			y--;
		}
		x++;
		circlepoints(x0, y0, x, y);
	}

	
}
void Circle()
{
	for (int i = 0; i<n; i++)
		glVertex2f(R*cos(2 * Pi / n * i), R*sin(2 * Pi / n * i));
}

void display()
{

	glBegin(GL_POINTS);

	LineDDA(xs, ys, xe, ye);
	//LineMidpoint(xs, ys, xe, ye);
	//LineBresenham(xs, ys, xe, ye);
	//CircleMidPoint(100, 100, 50);
	//Circle();

	glEnd();


	glFlush(); //刷新窗口以显示当前绘制图形
}
//鼠标拖动
void dragmouse(int x, int y) {
	xe = x;
	ye = h - y;

	printf("%d %d %d %d\n", xs, ys, xe, ye);//把两个坐标打印出来
	glClear(GL_COLOR_BUFFER_BIT);//清除窗口显示内容
	glBegin(GL_POINTS);
	
	//LineDDA(xs, ys, xe, ye);
	//LineMidpoint(xs, ys, xe, ye);
	LineBresenham(xs, ys, xe, ye);
	//CircleMidPoint(100, 100, 50);
	glEnd();
	glFlush();

}

//鼠标监听，画点
void mymouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		xe = x;
		ye = h - y;
		printf("%d %d %d %d\n", xs, ys, xe, ye);//把两个坐标打印出来
		glClear(GL_COLOR_BUFFER_BIT);//清除窗口显示内容
		glBegin(GL_POINTS);
		
		//LineDDA(xs, ys, xe, ye);
		//LineMidpoint(xs, ys, xe, ye);
		LineBresenham(xs, ys, xe, ye);
		//CircleMidPoint(100, 100, 50);

		glEnd();
		glFlush();

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xs = x;
		ys = h - y;
	}

}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);//设置背景颜色，此处为黑色
	glClear(GL_COLOR_BUFFER_BIT);//用当前背景色填充窗口，此处为黑色
	glColor3f(1.0, 1.0, 1.0);//设置绘制颜色，此处为白色
	glPointSize(2.0f);//设置点的大小
	glMatrixMode(GL_PROJECTION);//设置为投影矩阵模式
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);

	
	
	
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	cout << "输入线段起始和终点坐标（范围均为 0 - 500）:";
	cin >> xs >> ys >> xe >> ye;
	//xs = 105; ys = 405; xe = 405; ye = 120;
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(w, h);
	glutCreateWindow("drawline&circle");
	init();
	glutDisplayFunc(display);
	//glutMouseFunc(mymouse);//鼠标监听回调函数
	//glutMotionFunc(dragmouse);//鼠标拖动
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}