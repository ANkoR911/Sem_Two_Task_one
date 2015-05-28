#include <iostream>
#include <vector>
#include "PointSegmentVector.h"
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
const int Count_Rectangle_Vertices = 4;
const int Count_Triangle_Vertices = 3;


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

class Circle: public Shape
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

class Polygon: public Shape
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

	double Area() const
	{
		double S = 0;
		double X1, X2, Y1, Y2;
		for (int i = 0; i < PointBase.size(); i++)
		{
			X1 = PointBase[i % PointBase.size()].ShowX();
			X2 = PointBase[(i+1) % PointBase.size()].ShowX();
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

	void printPolygon()
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

class Rectangle: public Shape
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

class Square: public Rectangle
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

class Triangle: public Shape
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

int main()
{
	ifstream infile("Test_geometry.txt");
	int Number_of_tests, i;
	int Operation_Number;//1 - (Cicrle_1), 2 - (Circle_2)
	infile >> Number_of_tests;
	for (i = 1; i <= Number_of_tests; i++)
	{
		infile >> Operation_Number;
		switch (Operation_Number)
		{
		case 1:
		{
			Circle Test;
			infile >> Test;
			Point a, b, c;			
			bool Rez_a_1, Rez_b_1, Rez_c_1, Rez_a_2, Rez_b_2, Rez_c_2;
			int Rez = 0;
			infile >> a >> b >> c;
			infile >> Rez_a_1 >> Rez_b_1 >> Rez_c_1;
			infile >> Rez_a_2 >> Rez_b_2 >> Rez_c_2;
			if (Test.PointOnBorder(a) == Rez_a_1) Rez++;
			if (Test.PointOnBorder(b) == Rez_b_1) Rez++;
			if (Test.PointOnBorder(c) == Rez_c_1) Rez++;
			if (Test.PointAccessory(a) == Rez_a_2) Rez++;
			if (Test.PointAccessory(b) == Rez_b_2) Rez++;
			if (Test.PointAccessory(c) == Rez_c_2) Rez++;

			if (Rez != 6)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 2:
		{
			int j, n, n_1;
			Circle Test;
			Segment SegTest;
			infile >> Test;
			infile >> SegTest;
			infile >> n_1;
			vector<Point> Rez;
			vector<Point> Rez_1(n_1);
			for (j = 0; j < n_1; j++)
				infile >> Rez_1[j];
			n = Test.FindIntersectionPointWith(SegTest, Rez);
			if ((n != n_1) || (Rez != Rez_1))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 3:
		{
			int n, j;
			double S, S_Test;
			infile >> n;
			Polygon Test(n);
			infile >> Test;
			infile >> S_Test;
			Point a, b, c;
			bool Rez_a_1, Rez_b_1, Rez_c_1, Rez_a_2, Rez_b_2, Rez_c_2;
			int Rez = 0;
			infile >> a >> b >> c;
			infile >> Rez_a_1 >> Rez_b_1 >> Rez_c_1;
			infile >> Rez_a_2 >> Rez_b_2 >> Rez_c_2;
			if (Test.PointOnBorder(a) == Rez_a_1) Rez++;
			if (Test.PointOnBorder(b) == Rez_b_1) Rez++;
			if (Test.PointOnBorder(c) == Rez_c_1) Rez++;
			if (Test.PointAccessory(a) == Rez_a_2) Rez++;
			if (Test.PointAccessory(b) == Rez_b_2) Rez++;
			if (Test.PointAccessory(c) == Rez_c_2) Rez++;
			S = Test.Area();

			if ((Rez != 6) || (S != S_Test))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 4:
		{
			int n, j, n_1;
			infile >> n;
			Polygon Test(n);
			infile >> Test;
			Segment SegTest;
			infile >> SegTest;
			infile >> n_1;
			vector<Point> Rez;
			vector<Point> Rez_1(n_1);
			for (j = 0; j < n_1; j++)
				infile >> Rez_1[j];
			n = Test.FindIntersectionPointWith(SegTest, Rez);
			if ((n != n_1) || (Rez != Rez_1))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 5:
		{
			int n, j;
			double S, S_Test;
			Rectangle Test;
			infile >> Test;
			infile >> S_Test;
			Point a, b, c;
			bool Rez_a_1, Rez_b_1, Rez_c_1, Rez_a_2, Rez_b_2, Rez_c_2;
			int Rez = 0;
			infile >> a >> b >> c;
			infile >> Rez_a_1 >> Rez_b_1 >> Rez_c_1;
			infile >> Rez_a_2 >> Rez_b_2 >> Rez_c_2;
			if (Test.PointOnBorder(a) == Rez_a_1) Rez++;
			if (Test.PointOnBorder(b) == Rez_b_1) Rez++;
			if (Test.PointOnBorder(c) == Rez_c_1) Rez++;
			if (Test.PointAccessory(a) == Rez_a_2) Rez++;
			if (Test.PointAccessory(b) == Rez_b_2) Rez++;
			if (Test.PointAccessory(c) == Rez_c_2) Rez++;
			S = Test.Area();

			if ((Rez != 6) || (S != S_Test))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 6:
		{
			int n, j, n_1;
			Rectangle Test;
			infile >> Test;
			Segment SegTest;
			infile >> SegTest;
			infile >> n_1;
			vector<Point> Rez;
			vector<Point> Rez_1(n_1);
			for (j = 0; j < n_1; j++)
				infile >> Rez_1[j];
			n = Test.FindIntersectionPointWith(SegTest, Rez);
			if ((n != n_1) || (Rez != Rez_1))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 7:
		{
			int n, j;
			double S, S_Test;
			Square Test;
			infile >> Test;
			infile >> S_Test;
			Point a, b, c;
			bool Rez_a_1, Rez_b_1, Rez_c_1, Rez_a_2, Rez_b_2, Rez_c_2;
			int Rez = 0;
			infile >> a >> b >> c;
			infile >> Rez_a_1 >> Rez_b_1 >> Rez_c_1;
			infile >> Rez_a_2 >> Rez_b_2 >> Rez_c_2;
			if (Test.PointOnBorder(a) == Rez_a_1) Rez++;
			if (Test.PointOnBorder(b) == Rez_b_1) Rez++;
			if (Test.PointOnBorder(c) == Rez_c_1) Rez++;
			if (Test.PointAccessory(a) == Rez_a_2) Rez++;
			if (Test.PointAccessory(b) == Rez_b_2) Rez++;
			if (Test.PointAccessory(c) == Rez_c_2) Rez++;
			S = Test.Area();

			if ((Rez != 6) || (S != S_Test))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 8:
		{
			int n, j, n_1;
			Square Test;
			infile >> Test;
			Segment SegTest;
			infile >> SegTest;
			infile >> n_1;
			vector<Point> Rez;
			vector<Point> Rez_1(n_1);
			for (j = 0; j < n_1; j++)
				infile >> Rez_1[j];
			n = Test.FindIntersectionPointWith(SegTest, Rez);
			if ((n != n_1) || (Rez != Rez_1))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		default:
			cout << "Error!!! Uncorrect Operation_Number!!! (Test " << i << ")" << endl;
			break;
		}

	}
	return 0;
}