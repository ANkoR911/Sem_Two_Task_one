#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;



class Point
{
private:
	double x;
	double y;

public:
	Point() : x(0), y(0)
	{}

	Point(double a, double b) : x(a), y(b)
	{}

	Point operator = (const Point &a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}

	double ShowX()
	{
		return x;
	}

	double ShowY()
	{
		return y;
	}

	void PrintPoint()
	{
		cout << "(" << x << ", " << y << ")" << endl;
	}

	friend istream& operator>>(istream& is, Point& dt);
};

class Vector
{
private:
	double VecCoordX;
	double VecCoordY;

public:
	Vector() : VecCoordX(0), VecCoordY(0)
	{}

	Vector(double a, double b)
	{
		VecCoordX = a;
		VecCoordY = b;
	}

	Vector(Point a1, Point b1)
	{
		VecCoordX = b1.ShowX() - a1.ShowX();
		VecCoordY = b1.ShowY() - a1.ShowY();
	}

	void Reverse()
	{
		VecCoordX *= -1;
		VecCoordY *= -1;
	}

	double Mod()
	{
		return sqrt(VecCoordX * VecCoordX + VecCoordY * VecCoordY);
	}

	void MakeToOneSize()
	{
		double Size = sqrt(VecCoordX * VecCoordX + VecCoordY * VecCoordY);
		VecCoordX /= Size;
		VecCoordY /= Size;
	}

	void PrintVector()
	{
		cout << VecCoordX << " " << VecCoordY << endl;
	}

	Vector operator = (const Vector &a)
	{
		VecCoordX = a.VecCoordX;
		VecCoordY = a.VecCoordY;
		return *this;
	}

	Vector operator *= (double &a)
	{
		VecCoordX *= a;
		VecCoordY *= a;
		return *this;
	}

	bool operator == (const Vector &a)
	{
		if ((VecCoordX == a.VecCoordX) && (VecCoordY == a.VecCoordY)) return true;
		else return false;
	}

	bool operator != (const Vector &a)
	{
		if (*this == a) return false;
		else return true;
	}

	bool VecOneWay(const Vector foo)
	{
		Vector a = *this;
		Vector b = foo;
		double Help1, Help2;
		Help1 = fabs(a.VecCoordX);
		Help2 = fabs(b.VecCoordX);
		if ((Help1 == 0) && (Help2 == 0))
		{
			if ((a.VecCoordY * b.VecCoordY > 0) || ((a.VecCoordY == 0) && (b.VecCoordY == 0)))
				return true;
		}
		else
		{
			if ((Help1 == 0) || (Help2 == 0))
				return false;
			else
			{
				a *= Help2;
				b *= Help1;
				if (a != b)
				{
					return false;
				}
				else return true;
			}
		}
	}

	bool Parallel(const Vector foo)
	{
		Vector a = *this;
		Vector b = foo;
		double Help1, Help2;
		Help1 = fabs(a.VecCoordX);
		Help2 = fabs(b.VecCoordX);
		if ((Help1 == 0) && (Help2 == 0))
			return true;
		else
		{
			if ((Help1 == 0) || (Help2 == 0))
				return false;
			else
			{
				a *= Help2;
				b *= Help1;
				if (a != b)
				{
					b.Reverse();
					if (a != b)
						return false;
					else return true;
				}
				else return true;
			}
		}
	}
};

class Segment
{
private:
	Point A;
	Point B;

public:
	Segment(Point a, Point b) : A(a), B(b)
	{};

	Segment()
	{}

	Segment operator = (const Segment &a)
	{
		A = a.A;
		B = a.B;
		return *this;
	}

	Vector FindVector()
	{
		Vector Rez(B.ShowX() - A.ShowX(), B.ShowY() - A.ShowY());
		return Rez;
	}

