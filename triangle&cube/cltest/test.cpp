#include <gl/glut.h>  //������ذ�

int w = 600, h = 600;

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);  //�����ɫ������
	//glColor3f(1, 1, 1);   //����ɫΪ��ɫ

	glViewport(0, 0, w, h);

	/*glBegin(GL_LINES);
	glVertex2f(0, -2.0);
	glVertex2f(0, 2.0);
	glEnd();*/

	glColor3f(0, 1, 1);   //����ɫΪ����ɫ

	glViewport(0, 0, w/2, h);
	glLoadIdentity();   //��վ���
	glTranslatef(0, 0, -5); //��������X��������ƽ��x����λ(x���з�����)����Y��������ƽ��y����λ(y���з�����)����Z��������ƽ��z����λ(z���з�����)
	glRotatef(30, 0, 1, 0);//���������Ŵ�(0,0,0)��(x,y,z)��ֱ����תangle��(���ֶ���)
	glScalef(1, 2, 1);  //��������X��Ŵ�x������Y��Ŵ�y������Z��Ŵ�z��

	//glScalef(1, 2, 1);
	//gluLookAt(0,0,5,0,0,0,0,2,0); //�۲�λ����(0,0,5)������λ��(0,0,0)���Դ�����(0,2,0)

	glutWireCube(1.0); //����ʵ����������߿�������

	glViewport(w/2, 0, w/2, h);
	//glLoadIdentity();
	//glTranslatef(-2, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(1.5, 0.0);
	glEnd();



	glFlush();   //ˢ�´�������ʾ��ǰ����ͼ��
}
void init(void)
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT); //ѡ��ƽ������ģʽ��⻬����ģʽ
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);   //���û���
	glMatrixMode(GL_PROJECTION);  //ָ����һ�������ǵ�ǰ����
	glLoadIdentity();
	gluPerspective(60, 1, 1.5, 20);   //����͸��ͶӰ����(fovy,aspect,zNear,zFar);
	//glFrustum(-1,1,-1,1,1.5,20.0);  //��͸�Ӿ�����Ե�ǰ����(left,Right,bottom,top,near,far);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv); //�̶���ʽ
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //����ģʽ
	glutInitWindowSize(w, h);    //��ʾ��Ĵ�С
	glutInitWindowPosition(400, 400); //ȷ����ʾ�����Ͻǵ�λ��
	glutCreateWindow("�����������������");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop(); //����GLUT�¼�����ѭ��
	return 0;
}
