#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<math.h>
#include "now.h"
using namespace std;
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#define PI 3.1415926535


vector<position> poly;//��Χ����εĵ�
vector<edge> polyedge;//��Χ����εıߣ���ʱδʵ��
vector<position> polyin;//�ں�����εĵ�
edge tmpedge;
position tmp ;
color purple(0.855, 0.439, 0.839);//��ɫ
color white;
color black(0.0, 0.0, 0.0);
color orange(0.98, 0.43, 0.098);
color skyblue(0.529, 0.808, 0.921);
float cenx = 0, ceny = 0;//������������꣨���½�Ϊ0,0��
const int weight = 800, height = 500;
float mx, my;//������λ�ã����Ͻ�Ϊ0,0��


enum Mode { draw, dig, translation, rotation, scale, vacant, modify };
Mode modes = draw;

//�õ�ǰ��ɫ����
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
	/******������ߵ����͵�y����(ɨ�赽�˽���)****************************************/
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

	/*******��ʼ��AET��***********************************************************/
	AET *pAET = new AET();

	/******��ʼ��NET��************************************************************/
	//int leng = maxy - miny + 1;

	NET *pNET[10 * height];
	//NET *pNET = new NET[maxy - miny + 1];
	//if (maxy >= 2 * height || miny <= 0)
	//return;
	for (int i = 0; i <= maxy - miny; i++)
	{
		pNET[i] = new NET();
	}
 

	/******ɨ�貢����NET��*********************************************************/
	for (int i = 0; i <= maxy - miny; i++)
	{
		for (int j = 0; j < tvp.size(); j++)
		{
			if (int(tvp[j].y + 0.5) == (i + miny))
			{//һ�����ǰ���һ�����γ�һ���߶Σ�������ĵ�Ҳ�γ��߶�
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
	/******���������»��Ա߱�AET*****************************************************/

	for (int i = 0; i <= maxy - miny; i++)
	{
		//�����µĽ���x,����AET
		NET *p = pAET->next;
		while (p)
		{
			p->x = p->x + p->dx;
			p = p->next;
		}
		//���º���AET������*************************************************************/
		//�ϱ�����,���ٿ��ٿռ�
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
		//(�Ľ��㷨)�ȴ�AET����ɾ��ymax==i�Ľ��****************************************/
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
		//��NET�е��µ����AET,���ò��뷨��Xֵ��������**********************************/
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
		/******��������ɫ***************************************************************/


		p = pAET->next;
		while (p && p->next)
		{
			for (float j = p->x; j <= p->next->x; j++)
				glVertex2i((int)(j + 0.5), (i + miny));
			p = p->next->next;//���Ƕ˵����
		}

		//cout << "ɨ����\n";
	}
	delete pAET;


}

void PolyScan(vector<position> tvp, color col)
{
	/******������ߵ����͵�y����(ɨ�赽�˽���)****************************************/
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

	/*******��ʼ��AET��***********************************************************/
	AET *pAET = new AET();

	/******��ʼ��NET��************************************************************/
	//int leng = maxy - miny + 1;
	
	NET *pNET[10*height];
	//NET *pNET = new NET[maxy - miny + 1];
	//if (maxy >= 2 * height || miny <= 0)
		//return;
	for (int i = 0; i <= maxy - miny; i++)
	{
		pNET[i] = new NET();
	}
	//glClear(GL_COLOR_BUFFER_BIT);        //��ֵ�Ĵ�����ʾ.  
	glColor3f(col.red, col.green, col.blue);             //����ֱ�ߵ���ɫ��ɫ
	glPointSize(1);
	glBegin(GL_POINTS);
	/******ɨ�貢����NET��*********************************************************/
	for (int i = 0; i <= maxy - miny; i++)
	{
		for (int j = 0; j < tvp.size(); j++)
		{   
			if (int(tvp[j].y + 0.5) == (i + miny))
			{//һ�����ǰ���һ�����γ�һ���߶Σ�������ĵ�Ҳ�γ��߶�
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
	/******���������»��Ա߱�AET*****************************************************/

	for (int i = 0; i <= maxy - miny; i++)
	{
		//�����µĽ���x,����AET
		NET *p = pAET->next;
		while (p)
		{
			p->x = p->x + p->dx;
			p = p->next;
		}
		//���º���AET������*************************************************************/
		//�ϱ�����,���ٿ��ٿռ�
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
		//(�Ľ��㷨)�ȴ�AET����ɾ��ymax==i�Ľ��****************************************/
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
		//��NET�е��µ����AET,���ò��뷨��Xֵ��������**********************************/
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
		/******��������ɫ***************************************************************/


		p = pAET->next;
		while (p && p->next)
		{
			for (float j = p->x; j <= p->next->x; j++)
				glVertex2i((int)(j + 0.5), (i + miny));
			p = p->next->next;//���Ƕ˵����
		}

		//cout << "ɨ����\n";
	}
	delete pAET;

	
}



//������������
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

//ͨ���㼯����߼�
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

//ƽ��
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

//����
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

//��ת��i>0Ϊ��ʱ�룬i<=0Ϊ˳ʱ��
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
	cout << "jedgeedge������\n";
	for (int i = 0; i < polyedge.size(); i++)
	{
		cout << "��" << i << "����:";
		tmpedge = polyedge[i];
		cout << tmpedge.a << " * x + " << tmpedge.b << " * y + " << tmpedge.c << " = 0\t";
		cout << tmpedge.start << "  " << tmpedge.end << "\n";
		if (pt >= tmpedge.start&&pt <= tmpedge.end)
		{//�ڴ˱߶˵����Ƶ�x,y����֮��
			cout <<pt << "�ڶ˵�����֮��\t";
			if (abs(tmpedge.a*x + tmpedge.b*y + tmpedge.c) / sqrt(pow(tmpedge.a, 2) + pow(tmpedge.b, 2)) < dis)
			{//�ڴ˱ߵ�ѡȡ���֮��
				cout << "�ɲ����\n";
				poly.insert(poly.begin() + i, pt);
				//polyedge.insert(ployedge.begin()+)
				break;
			}
		}

		
		
	}



}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);//���ñ�����ɫ���˴�Ϊ��ɫ
	glClear(GL_COLOR_BUFFER_BIT);//�õ�ǰ����ɫ��䴰�ڣ��˴�Ϊ��ɫ
	glColor3f(1.0, 0.0, 1.0);//���û�����ɫ���˴�Ϊ��ɫ
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

		calcen();//���¼�������
		caledge();//���¼����
		cout << "��������(" << cenx << "," << ceny << ")\n";
		
		
		glClear(GL_COLOR_BUFFER_BIT);//�õ�ǰ����ɫ��䴰�ڣ��˴�Ϊ��ɫ            
		
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
		
		glClear(GL_COLOR_BUFFER_BIT);//�õ�ǰ����ɫ��䴰�ڣ��˴�Ϊ��ɫ
		glFrontFace(GL_CCW); // ������ʱ�뷽��Ϊ����
		glPolygonMode(GL_FRONT, GL_FILL); // ��������Ϊ���ģʽ
		glPolygonMode(GL_BACK, GL_LINE); // ���÷���Ϊ����ģʽ
		
		glColor3f(1.0, 0.0, 1.0);//��ɫ
		//��ʱ�����һ�� ������
		glBegin(GL_POLYGON);
		for (int i = 0; i < poly.size(); i++)
		{
			glVertex2f(poly[i].x, poly[i].y);
		}

		glEnd();


		glColor3f(0.0, 0.0, 0.0);//����ɫ
		//��ʱ�����һ�� ������
		glBegin(GL_POLYGON);
		for (int i = 0; i < polyin.size(); i++)
		{
			glVertex2f(polyin[i].x, polyin[i].y);
		}
		glEnd();

		glutSwapBuffers();   //˫�����ˢ��ģʽ��*/
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

//������¼�
void myMouse(int button, int state, int x, int y) 
{
	
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (modes == draw)
		{
			drawadot(x, height - y, purple);
			//cout << "\n��������꣺��" << x << "��" << y << "��\n";
			cout << "������ͶӰ���꣺��" << x << "��" << height - y<< "��\n\n";
			tmp.x = x;
			tmp.y = height - y;
			poly.push_back(tmp);
		}
		else if (modes == dig)
		{
			
			drawadot(x, height - y, white);
			//cout << "\n��������꣺��" << x << "��" << y << "��\n";
			cout << "����ڵ�ͶӰ���꣺��" << x << "��" << height - y << "��\n\n";
			tmp.x = x;
			tmp.y = height - y;
			polyin.push_back(tmp);
		}
		mx = x;
		my = y;
		cout << "����������\t(" << x << "," << height - y << ")\n";
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		cout << "��������Ҽ�\t";
		modes = translation;
	}
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		cout << "���¹��ּ�\t";
		

	}

	
	if (button == GLUT_WHEEL_DOWN)
	{


		Scale(0.9, 0.9, 0);
		cout << "�������¹���\n";
	}
	if (button == GLUT_WHEEL_UP)
	{

		Scale(1.1, 1.1, 0);
		cout << "�������Ϲ���\n";
	}

	glutPostRedisplay();

}
// ��갴�²��ƶ��¼� 
void myMouseMove(int x, int y)
{




	float px = x - mx;//����ƽ����
	float py = y - my;
	mx = x, my = y;//����mx��my

	if (modes == translation)
	{


		Translate(px, py);

		//glTranslatef(px, -py, 0);//�о������ƶ���������
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
	cout << "���²��ƶ������\t(" << x << "," << y <<" )\n";

}

//����ƶ��������������ƶ���
void myMouseOnlyMove(int x, int y)
{
	mx = x;
	my = y;

	//cout << "\n�ƶ������\t" << x << "  " << y  << "\n";
	//cout << "����ƶ���ͶӰ���꣺��" << x << "��" << height - y << "��\n\n";
}

//���̰�����������
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
			cout << "��ӡ���꣺��" << poly[i].x << "��" << poly[i].y << "��\n";
		}
		break;
	case 'd':
		glClear(GL_COLOR_BUFFER_BIT);//�õ�ǰ����ɫ��䴰�ڣ��˴�Ϊ��ɫ
		glFlush();   //ˢ�´�������ʾ��ǰ����ͼ��
		poly.clear();
		polyedge.clear();
		polyin.clear();
		cout << "����\n";
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
//�����Ƿ��ɿ�ĳЩ�������¼�
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
	cout << "�ɿ�����\n";
}*/

//�߼����̼����¼�
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
		cout << "������ctrl\n";
	}
	glutPostRedisplay();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//�̶���ʽ
	glutInitDisplayMode(GLUT_RED | GLUT_DOUBLE);//����ģʽ
	glutInitWindowSize(weight, height);//���ڴ�С
	glutInitWindowPosition(150, 150);//����λ�ã����Ͻ�λ�ã�
	glutCreateWindow("���ƶ����");

	init();
	glutDisplayFunc(display);

	glutMouseFunc(myMouse);//������¼�������������ɿ�
	glutMotionFunc(myMouseMove);//����ƶ��¼����������²��ƶ�
	glutPassiveMotionFunc(myMouseOnlyMove);//����ƶ��¼����������ƶ�

	glutKeyboardFunc(myKeyboard);//���̵���¼�����
	//glutKeyboardUpFunc(myKeyboardup);//���̵���¼�����,�ɿ�ʱ

	glutSpecialFunc(mySpecialKey);//�߼����̵�������¼�
	//glutEntryFunc();//�����봰�ڼ����¼�
	//glutReshapeFunc(reshape);
	glutMainLoop(); //����GLUT�¼�����ѭ��


	return 0;
}

