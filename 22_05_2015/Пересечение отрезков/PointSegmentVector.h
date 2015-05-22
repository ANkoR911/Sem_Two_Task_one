#include <iostream>
using namespace std;
#ifndef _POINT_S_VEC_
#define __POINT_S_VEC_
class Point
{
private:
	double x;
	double y;

public:
	Point() : x(0), y(0)
	{}

	Point(const double a, const double b) : x(a), y(b)
	{}

	Point operator = (const Point &a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}

	/*Point operator + (const Vector &a) const
	{
		Point Rez;
		double x, y;
		x = a.RetVecCoordX();
		y = a.RetVecCoordY();
		Rez.x = (*this).x + x;
		Rez.y = (*this).y + y;
		return Rez;
	}*/

	double ShowX() const
	{
		return x;
	}

	double ShowY() const
	{
		return y;
	}

	void PrintPoint() const
	{
		cout << "(" << (x ? x  : 0) << ", " << (y ? y : 0) << ")";
	}

	bool operator == (const Point &a) const
	{
		return ((x == a.x) && (y == a.y));
	}

	bool operator != (const Point &a) const
	{
		return (!(*this == a));
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

	Vector(const double a, const double b)
	{
		VecCoordX = a;
		VecCoordY = b;
	}

	Vector(const Point &a1, const Point &b1)
	{
		VecCoordX = b1.ShowX() - a1.ShowX();
		VecCoordY = b1.ShowY() - a1.ShowY();
	}

	double RetVecCoordX() const
	{
		return VecCoordX;
	}

	double RetVecCoordY() const
	{
		return VecCoordY;
	}

	void Reverse()
	{
		VecCoordX *= -1;
		VecCoordY *= -1;
	}

	double Mod() const
	{
		return sqrt(VecCoordX * VecCoordX + VecCoordY * VecCoordY);
	}

	void MakeToOneSize()
	{
		double Size = sqrt(VecCoordX * VecCoordX + VecCoordY * VecCoordY);
		VecCoordX /= Size;
		VecCoordY /= Size;
	}

	void PrintVector() const
	{
		cout << "(" << VecCoordX << ", " << VecCoordY << ")";
	}

	Vector operator = (const Vector &a)
	{
		VecCoordX = a.VecCoordX;
		VecCoordY = a.VecCoordY;
		return *this;
	}

	Vector operator *= (const double &a)
	{
		VecCoordX *= a;
		VecCoordY *= a;
		return *this;
	}

	bool operator == (const Vector &a) const
	{
		return ((VecCoordX == a.VecCoordX) && (VecCoordY == a.VecCoordY));
	};

	bool operator != (const Vector &a) const
	{
		if (*this == a) return false;
		else return true;
	};

	bool VecOneWay(const Vector &foo) const
	{
		Vector a = *this;
		Vector b = foo;
		Vector Zero;
		if ((a == Zero) || (b == Zero))
			return true;
		else
		{
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
					return (a == b);
				}
			}
		}
	};

	bool Parallel(const Vector &foo) const
	{
		Vector a = *this;
		Vector b = foo;
		if (a.VecOneWay(b)) return true;
		else
		{
			b.Reverse();
			return (a.VecOneWay(b));
		}
	}

	friend istream& operator>>(istream& is, Vector& dt);
};

class Segment
{
private:
	Point A;
	Point B;

public:
	Segment(const Point &a, const Point &b) : A(a), B(b)
	{};

	Segment()
	{}

	Segment operator = (const Segment &a)
	{
		A = a.A;
		B = a.B;
		return *this;
	};

	bool operator == (const Segment &a) const
	{
		return ((A == a.A) && (B == a.B));
	}

	bool operator != (const Segment &a) const
	{
		return (!(*this == a));
	}

	Vector FindVector() const
	{
		Vector Rez(B.ShowX() - A.ShowX(), B.ShowY() - A.ShowY());
		return Rez;
	};

	bool PointAccessory(const Point &a) const
	{
		if ((a == A) || (a == B))
			return true;
		else
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
	};

	void PrintSegment() const
	{
			cout << "First Point - " << "(" << A.ShowX() << ", " << A.ShowY() << ") ";
			cout << "Second Point - " << "(" << B.ShowX() << ", " << B.ShowY() << ")";
	};

	int FindIntersectionPointWith(const Segment &Two, Point &Rez) const
	{
		int returned;
		double A1, B1, C1, A2, B2, C2, X1, Y1;
		Segment One = *this;
		Vector FromOne, FromTwo;
		FromOne = One.FindVector();
		FromTwo = Two.FindVector();
		if (FromOne.Parallel(FromTwo))
		{
			returned = 0;
		}
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
			Point Rez1(X1, Y1);
			if (One.PointAccessory(Rez1) && Two.PointAccessory(Rez1))
			{
				/*cout << "The intersection is Point - ";
				Rez1.PrintPoint();*/
				returned = 1;
				(Rez) = Rez1;
			}
			else
				//cout << "Segments have no points of intersection" << endl;
				returned = 0;
		}
		return returned;
	}

	int FindIntersectionSegmentWith(const Segment &Two, Segment &Rez) const
	{
		int returned;
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
				/*cout << "The intersection is Segment - ";
				One.PrintSegment();*/
				(Rez) = One;
				returned = 1;
			}
			else
			{
				if ((One.PointAccessory(TwoA)) && (One.PointAccessory(TwoB)))
				{
					/*cout << "The intersection is Segment - ";
					Two.PrintSegment();*/
					(Rez) = Two;
					returned = 1;
				}
				else
				{
					if ((One.PointAccessory(TwoA)) && (Two.PointAccessory(OneB)))
					{
						/*cout << "The intersection is Segment - ";
						Segment Rez(TwoA, OneB);
						Rez.PrintSegment();*/
						Segment Rez1(TwoA, OneB);
						(Rez) = Rez1;
						returned = 1;
					}
					else
					{
						if ((Two.PointAccessory(OneA)) && (One.PointAccessory(TwoB)))
						{
							/*cout << "The intersection is Segment - ";
							Segment Rez(OneA, TwoB);
							Rez.PrintSegment();*/
							Segment Rez1(OneA, TwoB);
							(Rez) = Rez1;
							returned = 1;
						}
						else
						{
							returned = 0;
							//cout << "The intersection is Empty set." << endl;
						}
					}
				}
			}
		}
		else
			returned = 0;
		return returned;
	}

	friend istream& operator>>(istream& is, Segment& dt);
};

istream& operator>>(istream& is, Point& dt)
{
	is >> dt.x >> dt.y;
	return is;
}

istream& operator>>(istream& is, Vector& dt)
{
	is >> dt.VecCoordX >> dt.VecCoordY;
	return is;
}

istream& operator>>(istream& is, Segment& dt)
{
	is >> dt.A >> dt.B;
	return is;
}

#endif



