
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
//��ֵ΢�ַ�
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
	{//б�ʴ���
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
	{//б�ʲ�����
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
//�е㻭�߷�����֤x0 < x1
void LineMidpoint(int x0, int y0, int x1, int y1)
{
	if (x1 < x0)
	{
		temp = x1, x1 = x0, x0 = temp;
		temp = y1, y1 = y0, y0 = temp;
	}
	if (x1 - x0 != 0)
	{//б�ʴ���

		int a, b, d1, d2, d, x, y;
		a = y0 - y1, b = x1 - x0;
		

		if (b <= -a && -a <= 1)
		{//б��[0,1]

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
		{//б��[-1,0)
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
		{//б��>1
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
		{//б��<-1

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
	{//б�ʲ�����
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
	{//б�ʴ���
		if (0 <= dy && dy <= dx)
		{//б��[0,1]
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
		{//б��[-1,0)
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
		{//б��>1
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
		{//б��<-1
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
	{//б�ʲ�����

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
//�е㻭Բ����(x0,y0)ΪԲ�����꣬rΪ�뾶
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


	glFlush(); //ˢ�´�������ʾ��ǰ����ͼ��
}
//����϶�
void dragmouse(int x, int y) {
	xe = x;
	ye = h - y;

	printf("%d %d %d %d\n", xs, ys, xe, ye);//�����������ӡ����
	glClear(GL_COLOR_BUFFER_BIT);//���������ʾ����
	glBegin(GL_POINTS);
	
	//LineDDA(xs, ys, xe, ye);
	//LineMidpoint(xs, ys, xe, ye);
	LineBresenham(xs, ys, xe, ye);
	//CircleMidPoint(100, 100, 50);
	glEnd();
	glFlush();

}

//������������
void mymouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		xe = x;
		ye = h - y;
		printf("%d %d %d %d\n", xs, ys, xe, ye);//�����������ӡ����
		glClear(GL_COLOR_BUFFER_BIT);//���������ʾ����
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
	glClearColor(0.0, 0.0, 0.0, 1.0);//���ñ�����ɫ���˴�Ϊ��ɫ
	glClear(GL_COLOR_BUFFER_BIT);//�õ�ǰ����ɫ��䴰�ڣ��˴�Ϊ��ɫ
	glColor3f(1.0, 1.0, 1.0);//���û�����ɫ���˴�Ϊ��ɫ
	glPointSize(2.0f);//���õ�Ĵ�С
	glMatrixMode(GL_PROJECTION);//����ΪͶӰ����ģʽ
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
	cout << "�����߶���ʼ���յ����꣨��Χ��Ϊ 0 - 500��:";
	cin >> xs >> ys >> xe >> ye;
	//xs = 105; ys = 405; xe = 405; ye = 120;
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(w, h);
	glutCreateWindow("drawline&circle");
	init();
	glutDisplayFunc(display);
	//glutMouseFunc(mymouse);//�������ص�����
	//glutMotionFunc(dragmouse);//����϶�
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}