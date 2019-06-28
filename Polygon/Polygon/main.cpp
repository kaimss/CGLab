#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<math.h>
#include "now.h"
using namespace std;
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#define PI 3.1415926535


vector<position> poly;//外围多边形的点
vector<edge> polyedge;//外围多边形的边，暂时未实现
vector<position> polyin;//内含多边形的点
edge tmpedge;
position tmp ;
color purple(0.855, 0.439, 0.839);//紫色
color white;
color black(0.0, 0.0, 0.0);
color orange(0.98, 0.43, 0.098);
color skyblue(0.529, 0.808, 0.921);
float cenx = 0, ceny = 0;//多边形中心坐标（左下角为0,0）
const int weight = 800, height = 500;
float mx, my;//鼠标相对位置（左上角为0,0）


enum Mode { draw, dig, translation, rotation, scale, vacant, modify };
Mode modes = draw;

//用当前颜色画点
void drawadot(int x, int y, color col)
{
	glPointSize(5);
	glColor3f(col.red, col.green, col.blue);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	
	glColor3f(purple.red, purple.green, purple.blue);
	for (int i = 0; i < poly.size(); i++)
		glVertex2f(int(poly[i].x + 0.5), int(poly[i].y + 0.5));
	glColor3f(white.red, white.green, white.blue);
	for (int i = 0; i < polyin.size(); i++)
		glVertex2f(int(polyin[i].x + 0.5), int(polyin[i].y + 0.5));
	glEnd();
	//glFlush();
	glutSwapBuffers();
}
void drawdots(vector<position> tmp)
{
	for (int i = 0; i < tmp.size(); i++)
		glVertex2f(int(tmp[i].x + 0.5), int(tmp[i].y + 0.5));
}

