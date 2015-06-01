#ifndef _ALL_GEOMETRY_
#define _ALL_GEOMETRY_
#include <iostream>
#include <vector>
#include "PointSegmentVector.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
const int Count_Rectangle_Vertices = 4;
const int Count_Triangle_Vertices = 3;


int clockwise(const Point &a, const Point &b, const Point &c)
{
	int x1, y1, x2, y2, x3, y3;
	x1 = a.ShowX();
	y1 = a.ShowY();
	x2 = b.ShowX();
	y2 = b.ShowY();
	x3 = c.ShowX();
	y3 = c.ShowY();
	if (((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) > 0)
		return 1;
	if (((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) == 0)
		return 0;
	if (((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) < 0)
		return -1;
}

void Convex_hull(vector<Point> &a)
{
	if (a.size() < 3)
		return;
	int i, j, i_rez, k;
	bool Parametr;
	double minMod;
	i_rez = 0;
	Point Rez = a[0];
	for (i = 1; i < a.size(); i++)
	{
		if (a[i].ShowY() < Rez.ShowY())
		{
			Rez = a[i];
			i_rez = i;
		}
		else
		{
			if ((a[i].ShowY() == Rez.ShowY()) && (a[i].ShowX() < Rez.ShowX()))
			{
				Rez = a[i];
				i_rez = i;
			}
		}
	}
	a[i_rez] = a[0];
	a[0] = Rez;
	for (i = 1; i < a.size(); i++)
	{
		for (j = i; j < a.size(); j++)
		{
			Parametr = 1;
			for (k = j + 1; k < a.size(); k++)
			{
				if (clockwise(a[0], a[j], a[k]) == -1)
				{
					Parametr = 0;
					continue;
				}
				if (clockwise(a[0], a[j], a[k]) == 0)
				{
					if (a[0].PointsDistanceCube(a[k]) < a[0].PointsDistanceCube(a[j]))
					{
						Parametr = 0;
						continue;
					}
				}
			}
			if (Parametr)
			{
				a[i].swap(a[j]);
				break;
			}
		}
	}

	vector<Point> Rez1;
	Rez1.push_back(a[0]);
	Rez1.push_back(a[1]);
	k = 1;
	for (int i = 2; i < a.size(); i++)
	{
		while ((clockwise(Rez1[k - 1], Rez1[k], a[i])) == -1)
		{
			Rez1.pop_back();
			k--;
		}
		Rez1.push_back(a[i]);
		k++;
	}
	a = Rez1;
};

void DeleteDuplicate(vector<Point> &Rez)
{
	vector<Point> RezV2;
	int carry;
	if (!Rez.empty())
		RezV2.push_back(Rez[0]);


	for (int i = 1; i < Rez.size(); i++)
	{
		carry = 1;
		for (int j = 0; j < RezV2.size(); j++)
		{
			if (Rez[i] == RezV2[j])
				carry = 0;
		}
		if (carry)
			RezV2.push_back(Rez[i]);
	}

	Rez = RezV2;
}

class Shape
{
public:
	virtual double Area() const = 0;
	virtual bool PointOnBorder(const Point &a) const = 0;
	virtual bool PointAccessory(const Point &a) const = 0;
	virtual int FindIntersectionPointWith(const Segment &a, vector<Point> &Rez) const = 0;
};

class Circle : public Shape
{
private:
	Point Centre;
	double Radius;

public:
	Circle() : Centre(0, 0), Radius(0)
	{}

	Circle(const Point &a) : Centre(a), Radius(0)
	{}

	Circle(const Point &a, const double b) : Centre(a), Radius(b)
	{}

	Point ShowPoint() const
	{
		return Centre;
	}

	double ShowRadius() const
	{
		return Radius;
	}

	double Area() const
	{
		return ((M_PI)*(pow(Radius, 2)));
	}

	bool PointOnBorder(const Point &a) const
	{
		double Rez = pow((Centre.ShowX() - a.ShowX()), 2) + pow((Centre.ShowY() - a.ShowY()), 2);
		//cout << Rez << " " << (pow(Radius, 2)) << endl;
		return (Rez == (pow(Radius, 2)));
	}

	bool PointAccessory(const Point &a) const
	{
		double Rez = pow((Centre.ShowX() - a.ShowX()), 2) + pow((Centre.ShowY() - a.ShowY()), 2);
		//cout << Rez << " " << (pow(Radius, 2)) << endl;
		return (Rez <= (pow(Radius, 2)));
	}

	int FindIntersectionPointWith(const Segment &a, vector<Point> &Rez) const
	{
		bool Intersec;
		double A, B, C;
		Point Rez1;
		Line FromA(a);
		FromA.RetCoefficients(A, B, C);
		Vector Help(A, B);
		Line FromCircle(Centre, Help);
		Intersec = FromCircle.FindIntersectionPointWith(FromA, Rez1);
		if (this->PointOnBorder(Rez1))
		{
			if (a.PointAccessory(Rez1))
			{
				Rez.push_back(Rez1);
				return 1;
			}
			else return 0;
		}
		else
		{
			if (this->PointAccessory(Rez1))
			{
				int returned = 0;
				double RightLeft;
				Point Rez1_1, Rez1_2;
				Vector Help2 = a.FindVector();
				Help2.MakeToOneSize();
				RightLeft = sqrt(pow(Radius, 2) - Centre.PointsDistanceCube(Rez1));
				Help2 *= RightLeft;
				Rez1_1 = Help2 + Rez1;
				Help2.Reverse();
				Rez1_2 = Help2 + Rez1;
				if (a.PointAccessory(Rez1_1))
				{
					returned++;
					Rez.push_back(Rez1_1);
				}
				if (a.PointAccessory(Rez1_2))
				{
					returned++;
					Rez.push_back(Rez1_2);
				}
				return returned;;
			}
			else return 0;
		}
	}

	void printCircle()
	{
		cout << "Radius = " << Radius << endl;
		cout << "Centre = ";
		Centre.PrintPoint();
	}

	friend istream& operator>>(istream& is, Circle& dt);
};

class Polygon : public Shape
{
private:
	vector<Point> PointBase;
	vector<Segment> SegmentBase;

public:
	Polygon()
	{}

	Polygon(const int n)
	{
		Point a;
		Segment b;
		for (int i = 0; i < n; i++)
		{
			PointBase.push_back(a);
			SegmentBase.push_back(b);
		}
	}

	Polygon(const vector<Point> &a)
	{
		PointBase = a;
		int size = PointBase.size();
		for (int i = 0; i < size; i++)
		{
			Segment a(PointBase[i], PointBase[(i + 1) % size]);
			SegmentBase.push_back(a);
		}
	}

	vector<Point> createCH() const
	{
		vector<Point> Rez = PointBase;
		Convex_hull(Rez);
		return Rez;
	}

	double Area() const
	{
		double S = 0;
		double X1, X2, Y1, Y2;
		for (int i = 0; i < PointBase.size(); i++)
		{
			X1 = PointBase[i % PointBase.size()].ShowX();
			X2 = PointBase[(i + 1) % PointBase.size()].ShowX();
			Y1 = PointBase[i % PointBase.size()].ShowY();
			Y2 = PointBase[(i + 1) % PointBase.size()].ShowY();
			S += (X2 - X1) * (Y1 + Y2) / 2;
		}
		return abs(S);
	}

	bool PointOnBorder(const Point &a) const
	{
		bool returned = 0;
		for (int i = 0; i < SegmentBase.size(); i++)
		{
			if (SegmentBase[i].PointAccessory(a))
				returned = 1;
		}
		return returned;
	}

	bool PointAccessory(const Point &a) const
	{
		if (this->PointOnBorder(a))
			return 1;
		else
		{
			bool Parametr;
			Vector FromB(1, 0);
			Line b(a, FromB);
			Point Rez_1;
			vector<Point> Rez;
			for (int i = 0; i < SegmentBase.size(); i++)
			{
				Parametr = 0;
				Parametr = b.FindIntersectionPointWith(SegmentBase[i], Rez_1);
				if (Parametr)
					Rez.push_back(Rez_1);
			}
			DeleteDuplicate(Rez);
			if (Rez.size() == 0)
				return 0;
			else
			{
				int N = 0;
				for (int i = 0; i < Rez.size(); i++)
				{
					if (a.ShowX() < Rez[i].ShowX())
						N++;
				}
				return (N % 2);
			}
		}
	}

	int FindIntersectionPointWith(const Segment &a, vector<Point> &Rez) const
	{
		bool Parametr;
		Point Rez1;
		for (int i = 0; i < SegmentBase.size(); i++)
		{
			Parametr = 0;
			Parametr = a.FindIntersectionPointWith(SegmentBase[i], Rez1);
			if (Parametr)
				Rez.push_back(Rez1);
		}
		DeleteDuplicate(Rez);
		return Rez.size();
	}

	void printPolygon() const
	{
		for (int i = 0; i < PointBase.size(); i++)
		{
			PointBase[i].PrintPoint();
			cout << " ";
		}
		cout << endl;
		for (int i = 0; i < SegmentBase.size(); i++)
		{
			SegmentBase[i].PrintSegment();
		}
	}

	friend istream& operator>>(istream& is, Polygon& dt);
};

class Rectangle : public Shape
{
private:
	vector<Point> PointBase;
	vector<Segment> SegmentBase;

public:
	Rectangle()
	{
		Point a;
		Segment b;
		for (int i = 0; i < Count_Rectangle_Vertices; i++)
		{
			PointBase.push_back(a);
			SegmentBase.push_back(b);
		}
	}

	Rectangle(const vector<Point> &a)
	{
		if (a.size() != Count_Rectangle_Vertices)
		{
			cout << "Error. Count of points != 4." << endl;
			exit(1);
		}
		PointBase = a;
		int size = PointBase.size();
		for (int i = 0; i < size; i++)
		{
			Segment a(PointBase[i], PointBase[(i + 1) % size]);
			SegmentBase.push_back(a);
		}
		this->RectangleCheck();
	}

	void RectangleCheck()
	{
		bool Parametr = 0;
		for (int i = 0; i < Count_Rectangle_Vertices; i++)
		{
			Vector One = SegmentBase[i].FindVector();
			Vector Two = SegmentBase[(i + 1) % Count_Rectangle_Vertices].FindVector();
			if (One.DotProduct(Two))
			{
				cout << One.DotProduct(Two) << endl;
				Parametr = 1;
			}
		}
		if (Parametr)
		{
			PointBase.clear();
			SegmentBase.clear();
			cout << "Uncorrect points from this class." << endl;
			exit(1);
		}
	}

	double Area() const
	{
		double a = SegmentBase[0].ModInCube();
		double b = SegmentBase[1].ModInCube();
		return sqrt(a*b);
	}

	bool PointOnBorder(const Point &a) const
	{
		bool returned = 0;
		for (int i = 0; i < Count_Rectangle_Vertices; i++)
		{
			if (SegmentBase[i].PointAccessory(a))
				returned = 1;
		}
		return returned;
	}

	bool PointAccessory(const Point &a) const
	{
		if (this->PointOnBorder(a))
			return 1;
		else
		{
			bool Parametr1, Parametr2;
			Point One, Two;
			Vector FromB = SegmentBase[0].FindVector();
			Line b(a, FromB);
			Parametr1 = b.FindIntersectionPointWith(SegmentBase[1], One);
			Parametr2 = b.FindIntersectionPointWith(SegmentBase[3], Two);
			if ((Parametr1) && (Parametr2))
			{
				Segment Help(One, Two);
				return Help.PointAccessory(a);
			}
			else return 0;
		}
	}

	int FindIntersectionPointWith(const Segment &a, vector<Point> &Rez) const
	{
		bool Parametr;
		Point Rez1;
		for (int i = 0; i < Count_Rectangle_Vertices; i++)
		{
			Parametr = 0;
			Parametr = a.FindIntersectionPointWith(SegmentBase[i], Rez1);
			if (Parametr)
				Rez.push_back(Rez1);
		}
		DeleteDuplicate(Rez);
		return Rez.size();
	}

	void printRectangle()
	{
		for (int i = 0; i < Count_Rectangle_Vertices; i++)
		{
			PointBase[i].PrintPoint();
			cout << " ";
		}
		cout << endl;
		for (int i = 0; i < Count_Rectangle_Vertices; i++)
		{
			SegmentBase[i].PrintSegment();
		}
	}

	friend istream& operator>>(istream& is, Rectangle& dt);
};

class Square : public Rectangle
{
private:
	vector<Point> PointBase;
	vector<Segment> SegmentBase;

public:
	Square()
	{
		Point a;
		Segment b;
		for (int i = 0; i < Count_Rectangle_Vertices; i++)
		{
			PointBase.push_back(a);
			SegmentBase.push_back(b);
		}
	}

	Square(const vector<Point> &a)
	{
		if (a.size() != Count_Rectangle_Vertices)
		{
			cout << "Error. Count of points < 4." << endl;
			exit(1);
		}
		PointBase = a;
		for (int i = 0; i < Count_Rectangle_Vertices; i++)
		{
			Segment a(PointBase[i], PointBase[(i + 1) % Count_Rectangle_Vertices]);
			SegmentBase.push_back(a);
		}
	}

	void SquareCheck()
	{
		if (SegmentBase[0].ModInCube() != SegmentBase[1].ModInCube())
		{
			PointBase.clear();
			SegmentBase.clear();
			cout << "Uncorrect size from this class." << endl;
			exit(1);
		}
	}
};

class Triangle : public Shape
{
private:
	vector<Point> PointBase;
	vector<Segment> SegmentBase;

public:
	Triangle()
	{
		Point a;
		Segment b;
		for (int i = 0; i < Count_Triangle_Vertices; i++)
		{
			PointBase.push_back(a);
			SegmentBase.push_back(b);
		}
	}

	Triangle(const vector<Point> &a)
	{
		if (a.size() != Count_Triangle_Vertices)
		{
			cout << "Error. Count of points < 4." << endl;
			exit(1);
		}
		PointBase = a;
		for (int i = 0; i < Count_Triangle_Vertices; i++)
		{
			Segment a(PointBase[i], PointBase[(i + 1) % Count_Triangle_Vertices]);
			SegmentBase.push_back(a);
		}
	}

	double Area() const
	{
		double x1, x2, x3, y1, y2, y3;
		x1 = PointBase[0].ShowX();
		x2 = PointBase[1].ShowX();
		x3 = PointBase[2].ShowX();
		y1 = PointBase[0].ShowY();
		y2 = PointBase[1].ShowY();
		y3 = PointBase[2].ShowY();
		return abs((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 2.0;
	}

	bool PointOnBorder(const Point &a) const
	{
		bool returned = 0;
		for (int i = 0; i < Count_Triangle_Vertices; i++)
		{
			if (SegmentBase[i].PointAccessory(a))
				returned = 1;
		}
		return returned;
	}

	bool PointAccessory(const Point &a) const
	{
		if (this->PointOnBorder(a))
			return 1;
		else
		{
			bool Parametr1, Parametr2;
			Point One, Two;
			Vector FromB = SegmentBase[0].FindVector();
			Line b(a, FromB);
			Parametr1 = b.FindIntersectionPointWith(SegmentBase[1], One);
			Parametr2 = b.FindIntersectionPointWith(SegmentBase[2], Two);
			if ((Parametr1) && (Parametr2))
			{
				Segment Help(One, Two);
				return Help.PointAccessory(a);
			}
			else return 0;
		}
	}

	int FindIntersectionPointWith(const Segment &a, vector<Point> &Rez) const
	{
		bool Parametr;
		Point Rez1;
		for (int i = 0; i < Count_Triangle_Vertices; i++)
		{
			Parametr = 0;
			Parametr = a.FindIntersectionPointWith(SegmentBase[i], Rez1);
			if (Parametr)
				Rez.push_back(Rez1);
		}
		DeleteDuplicate(Rez);
		return Rez.size();
	}

	void printTriangle()
	{
		for (int i = 0; i < Count_Triangle_Vertices; i++)
		{
			PointBase[i].PrintPoint();
			cout << " ";
		}
		cout << endl;
		for (int i = 0; i < Count_Triangle_Vertices; i++)
		{
			SegmentBase[i].PrintSegment();
		}
	}

	friend istream& operator>>(istream& is, Triangle& dt);
};

istream& operator>>(istream& is, Circle& dt)
{
	is >> dt.Centre >> dt.Radius;
	return is;
}

istream& operator>>(istream& is, Polygon& dt)
{
	int size = dt.PointBase.size();
	for (int i = 0; i < size; i++)
	{
		is >> dt.PointBase[i];
	}
	for (int i = 0; i < size; i++)
	{
		Segment a(dt.PointBase[i], dt.PointBase[(i + 1) % size]);
		dt.SegmentBase[i] = a;
	}
	return is;
}

istream& operator>>(istream& is, Rectangle& dt)
{
	for (int i = 0; i < Count_Rectangle_Vertices; i++)
	{
		is >> dt.PointBase[i];
	}
	for (int i = 0; i < Count_Rectangle_Vertices; i++)
	{
		Segment a(dt.PointBase[i], dt.PointBase[(i + 1) % Count_Rectangle_Vertices]);
		dt.SegmentBase[i] = a;
	}
	dt.RectangleCheck();

	return is;
}

istream& operator>>(istream& is, Triangle& dt)
{
	for (int i = 0; i < Count_Triangle_Vertices; i++)
	{
		is >> dt.PointBase[i];
	}
	for (int i = 0; i < Count_Triangle_Vertices; i++)
	{
		Segment a(dt.PointBase[i], dt.PointBase[(i + 1) % Count_Triangle_Vertices]);
		dt.SegmentBase[i] = a;
	}
	return is;
}
#endif