#pragma once
#include<iostream>
using namespace std;

/******定义结构体用于活性边表AET和新边表NET***********************************/
typedef struct XET
{
	float x;
	float dx, ymax;
	XET* next;

	XET() { x = 0; dx = 0; ymax = 0; next = NULL; }
	XET(float x, float ymax, float dx) : x(x), ymax(ymax), dx(dx){ }
}AET, NET;

struct position
{
	float x;
	float y;

	position() { x = 0; y = 0; }
	position(float x, float y) :x(x), y(y) { }

	//int operator =(const edge &a);
	friend bool operator >(const position &a, const position &b)
	{
		if (a.x == b.x)
			return a.y > b.y;
		else
			return a.x > b.x;
	}
	friend bool operator >=(const position &a, const position &b)
	{
		if (a.x == b.x)
			return a.y >= b.y;
		else
			return a.x >= b.x;
	}
	friend bool operator <(const position &a, const position &b)
	{
		if (a.x == b.x)
			return a.y < b.y;
		else
			return a.x < b.x;
	}
	friend bool operator <=(const position &a, const position &b)
	{
		if (a.x == b.x)
			return a.y <= b.y;
		else
			return a.x <= b.x;
	}
	/*friend bool operator ==(const position &a, const position &b);
	friend bool operator !=(const position &a, const position &b);
	friend position operator + (const position &a, const position &b);
	friend position operator - (const position &a, const position &b);*/
	friend ostream& operator << (ostream &out, const position &p)
	{
		out << "(" << p.x << ", " << p.y << ")\n";
		return out;
	}
};
struct edge
{
	float a, b, c;
	float k, t;
	bool existk;
	position start;
	position end;
};
struct color
{
	float red;
	float green;
	float blue;
	color() { red = 1; green = 1; blue = 1;}
	color(float red, float green, float blue) : red(red), green(green), blue(blue) { }
};