void mPolyScan(vector<position> tvp)
{
	/******计算最高点和最低的y坐标(扫描到此结束)****************************************/
	//if (tvp.size() == 0)
	//	return;
	int maxy = 0, miny = height;
	for (int i = 0; i < tvp.size(); i++)
	{
		if (tvp[i].y > maxy)
			maxy = tvp[i].y;
		if (tvp[i].y < miny)
			miny = tvp[i].y;
	}
	cout << "maxy=" << maxy << "miny" << miny << endl;

	/*******初始化AET表***********************************************************/
	AET *pAET = new AET();

	/******初始化NET表************************************************************/
	//int leng = maxy - miny + 1;

	NET *pNET[10 * height];
	//NET *pNET = new NET[maxy - miny + 1];
	//if (maxy >= 2 * height || miny <= 0)
	//return;
	for (int i = 0; i <= maxy - miny; i++)
	{
		pNET[i] = new NET();
	}
 

	/******扫描并建立NET表*********************************************************/
	for (int i = 0; i <= maxy - miny; i++)
	{
		for (int j = 0; j < tvp.size(); j++)
		{
			if (int(tvp[j].y + 0.5) == (i + miny))
			{//一个点跟前面的一个点形成一条线段，跟后面的点也形成线段
				int fore = (j - 1 + tvp.size()) % tvp.size();
				int after = (j + 1 + tvp.size()) % tvp.size();
				if (tvp[fore].y > tvp[j].y)
				{
					NET *p = new NET();
					p->x = tvp[j].x;
					p->ymax = int(tvp[fore].y + 0.5);
					p->dx = (tvp[fore].x - tvp[j].x) / (tvp[fore].y - tvp[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;

				}
				if (tvp[after].y > tvp[j].y)
				{
					NET *p = new NET();
					p->x = tvp[j].x;
					p->ymax = int(tvp[after].y + 0.5);
					p->dx = (tvp[after].x - tvp[j].x) / (tvp[after].y - tvp[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
			}
		}

	}
	/******建立并更新活性边表AET*****************************************************/

	for (int i = 0; i <= maxy - miny; i++)
	{
		//计算新的交点x,更新AET
		NET *p = pAET->next;
		while (p)
		{
			p->x = p->x + p->dx;
			p = p->next;
		}
		//更新后新AET先排序*************************************************************/
		//断表排序,不再开辟空间
		AET *tq = pAET;
		p = pAET->next;
		tq->next = NULL;
		while (p)
		{
			while (tq->next && p->x >= tq->next->x)
				tq = tq->next;
			NET *s = p->next;
			p->next = tq->next;
			tq->next = p;
			p = s;
			tq = pAET;
		}
		//(改进算法)先从AET表中删除ymax==i的结点****************************************/
		AET *q = pAET;
		p = q->next;
		while (p)
		{
			if (p->ymax == (i + miny))
			{
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else
			{
				q = q->next;
				p = q->next;
			}
		}
		//将NET中的新点加入AET,并用插入法按X值递增排序**********************************/
		p = pNET[i]->next;
		q = pAET;
		while (p)
		{
			while (q->next && p->x >= q->next->x)
				q = q->next;
			NET *s = p->next;
			p->next = q->next;
			q->next = p;
			p = s;
			q = pAET;
		}
		/******配对填充颜色***************************************************************/


		p = pAET->next;
		while (p && p->next)
		{
			for (float j = p->x; j <= p->next->x; j++)
				glVertex2i((int)(j + 0.5), (i + miny));
			p = p->next->next;//考虑端点情况
		}

		//cout << "扫描中\n";
	}
	delete pAET;


}

void PolyScan(vector<position> tvp, color col)
{
	/******计算最高点和最低的y坐标(扫描到此结束)****************************************/
	//if (tvp.size() == 0)
	//	return;
	int maxy = 0, miny = height;
	for (int i = 0; i < tvp.size(); i++)
	{
		if (tvp[i].y > maxy)
			maxy = tvp[i].y;
		if (tvp[i].y < miny)
			miny = tvp[i].y;
	}
	cout << "maxy=" << maxy << "miny" << miny << endl;

	/*******初始化AET表***********************************************************/
	AET *pAET = new AET();

	/******初始化NET表************************************************************/
	//int leng = maxy - miny + 1;
	
	NET *pNET[10*height];
	//NET *pNET = new NET[maxy - miny + 1];
	//if (maxy >= 2 * height || miny <= 0)
		//return;
	for (int i = 0; i <= maxy - miny; i++)
	{
		pNET[i] = new NET();
	}
	//glClear(GL_COLOR_BUFFER_BIT);        //赋值的窗口显示.  
	glColor3f(col.red, col.green, col.blue);             //设置直线的颜色紫色
	glPointSize(1);
	glBegin(GL_POINTS);
	/******扫描并建立NET表*********************************************************/
	for (int i = 0; i <= maxy - miny; i++)
	{
		for (int j = 0; j < tvp.size(); j++)
		{   
			if (int(tvp[j].y + 0.5) == (i + miny))
			{//一个点跟前面的一个点形成一条线段，跟后面的点也形成线段
				int fore = (j - 1 + tvp.size()) % tvp.size();
				int after = (j + 1 + tvp.size()) % tvp.size();
				if (tvp[fore].y > tvp[j].y)
				{
					NET *p = new NET();
					p->x = tvp[j].x;
					p->ymax = int(tvp[fore].y + 0.5);
					p->dx = (tvp[fore].x - tvp[j].x) / (tvp[fore].y - tvp[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;

				}
				if (tvp[after].y > tvp[j].y)
				{
					NET *p = new NET();
					p->x = tvp[j].x;
					p->ymax = int(tvp[after].y + 0.5);
					p->dx = (tvp[after].x - tvp[j].x) / (tvp[after].y - tvp[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
			}	
		}

	}
	/******建立并更新活性边表AET*****************************************************/

	for (int i = 0; i <= maxy - miny; i++)
	{
		//计算新的交点x,更新AET
		NET *p = pAET->next;
		while (p)
		{
			p->x = p->x + p->dx;
			p = p->next;
		}
		//更新后新AET先排序*************************************************************/
		//断表排序,不再开辟空间
		AET *tq = pAET;
		p = pAET->next;
		tq->next = NULL;
		while (p)
		{
			while (tq->next && p->x >= tq->next->x)
				tq = tq->next;
			NET *s = p->next;
			p->next = tq->next;
			tq->next = p;
			p = s;
			tq = pAET;
		}
		//(改进算法)先从AET表中删除ymax==i的结点****************************************/
		AET *q = pAET;
		p = q->next;
		while (p)
		{
			if (p->ymax == (i + miny))
			{
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else
			{
				q = q->next;
				p = q->next;
			}
		}
		//将NET中的新点加入AET,并用插入法按X值递增排序**********************************/
		p = pNET[i]->next;
		q = pAET;
		while (p)
		{
			while (q->next && p->x >= q->next->x)
				q = q->next;
			NET *s = p->next;
			p->next = q->next;
			q->next = p;
			p = s;
			q = pAET;
		}
		/******配对填充颜色***************************************************************/


		p = pAET->next;
		while (p && p->next)
		{
			for (float j = p->x; j <= p->next->x; j++)
				glVertex2i((int)(j + 0.5), (i + miny));
			p = p->next->next;//考虑端点情况
		}

		//cout << "扫描中\n";
	}
	delete pAET;

	
}



//计算中心坐标
void calcen()
{
	float sumx = 0, sumy = 0;
	for (int i = 0; i < poly.size(); i++)
	{
		sumx += poly[i].x;
		sumy += poly[i].y;
	}
	if (poly.size() > 0)
	{
		cenx = sumx / poly.size();
		ceny = sumy / poly.size();

	}
}

//通过点集计算边集
void caledge()
{
	polyedge.clear();
	float x1, x2, y1, y2;
	
	for (int i = 0; i < poly.size(); i++)
	{
		x1 = poly[i].x; y1 = poly[i].y;
		x2 = poly[(i + 1) % poly.size()].x; y2 = poly[(i + 1) % poly.size()].y;

		if (x1 != x2)
		{
			tmpedge.existk = true;
			tmpedge.k = (y1 - y2) / (x1 - x2);
			tmpedge.t = y1 - tmpedge.k*x1;

			tmpedge.a = y1 - y2;
			tmpedge.b = -(x1 - x2);
			tmpedge.c = tmpedge.t * (x1 - x2);

			if (x1 > x2)
			{
				tmp.x = x1; tmp.y = y1;
				tmpedge.start = tmp;
				tmp.x = x2; tmp.y = y2;
				tmpedge.end = tmp;
			}
			else
			{
				tmp.x = x2; tmp.y = y2;
				tmpedge.start = tmp;
				tmp.x = x1; tmp.y = y1;
				tmpedge.end = tmp;
			}
		}
		else
		{
			tmpedge.existk = false;
			tmpedge.a = 1;
			tmpedge.b = 0;
			tmpedge.c = -x1;

			tmp.x = x1; tmp.y = y1 > y2 ? y1 : y2;
			tmpedge.start = tmp;
			tmp.x = x2; tmp.y = y1 > y2 ? y2 : y1;
			tmpedge.end = tmp;
		}
		polyedge.push_back(tmpedge);
	}
}

//平移
void Translate(float px, float py)
{
	for (int i = 0; i < poly.size(); i++)
	{
		poly[i].x += px;
		poly[i].y -= py;
	}
	for (int i = 0; i < polyin.size(); i++)
	{
		polyin[i].x += px;
		polyin[i].y -= py;
	}
}

//缩放
void Scale(float sx, float sy, int index)
{
	if (index == 1)
	{
		for (int i = 0; i < poly.size(); i++)
		{
			poly[i].x = poly[i].x * sx + mx * (1 - sx);
			poly[i].y = poly[i].y * sy + (height - my) * (1 - sy);
		}
		for (int i = 0; i < polyin.size(); i++)
		{
			polyin[i].x = polyin[i].x * sx + cenx * (1 - sx);
			polyin[i].y = polyin[i].y * sy + (height - my) * (1 - sy);
		}
	}
	else
	{
		for (int i = 0; i < poly.size(); i++)
		{
			poly[i].x = poly[i].x * sx + cenx * (1 - sx);
			poly[i].y = poly[i].y * sy + ceny * (1 - sy);
		}
		for (int i = 0; i < polyin.size(); i++)
		{
			polyin[i].x = polyin[i].x * sx + cenx * (1 - sx);
			polyin[i].y = polyin[i].y * sy + ceny * (1 - sy);
		}
	}

}

//旋转，i>0为逆时针，i<=0为顺时针
void Rotate(int i)
{
	float theta = 0;
	if (i > 0)
		theta = -PI / 90;
	else
		theta = PI / 90;

	for (int i = 0; i < poly.size(); i++)
	{
		poly[i].x = cenx + (poly[i].x - cenx)*cos(theta) - (poly[i].y - ceny)*sin(theta);
		poly[i].y = ceny + (poly[i].x - cenx)*sin(theta) + (poly[i].y - ceny)*cos(theta);
	}
	for (int i = 0; i < polyin.size(); i++)
	{
		polyin[i].x = cenx + (polyin[i].x - cenx)*cos(theta) - (polyin[i].y - ceny)*sin(theta);
		polyin[i].y = ceny + (polyin[i].x - cenx)*sin(theta) + (polyin[i].y - ceny)*cos(theta);
	}
}




int judge(float x, float y)
{
	float r = 10;
	for (int i = 0; i < poly.size(); i++)
	{
		if (pow((poly[i].x - x), 2) + pow((poly[i].y - y), 2) < pow(r, 2))
		{
			return i;
		}
		
		
	}
	for (int i = 0; i < polyin.size(); i++)
	{
		if (pow((polyin[i].x - x), 2) + pow((polyin[i].y - y), 2) < pow(r, 2))
		{
			return 100 + i;
		}


	}
	return -1;
}

void judgeedge(float x, float y)
{
	float dis = 5;
	position pt(x, y);
	cout << "jedgeedge函数中\n";
	for (int i = 0; i < polyedge.size(); i++)
	{
		cout << "第" << i << "条边:";
		tmpedge = polyedge[i];
		cout << tmpedge.a << " * x + " << tmpedge.b << " * y + " << tmpedge.c << " = 0\t";
		cout << tmpedge.start << "  " << tmpedge.end << "\n";
		if (pt >= tmpedge.start&&pt <= tmpedge.end)
		{//在此边端点限制的x,y区间之内
			cout <<pt << "在端点区间之内\t";
			if (abs(tmpedge.a*x + tmpedge.b*y + tmpedge.c) / sqrt(pow(tmpedge.a, 2) + pow(tmpedge.b, 2)) < dis)
			{//在此边的选取误差之内
				cout << "可插入点\n";
				poly.insert(poly.begin() + i, pt);
				//polyedge.insert(ployedge.begin()+)
				break;
			}
		}

		
		
	}



}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);//设置背景颜色，此处为黑色
	glClear(GL_COLOR_BUFFER_BIT);//用当前背景色填充窗口，此处为黑色
	glColor3f(1.0, 0.0, 1.0);//设置绘制颜色，此处为紫色
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, weight, 0, height);
	//gluOrtho2D(-weight / 2, weight / 2, -height / 2, height / 2);
	//glViewport(-weight / 2, weight / 2, -height / 2, height / 2);

	
}
void display(void)
{
	//cout << "display\n";

	if (modes == draw)
	{

	}
	else if (modes == dig)
	{

	}
	else
	{

		calcen();//重新计算中心
		caledge();//重新计算边
		cout << "中心坐标(" << cenx << "," << ceny << ")\n";
		
		
		glClear(GL_COLOR_BUFFER_BIT);//用当前背景色填充窗口，此处为黑色            
		
		glPointSize(1);
		glBegin(GL_POINTS);

		glColor3f(skyblue.red, skyblue.green, skyblue.blue);
		mPolyScan(poly);
		glColor3f(black.red, black.green, black.blue);
		mPolyScan(polyin);

		glEnd();


		glPointSize(5);
		glBegin(GL_POINTS);

		glColor3f(purple.red, purple.green, purple.blue);
		drawdots(poly);

		glColor3f(white.red, white.green, white.blue);
		drawdots(polyin);

		glEnd();
		//glFlush();
		glutSwapBuffers();


		/*
		
		glClear(GL_COLOR_BUFFER_BIT);//用当前背景色填充窗口，此处为黑色
		glFrontFace(GL_CCW); // 设置逆时针方向为正面
		glPolygonMode(GL_FRONT, GL_FILL); // 设置正面为填充模式
		glPolygonMode(GL_BACK, GL_LINE); // 设置反面为线形模式
		
		glColor3f(1.0, 0.0, 1.0);//紫色
		//逆时针绘制一个 正方形
		glBegin(GL_POLYGON);
		for (int i = 0; i < poly.size(); i++)
		{
			glVertex2f(poly[i].x, poly[i].y);
		}

		glEnd();


		glColor3f(0.0, 0.0, 0.0);//背景色
		//逆时针绘制一个 正方形
		glBegin(GL_POLYGON);
		for (int i = 0; i < polyin.size(); i++)
		{
			glVertex2f(polyin[i].x, polyin[i].y);
		}
		glEnd();

		glutSwapBuffers();   //双缓冲的刷新模式；*/
	}




}
void reshape(int w, int h)
{
	//cout << "w =" << w << "  h = " << h << endl;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	//gluOrtho2D(-(GLdouble)w / 2, (GLdouble)w / 2, -(GLdouble)h / 2, (GLdouble)h / 2);
}

//鼠标点击事件
void myMouse(int button, int state, int x, int y) 
{
	
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (modes == draw)
		{
			drawadot(x, height - y, purple);
			//cout << "\n鼠标点击坐标：（" << x << "，" << y << "）\n";
			cout << "添加外点投影坐标：（" << x << "，" << height - y<< "）\n\n";
			tmp.x = x;
			tmp.y = height - y;
			poly.push_back(tmp);
		}
		else if (modes == dig)
		{
			
			drawadot(x, height - y, white);
			//cout << "\n鼠标点击坐标：（" << x << "，" << y << "）\n";
			cout << "添加内点投影坐标：（" << x << "，" << height - y << "）\n\n";
			tmp.x = x;
			tmp.y = height - y;
			polyin.push_back(tmp);
		}
		mx = x;
		my = y;
		cout << "按下鼠标左键\t(" << x << "," << height - y << ")\n";
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		cout << "按下鼠标右键\t";
		modes = translation;
	}
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		cout << "按下滚轮键\t";
		

	}

	
	if (button == GLUT_WHEEL_DOWN)
	{


		Scale(0.9, 0.9, 0);
		cout << "滚轮向下滚动\n";
	}
	if (button == GLUT_WHEEL_UP)
	{

		Scale(1.1, 1.1, 0);
		cout << "滚轮向上滚动\n";
	}

	glutPostRedisplay();

}
// 鼠标按下并移动事件 
void myMouseMove(int x, int y)
{




	float px = x - mx;//计算平移量
	float py = y - my;
	mx = x, my = y;//更新mx与my

	if (modes == translation)
	{


		Translate(px, py);

		//glTranslatef(px, -py, 0);//感觉像是移动了坐标轴
	}
	else if (modes == rotation)
	{
	
		Rotate(px);

	}
	else if (modes == scale)
	{

		float sx = 1, sy = 1;
		if (px > 0)
		{
			Scale(1.1, 1.1, 0);
		}
		else if (px < 0)
		{
			Scale(0.9, 0.9, 0);
		}

	}
	else if (modes == modify)
	{
		float cx = mx;
		float cy = height - my;
		int i = judge(cx, cy);
		if (i >= 0 && i < 100&& i < poly.size())
		{
			poly[i].x = cx;
			poly[i].y = cy;
		}
		else if (i >= 100 && (i - 100) < poly.size())
		{
			polyin[i - 100].x = cx;
			polyin[i - 100].y = cy;
		}
		//else
			//judgeedge(cx, cy);

	}



	glutPostRedisplay();
	cout << "按下并移动鼠标中\t(" << x << "," << y <<" )\n";

}

//鼠标移动监听函数（仅移动）
void myMouseOnlyMove(int x, int y)
{
	mx = x;
	my = y;

	//cout << "\n移动鼠标中\t" << x << "  " << y  << "\n";
	//cout << "鼠标移动中投影坐标：（" << x << "，" << height - y << "）\n\n";
}

//键盘按键监听函数
void myKeyboard(unsigned char key, int x, int y) 
{

	switch (key)
	{

	case 'a':
		modes = draw;
		break;
	case 'x':
		modes = dig;
		break;
	case 'r':
		modes = rotation;
		break;
	case 't':
		modes = translation;
		break;
	case 's':
		modes = scale;
		break;
	case 'c':
		cout << modes << "\n";
		for (int i = 0; i < poly.size(); i++)
		{
			cout << "打印坐标：（" << poly[i].x << "，" << poly[i].y << "）\n";
		}
		break;
	case 'd':
		glClear(GL_COLOR_BUFFER_BIT);//用当前背景色填充窗口，此处为黑色
		glFlush();   //刷新窗口以显示当前绘制图形
		poly.clear();
		polyedge.clear();
		polyin.clear();
		cout << "清屏\n";
		modes = draw;
		break;
	case 'm':
		modes = modify;
		break;
	default:
		break;
	}


	glutPostRedisplay();
}
//键盘是否松开某些键监听事件
/*void myKeyboardup(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		//mode = vacant;
		modes = draw;
		break;
	case 'r':
		//mode = vacant;
		modes = rotation;
		break;
	case 't':
		//mode = vacant;
		modes = translation;
		break;
	case 'x':
		modes = dig;
		break;
	case 'm':
		modes = modify;
		break;
	case 's':
		//mode = vacant;
		modes = scale;
		break;
	default:
		break;
	}

	glutPostRedisplay();
	cout << "松开键盘\n";
}*/

//高级键盘监听事件
void mySpecialKey(GLint key, GLint x, GLint y)
{
	if (key == GLUT_KEY_UP)
	{
		Translate(0, -5);
	}
	if (key == GLUT_KEY_LEFT)
	{
		Translate(-5, 0);
	}
	if (key == GLUT_KEY_DOWN)
	{
		Translate(0, 5);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		Translate(5, 0);
	}
	int mod = glutGetModifiers();
	if (mod == (GLUT_ACTIVE_CTRL)) {
		//TODO
		cout << "按下了ctrl\n";
	}
	glutPostRedisplay();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//固定格式
	glutInitDisplayMode(GLUT_RED | GLUT_DOUBLE);//缓存模式
	glutInitWindowSize(weight, height);//窗口大小
	glutInitWindowPosition(150, 150);//窗口位置（左上角位置）
	glutCreateWindow("绘制多边形");

	init();
	glutDisplayFunc(display);

	glutMouseFunc(myMouse);//鼠标点击事件监听，点击或松开
	glutMotionFunc(myMouseMove);//鼠标移动事件监听，按下并移动
	glutPassiveMotionFunc(myMouseOnlyMove);//鼠标移动事件监听，仅移动

	glutKeyboardFunc(myKeyboard);//键盘点击事件监听
	//glutKeyboardUpFunc(myKeyboardup);//键盘点击事件监听,松开时

	glutSpecialFunc(mySpecialKey);//高级键盘点击监听事件
	//glutEntryFunc();//鼠标进入窗口监听事件
	//glutReshapeFunc(reshape);
	glutMainLoop(); //进人GLUT事件处理循环


	return 0;
}

