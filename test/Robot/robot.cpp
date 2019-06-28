#include <gl/glut.h>
#include <iostream>
using namespace std;
#define BMP_Header_Length 54  //图像数据在内存块中的偏移量
#define PI 3.1415926535
//定义两个纹理对象编号
GLuint texGround;
GLuint texWall;
GLuint load_texture(const char* file_name);
static double lookx = 0, looky = 0, lookz = 0;//摄像机位置
static double rx = 0, ry = 5.0, rz = 0;//看向位置
static double rxs = 0, rys = 0, rzs = 0;//机器人中心
static int angles = 0;
static int w = 600, h = 600;
static int shoulder = 0, elbow = 0;
static float pace = 0;
static int angle = 0, neck = 0, lshoulder = 0, lelbow = 0, rshoulder = 0, relbow = 0,
lhips = 0, rhips = 0, lfoot = 0, rfoot = 0, flagneck = 0, flaglshoulder = 0,
flaglelbow = 0, flagrshoulder = 0, flagrelbow = 0, flaglhips = 0,
flagrhips = 0, flaglfoot = 0, flagrfoot = 0;
static float height = 0;
void init()
{

	GLfloat light_position[] = { -8.0f, 8.0f, 5.0f, 1.0f }; //光源的位置，齐次坐标形式
	GLfloat light_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f }; //RGBA模式的环境光，为0
	GLfloat light_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f }; //RGBA模式的漫反射光，全白光
	GLfloat light_specular[] = { 0.6f, 0.6f, 0.6f, 1.0f };  //RGBA模式下的镜面光 ，全白光
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//开启灯光
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);    // 启用纹理
	texGround = load_texture("ground.bmp");  //加载纹理
	texWall = load_texture("ground.bmp");
}
void draw_bodym()
{
	glPushMatrix();
	glScalef(0.5, 1, 0.4);
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };  //定义材质的环境光颜色，
	GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，
	GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };   //定义材质的镜面反射光颜色，
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidCube(5);
	height = 5 / 2;
	glPopMatrix();
}
void draw_headm()
{
	glPushMatrix();
	GLfloat mat_ambient[] = { 0.0f, 0.2f, 0.2f, 1.0f };  //定义材质的环境光颜色，
	GLfloat mat_diffuse[] = { 0.0f, 0.5f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，
	GLfloat mat_specular[] = { 0.0f, 0.8f, 0.8f, 1.0f };   //定义材质的镜面反射光颜色，
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glTranslatef(0, height + 2.0, 0);
	glutWireSphere(1.3, 500, 500);

	glPushMatrix();
	glTranslatef(0.5, 0.5, 1.1);
	glutSolidCube(0.25);
	glTranslatef(-1.0, 0.0, 0.0);
	glutSolidCube(0.25);
	glPopMatrix();

	glTranslatef(0.0, -0.5, 1.1);
	glScalef(1.0, 0.3, 0.5);
	glutSolidCube(0.5);
	glPopMatrix();
}
// 函数power_of_two用于判断一个整数是不是2的整数次幂
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 若图像宽高超过了OpenGL规定的最大值，也缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	free(pixels);
	return texture_ID;
}
void draw_body(void) {
	glPushMatrix();
	glTranslatef(0, 1.5, 0);
	glScalef(0.5, 1, 0.4);
	//GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };  //定义材质的环境光颜色，
	//GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，
	//GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };   //定义材质的镜面反射光颜色，
	//GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	//GLfloat mat_shininess = 30.0f;
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	//glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glutSolidCube(4);
	glPopMatrix();
}

void draw_leftshoulder(void) {
	glPushMatrix();
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };  //定义材质的环境光颜色，
	GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，
	GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };   //定义材质的镜面反射光颜色，
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glTranslatef(1.5, 3, 0);
	glRotatef(lshoulder, 1, 0, 0);

	glTranslatef(0, -0.5, 0);
	glScalef(0.4, 1, 0.5);
	glutSolidCube(2);

	glScalef(1 / 0.4, 1 / 1, 1 / 0.5);
	glTranslatef(0, -1.4, 0);
	glRotatef(lelbow, 1, 0, 0);
	glutWireSphere(0.4, 200, 500);

	glScalef(0.4, 1, 0.5);
	glTranslatef(0, -1.4, 0);
	glutSolidCube(2);

	glPopMatrix();
}

