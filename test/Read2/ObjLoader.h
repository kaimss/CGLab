#pragma once

#include <stdio.h>
#include <gl/glut.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#pragma warning(disable:4996)
class ObjLoader {
public:
	ObjLoader(string filename);//构造函数
	void Draw();//绘制函数
private:
	vector<vector<GLfloat>>vSets;//存放顶点(x,y,z)坐标
	vector<vector<GLint>>fSets;//存放面的三个顶点索引
};

ObjLoader::ObjLoader(string filename)
{
	std::ifstream file(filename);
	std::string line;
	while (getline(file, line))
	{
		if (line.substr(0, 2) == "vt")
		{

		}
		else if (line.substr(0, 2) == "vn")
		{

		}
		else if (line.substr(0, 1) == "v")
		{
			vector<GLfloat> Point;
			GLfloat x, y, z;
			std::istringstream s(line.substr(2));
			s >> x; s >> y; s >> z;
			Point.push_back(x);
			Point.push_back(y);
			Point.push_back(z);
			vSets.push_back(Point);

		}
		else if (line.substr(0, 1) == "f")
		{
			vector<GLint> vIndexSets;
			GLint u, v, w;
			std::istringstream vtns(line.substr(2));
			vtns >> u; vtns >> v; vtns >> w;
			vIndexSets.push_back(u - 1);
			vIndexSets.push_back(v - 1);
			vIndexSets.push_back(w - 1);
			fSets.push_back(vIndexSets);
		}
		else if (line.substr(0, 1) == "#")
		{

		}
		else
		{

		}
	}
	file.close();
}



void ObjLoader::Draw() {

	glBegin(GL_TRIANGLES);//开始绘制
	for (int i = 0; i < fSets.size(); i++) {
		GLfloat VN[3];
		//三个顶点
		GLfloat SV1[3];
		GLfloat SV2[3];
		GLfloat SV3[3];

		if ((fSets[i]).size() != 3) {
			cout << "the fSetsets_Size is not correct" << endl;
		}
		else {
			GLint firstVertexIndex = (fSets[i])[0];//取出顶点索引
			GLint secondVertexIndex = (fSets[i])[1];
			GLint thirdVertexIndex = (fSets[i])[2];

			SV1[0] = (vSets[firstVertexIndex])[0];//第一个顶点
			SV1[1] = (vSets[firstVertexIndex])[1];
			SV1[2] = (vSets[firstVertexIndex])[2];

			SV2[0] = (vSets[secondVertexIndex])[0]; //第二个顶点
			SV2[1] = (vSets[secondVertexIndex])[1];
			SV2[2] = (vSets[secondVertexIndex])[2];

			SV3[0] = (vSets[thirdVertexIndex])[0]; //第三个顶点
			SV3[1] = (vSets[thirdVertexIndex])[1];
			SV3[2] = (vSets[thirdVertexIndex])[2];


			GLfloat vec1[3], vec2[3], vec3[3];//计算法向量
											  //(x2-x1,y2-y1,z2-z1)
			vec1[0] = SV1[0] - SV2[0];
			vec1[1] = SV1[1] - SV2[1];
			vec1[2] = SV1[2] - SV2[2];

			//(x3-x2,y3-y2,z3-z2)
			vec2[0] = SV1[0] - SV3[0];
			vec2[1] = SV1[1] - SV3[1];
			vec2[2] = SV1[2] - SV3[2];

			//(x3-x1,y3-y1,z3-z1)
			vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
			vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
			vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

			GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

			VN[0] = vec3[0] / D;
			VN[1] = vec3[1] / D;
			VN[2] = vec3[2] / D;

			glNormal3f(VN[0], VN[1], VN[2]);//绘制法向量

			glVertex3f(SV1[0], SV1[1], SV1[2]);//绘制三角面片
			glVertex3f(SV2[0], SV2[1], SV2[2]);
			glVertex3f(SV3[0], SV3[1], SV3[2]);
		}
	}
	glEnd();
}