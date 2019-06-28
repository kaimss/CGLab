#pragma once
#include<vector>
using namespace std;
template<class T>
struct position
{
	T x;
	T y;
	position(int x, int y) :x(x), y(y) { }
};
template<class T>
class Polygon
{
public:
	Polygon() 
	{
		n = 0;
	};
	Polygon(vector<position> ver);
	void addVertex(position p);
private:
	int n;
	vector<position> vertex;
};
template<class T>
Polygon::Polygon(vector<position> ver)
{

}
template<class T>
void Polygon::addVertex(position p)
{
	vertex.push_back(p);
	n++;
}