void draw_rightshoulder(void) {
	glPushMatrix();
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };  //定义材质的环境光颜色，
	GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，
	GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };   //定义材质的镜面反射光颜色，
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glTranslatef(-1.5, 3, 0);
	glRotatef(rshoulder, 1, 0, 0);

	glTranslatef(0, -0.5, 0);
	glScalef(0.4, 1, 0.5);
	glutSolidCube(2);

	glScalef(1 / 0.4, 1 / 1, 1 / 0.5);
	glTranslatef(0, -1.4, 0);
	glRotatef(relbow, 1, 0, 0);
	glutWireSphere(0.4, 200, 500);

	glScalef(0.4, 1, 0.5);
	glTranslatef(0, -1.4, 0);
	glutSolidCube(2);

	glPopMatrix();
}

void draw_head(void)
{
	glPushMatrix();
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };  //定义材质的环境光颜色，
	GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，
	GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };   //定义材质的镜面反射光颜色，
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glTranslatef(0, 3.5, 0);
	glRotatef(neck, 0, 0, 1);
	glTranslatef(0, 1, 0);
	glutWireSphere(1, 200, 500);

	glPopMatrix();
}

void draw_leftfoot(void) {
	glPushMatrix();
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };  //定义材质的环境光颜色，
	GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，
	GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };   //定义材质的镜面反射光颜色，
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glTranslatef(-0.6, -0.6, 0);
	glRotatef(lfoot, 1, 0, 0);
	glTranslatef(0, -1, 0);
	glScalef(0.4, 1, 0.5);
	glutSolidCube(2);

	glScalef(1 / 0.4, 1 / 1, 1 / 0.5);
	glTranslatef(0, -1.4, 0);
	glRotatef(lhips, 1, 0, 0);
	glutWireSphere(0.4, 200, 500);

	glScalef(0.4, 1, 0.5);
	glTranslatef(0, -1.4, 0);
	glutSolidCube(2);

	glPopMatrix();
}