	bool PointAccessory(Point a)
	{
		double x1, x2, x3, y1, y2, y3, S;
		Vector TestOne(a, A);

		Vector TestTwo(a, B);

		x1 = a.ShowX();
		y1 = a.ShowY();
		x2 = A.ShowX();
		y2 = A.ShowY();
		x3 = B.ShowX();
		y3 = B.ShowY();
		S = (x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2;
		if ((S == 0) && ((TestOne.VecOneWay(TestTwo)) != 1)) return true;
		else return false;
	}

	void PrintSegment()
	{
		cout << "First Point - " << "(" << A.ShowX() << ", " << A.ShowY() << ") ";
		cout << "Second Point - " << "(" << B.ShowX() << ", " << B.ShowY() << ")" << endl;
	}

	void FindIntersectionPointWith(Segment Two)
	{
		double A1, B1, C1, A2, B2, C2, X1, Y1;
		Segment One = *this;
		Vector FromOne, FromTwo;
		FromOne = One.FindVector();
		FromTwo = Two.FindVector();
		if (FromOne.Parallel(FromTwo))
		{ }
		else
		{
			A1 = One.A.ShowY() - One.B.ShowY();
			B1 = One.B.ShowX() - One.A.ShowX();
			C1 = One.A.ShowX()*One.B.ShowY() - One.B.ShowX()*One.A.ShowY();
			A2 = Two.A.ShowY() - Two.B.ShowY();
			B2 = Two.B.ShowX() - Two.A.ShowX();
			C2 = Two.A.ShowX()*Two.B.ShowY() - Two.B.ShowX()*Two.A.ShowY();
			X1 = -((C1*B2 - C2*B1) / (A1*B2 - A2*B1));
			Y1 = -((A1*C2 - C1*A2) / (A1*B2 - B1*A2));
			Point Rez(X1, Y1);
			if (One.PointAccessory(Rez) && Two.PointAccessory(Rez))
			{
				cout << "The intersection is Point - ";
				Rez.PrintPoint();
			}
			//else
			//	cout << "The intersection is Empty set." << endl;
		}

	}

	void FindIntersectionSegmentWith(Segment Two)
	{
		double A1, B1, C1, A2, B2, C2, X1, Y1;
		Segment One = *this;
		Vector FromOne, FromTwo;
		FromOne = One.FindVector();
		FromTwo = Two.FindVector();
		if (FromOne.Parallel(FromTwo))
		{
			Point OneA = One.A;
			Point OneB = One.B;
			Point TwoA = Two.A;
			Point TwoB = Two.B;
			if ((Two.PointAccessory(OneA)) && (Two.PointAccessory(OneB)))
			{
				cout << "The intersection is Segment - ";
				One.PrintSegment();
			}
			else
			{
				if ((One.PointAccessory(TwoA)) && (One.PointAccessory(TwoB)))
				{
					cout << "The intersection is Segment - ";
					Two.PrintSegment();
				}
				else
				{
					if ((One.PointAccessory(TwoA)) && (Two.PointAccessory(OneB)))
					{
						cout << "The intersection is Segment - ";
						Segment Rez(TwoA, OneB);
						Rez.PrintSegment();
					}
					else
					{
						if ((Two.PointAccessory(OneA)) && (One.PointAccessory(TwoB)))
						{
							cout << "The intersection is Segment - ";
							Segment Rez(OneA, TwoB);
							Rez.PrintSegment();
						}
						else
						{
							//cout << "The intersection is Empty set." << endl;
						}
					}
				}
			}

		}
	}

	friend istream& operator>>(istream& is, Segment& dt);
};

istream& operator>>(istream& is, Point& dt)
{
	is >> dt.x >> dt.y;
	return is;
}

istream& operator>>(istream& is, Segment& dt)
{
	is >> dt.A >> dt.B;
	return is;
}

int main()
{
	ifstream infile("INPUT.txt");
	int n, i, j;
	Segment a;
	infile >> n;
	vector<Segment> Base;
	for (i = 0; i < n; i++)
		Base.push_back(a);
	for (i = 0; i < n; i++)
		infile >> Base[i];
	for (i = 0; i < n; i++)
	{
		if (i != n - 1)
		{
			for (j = i + 1; j < n; j++)
			{
				Base[i].FindIntersectionPointWith(Base[j]);
			}
		}		
	}

	for (i = 0; i < n; i++)
	{
		if (i != n - 1)
		{
			for (j = i + 1; j < n; j++)
			{
				Base[i].FindIntersectionSegmentWith(Base[j]);
			}
		}

	}
	return 0;
}