void draw_rightfoot(void) {
	glPushMatrix();
	//glBindTexture(GL_TEXTURE_2D, texGround);
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };  //定义材质的环境光颜色，
	GLfloat mat_diffuse[] = { 0.0f, 0.5f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，
	GLfloat mat_specular[] = { 0.0f, 0.8f, 0.8f, 1.0f };   //定义材质的镜面反射光颜色，
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glTranslatef(0.6, -0.6, 0);
	glRotatef(rfoot, 1, 0, 0);
	glTranslatef(0, -1, 0);
	glScalef(0.4, 1, 0.5);
	glutSolidCube(2);

	glScalef(1 / 0.4, 1 / 1, 1 / 0.5);
	glTranslatef(0, -1.4, 0);
	glRotatef(rhips, 1, 0, 0);
	glutWireSphere(0.4, 200, 500);

	glScalef(0.4, 1, 0.5);
	glTranslatef(0, -1.4, 0);
	glutSolidCube(2);

	glPopMatrix();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float m[16] = { 0 }; //用来保存当前矩阵数据

	gluLookAt(0.0 + lookx, 10.0 + looky, 30.0 + lookz, rx,  ry, rz, 0.0, 1.0, 0.0);
	//glRotatef(angle, 0, 1, 0);



	//glPushMatrix();
	//glTranslatef(rx, ry, rz);
	//glutSolidCube(1);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0, 0, 0);
	//glutSolidSphere(1, 100, 100);
	//glPopMatrix();



	glPushMatrix();
	//cout << "(" << rxs << "," << rzs << ")" << "\t" << angle << endl << endl;
	glTranslatef(rxs, rys, rzs);
	glRotatef(angle, 0, 1, 0);
	
	

	//glGetFloatv(GL_MODELVIEW_MATRIX, m);
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		cout << m[i * 4 + j] << "  ";
	//	}
	//	cout << endl;
	//}



	glTranslatef(0, 4, 0);
	draw_body();

	draw_head();

	draw_leftshoulder();
	draw_rightshoulder();

	draw_leftfoot();
	draw_rightfoot();

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLfloat)w / (GLfloat)h, 0.1, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0, 10.0, 50.0, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		angle = (angle + 5) % 360;
		glutPostRedisplay();
		break;
	case '2':
		angle = (angle - 5) % 360;
		glutPostRedisplay();
		break;
	case '3':
		if (flagneck) {
			neck = neck + 5;
			if (neck >= 30)flagneck = 0;
		}
		else {
			neck = neck - 5;
			if (neck <= -30)flagneck = 1;
		}
		glutPostRedisplay();
		break;
	case '4':
		if (flaglshoulder) {
			lshoulder += 5;
			if (lshoulder >= 60)flaglshoulder = 0;
		}
		else {
			lshoulder -= 5;
			if (lshoulder <= -60)flaglshoulder = 1;
		}
		if (lshoulder >= 0)
			lelbow = lshoulder * 2 / 3;
		else
			lelbow = 0;
		glutPostRedisplay();
		break;
	case '5':
		if (flagrshoulder) {
			rshoulder += 5;
			if (rshoulder >= 60)flagrshoulder = 0;
		}
		else {
			rshoulder -= 5;
			if (rshoulder <= -60)flagrshoulder = 1;
		}
		if (rshoulder >= 0)
			relbow = rshoulder * 2 / 3;
		else
			relbow = 0;
		glutPostRedisplay();
		break;
	case '6':
		if (flaglelbow) {
			lelbow += 5;
			if (lelbow >= 60)flaglelbow = 0;
		}
		else {
			lelbow -= 5;
			if (lelbow <= -60)flaglelbow = 1;
		}

		glutPostRedisplay();
		break;
	case '7':
		if (flagrelbow) {
			relbow += 5;
			if (relbow >= 60)flagrelbow = 0;
		}
		else {
			relbow -= 5;
			if (relbow <= -60)flagrelbow = 1;
		}
		glutPostRedisplay();
		break;
	case '8':
		if (flaglhips) {
			lhips += 5;
			if (lhips >= 60)flaglhips = 0;
		}
		else {
			lhips -= 5;
			if (lhips <= -60)flaglhips = 1;
		}

		glutPostRedisplay();
		break;
	case '9':
		if (flagrhips) {
			rhips += 5;
			if (rhips >= 60)flagrhips = 0;
		}
		else {
			rhips -= 5;
			if (rhips <= -60)flagrhips = 1;
		}
		glutPostRedisplay();
		break;
	case 'o':
		if (flaglfoot) {
			lfoot += 5;
			if (lfoot >= 30)flaglfoot = 0;
		}
		else {
			lfoot -= 5;
			if (lfoot <= -30)flaglfoot = 1;
		}
		if (lfoot <= 0)
			lhips = lfoot * 2 / 3;
		else
			lhips = 0;
		glutPostRedisplay();
		break;
	case 'p':
		if (flagrfoot) {
			rfoot += 5;
			if (rfoot >= 30)flagrfoot = 0;
		}
		else {
			rfoot -= 5;
			if (rfoot <= -30)flagrfoot = 1;
		}
		if (rfoot <= 0)
			rhips = rfoot * 2 / 3;
		else
			rhips = 0;
		glutPostRedisplay();
		break;
	case 'q':
		lookx += 1;

		glutPostRedisplay();
		break;
	case 'w':
		lookx -= 1;
		glutPostRedisplay();
		break;
	case 'e':
		looky += 1;
		glutPostRedisplay();
		break;
	case 'r':
		looky -= 1;
		glutPostRedisplay();
		break;
	case 't':
		lookz += 1;
		glutPostRedisplay();
		break;
	case 'y':
		lookz -= 1;
		glutPostRedisplay();
		break;
	case 'a':
		rx += 1;

		glutPostRedisplay();
		break;
	case 's':
		rx -= 1;
		glutPostRedisplay();
		break;
	case 'd':
		ry += 1;
		glutPostRedisplay();
		break;
	case 'f':
		ry -= 1;
		glutPostRedisplay();
		break;
	case 'g':
		rz += 1;
		glutPostRedisplay();
		break;
	case 'h':
		rz -= 1;
		glutPostRedisplay();
		break;
	case 'c':
		//cout << rx << " " << ry << " " << rz << endl;
		//cout << lookx << " " << looky << " " << lookz << endl;
		if (lookx >= rx - 0.1 && lookx <= rx + 7.1 && lookz >= rz - 0.1 && lookz <= rz + 7.1)
		{
			lookx += 1;
			lookz -= 1;
		}
		else if (lookx >= rx - 0.1 && lookx <= rx + 7.1 && lookz >= rz - 7.1 && lookz <= rz + 0.1)
		{
			lookx -= 1;
			lookz -= 1;
		}
		else if (lookx >= rx - 7.1 && lookx <= rx + 0.1 && lookz >= rz - 7.1 && lookz <= rz + 0.1)
		{
			lookx -= 1;
			lookz += 1;
		}
		else if (lookx >= rx - 7.1 && lookx <= rx + 0.1 && lookz >= rz - 0.1 && lookz <= rz + 7.1)
		{
			lookx += 1;
			lookz += 1;
		}
		glutPostRedisplay();
		break;
	case 'v':
		rz -= 1;
		glutPostRedisplay();
		break;
	case 'z':

		//cout << angle << endl;
		//cout << rzs << " + = " << 0.1*cos(angle* PI / 180) << "\n" << rxs << " += " << 0.1*sin(angle* PI / 180) << endl;
		rzs -= 0.1*cos(angle* PI / 180);
		rxs -= 0.1*sin(angle* PI / 180);
		
		if (flaglshoulder) {
			lshoulder += 5;
			if (lshoulder >= 30)flaglshoulder = 0;
		}
		else {
			lshoulder -= 5;
			if (lshoulder <= -30)flaglshoulder = 1;
		}
		if (lshoulder >= 0)
			lelbow = lshoulder * 2 / 3;
		else
			lelbow = 0;

		if (flagrshoulder) {
			rshoulder -= 5;
			if (rshoulder <= -30)flagrshoulder = 0;
		}
		else {
			rshoulder += 5;
			if (rshoulder >= 30)flagrshoulder = 1;
		}
		if (rshoulder >= 0)
			relbow = rshoulder * 2 / 3;
		else
			relbow = 0;

		if (flaglfoot) {
			lfoot += 5;
			if (lfoot >= 30)flaglfoot = 0;
		}
		else {
			lfoot -= 5;
			if (lfoot <= -30)flaglfoot = 1;
		}
		if (lfoot <= 0)
			lhips = lfoot * 2 / 3;
		else
			lhips = 0;

		if (flagrfoot) {
			rfoot -= 5;
			if (rfoot <= -30)flagrfoot = 0;
		}
		else {
			rfoot += 5;
			if (rfoot >= 30)flagrfoot = 1;
		}
		if (rfoot <= 0)
			rhips = rfoot * 2 / 3;
		else
			rhips = 0;

		glutPostRedisplay();
		break;
	case 'x':
		//angles += 3;
		pace += 0.3;
		lelbow = 50;
		relbow = 50;
		
		if (flaglshoulder) {
			lshoulder += 5;
			if (lshoulder >= 60)flaglshoulder = 0;
		}
		else {
			lshoulder -= 5;
			if (lshoulder <= -60)flaglshoulder = 1;
		}

		if (flagrshoulder) {
			rshoulder -= 5;
			if (rshoulder <= -60)flagrshoulder = 0;
		}
		else {
			rshoulder += 5;
			if (rshoulder >= 60)flagrshoulder = 1;
		}

		if (flaglfoot) {
			lfoot += 5;
			if (lfoot >= 60)flaglfoot = 0;
		}
		else {
			lfoot -= 5;
			if (lfoot <= -60)flaglfoot = 1;
		}
		if(lfoot >= 0)
			lhips = -lfoot - lfoot;


		if (flagrfoot) {
			rfoot -= 5;
			if (rfoot <= -60)flagrfoot = 0;
		}
		else {
			rfoot += 5;
			if (rfoot >= 60)flagrfoot = 1;
		}
		if(rfoot >= 0)
			rhips = -rfoot - rfoot;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	printf("按键’1’,’2’为整体旋转\n");
	printf("按键’3’为头部旋转\n");
	printf("按键’4’,’5’,’6’,’7’为手臂旋转\n");
	printf("按键’8’,’9’,’o’,’p’为腿部旋转\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
