#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

class Quaternion
{
private:
	double Im;
	double Re_i;
	double Re_j;
	double Re_k;

public:
	Quaternion() : Im(0), Re_i(0), Re_j(0), Re_k(0)
	{}

	Quaternion(const double a, const double b, const double c, const double d) : Im(a), Re_i(b), Re_j(c), Re_k(d)
	{}


	void printQ()
	{
		cout << Im << " " << Re_i << " " << Re_j << " " << Re_k << endl;
	}

	Quaternion operator = (const Quaternion &a)
	{
		Im = a.Im;
		Re_i = a.Re_i;
		Re_j = a.Re_j;
		Re_k = a.Re_k;
		return *this;
	}

	Quaternion operator + (const Quaternion &a) const
	{
		Quaternion Rez;
		Rez.Im = Im + a.Im;
		Rez.Re_i = Re_i + a.Re_i;
		Rez.Re_j = Re_j + a.Re_j;
		Rez.Re_k = Re_k + a.Re_k;
		return Rez;
	}

	Quaternion operator - (const Quaternion &a) const
	{
		Quaternion Rez;
		Rez.Im = Im - a.Im;
		Rez.Re_i = Re_i - a.Re_i;
		Rez.Re_j = Re_j - a.Re_j;
		Rez.Re_k = Re_k - a.Re_k;
		return Rez;
	}

	Quaternion operator += (const Quaternion &a)
	{
		Im += a.Im;
		Re_i += a.Re_i;
		Re_j += a.Re_j;
		Re_k += a.Re_k;
		return *this;
	}

	Quaternion operator -= (const Quaternion &a)
	{
		Im -= a.Im;
		Re_i -= a.Re_i;
		Re_j -= a.Re_j;
		Re_k -= a.Re_k;
		return *this;
	}

	Quaternion operator * (const Quaternion &a) const
	{
		Quaternion Rez;
		Rez.Im = (Im * a.Im) - (Re_i * a.Re_i) - (Re_j * a.Re_j) - (Re_k * a.Re_k);
		Rez.Re_i = (Im * a.Re_i) + (Re_i * a.Im) + (Re_j * a.Re_k) - (Re_k * a.Re_j);
		Rez.Re_j = (Im * a.Re_j) - (Re_i * a.Re_k) + (Re_j * a.Im) + (Re_k * a.Re_i);
		Rez.Re_k = (Im * a.Re_k) + (Re_i * a.Re_j) - (Re_j * a.Re_i) + (Re_k * a.Im);
		return Rez;
	}

	Quaternion operator *= (const Quaternion &a)
	{
		Quaternion Rez;
		Rez.Im = (Im * a.Im) - (Re_i * a.Re_i) - (Re_j * a.Re_j) - (Re_k * a.Re_k);
		Rez.Re_i = (Im * a.Re_i) + (Re_i * a.Im) + (Re_j * a.Re_k) - (Re_k * a.Re_j);
		Rez.Re_j = (Im * a.Re_j) - (Re_i * a.Re_k) + (Re_j * a.Im) + (Re_k * a.Re_i);
		Rez.Re_k = (Im * a.Re_k) + (Re_i * a.Re_j) - (Re_j * a.Re_i) + (Re_k * a.Im);
		*this = Rez;
		return *this;
	}

	Quaternion operator / (double n) const
	{
		Quaternion Rez;
		Rez.Im = Im / n;
		Rez.Re_i = Re_i / n;
		Rez.Re_j = Re_j / n;
		Rez.Re_k = Re_k / n;
		return Rez;
	}

	Quaternion operator /= (double n)
	{
		Im /= n;
		Re_i /= n;
		Re_j /= n;
		Re_k /= n;
		return *this;
	}

	Quaternion Conjugation() //сопряженный кватернион
	{
		Re_i = -Re_i;
		Re_j = -Re_j;
		Re_k = -Re_k;
		return *this;
	}

	/*double Norm() //модуль кватерниона
	{
		double a = sqrt((Im*Im) + (Re_i*Re_i) + (Re_j*Re_j) + (Re_k*Re_k));
		return a;
	}*/

	/*Quaternion Reciprocal() // кватернион А в степени -1
	{
		double n;
		Quaternion A = *this;
		//n = A.Norm();
		n = (Im*Im) + (Re_i*Re_i) + (Re_j*Re_j) + (Re_k*Re_k);
		A.Conjugation();
		A /= n;
		return A;
	}*/

	Quaternion operator / (const Quaternion &a) const
	{
		Quaternion Rez, Help;
		Help = a;
		Help = Help.Conjugation();
		Rez = *this * Help;
		Rez /= (a.Im*a.Im) + (a.Re_i*a.Re_i) + (a.Re_j*a.Re_j) + (a.Re_k*a.Re_k);
		return Rez;
	}

	Quaternion operator /= (const Quaternion &a)
	{
		Quaternion Rez, Help;
		Help = a;
		Help = Help.Conjugation();
		Rez = *this * Help;
		Rez /= (a.Im*a.Im) + (a.Re_i*a.Re_i) + (a.Re_j*a.Re_j) + (a.Re_k*a.Re_k);
		*this = Rez;
		return *this;
	}

	bool operator == (const Quaternion &a) const
	{
		return ((Im == a.Im) && (Re_i == a.Re_i) && (Re_j == a.Re_j) && (Re_k == a.Re_k));
	}

	bool operator != (const Quaternion &a) const
	{
		return (!(*this == a));
	}

	double DotProduct(const Quaternion &a) const
	{
		double Rez = (Im*a.Im) + (Re_i*a.Re_i) + (Re_j*a.Re_j) + (Re_k*a.Re_k);
		return Rez;
	}

	Quaternion CrossProduct(Quaternion &a) const
	{
		Quaternion Help = *this;
		Quaternion Rez = ((Help * a) - (a * Help)) / 2;
		return Rez;
	}

	friend ostream& operator << (ostream& os, Quaternion &a);

	friend istream& operator >> (istream& is, Quaternion &a);
};

ostream& operator << (ostream& os, Quaternion &a)
{
	os << a.Im << a.Re_i << a.Re_j << a.Re_k;
	return os;
}

istream& operator >> (istream& is, Quaternion &a)
{
	is >> a.Im >> a.Re_i >> a.Re_j >> a.Re_k;
	return is;
}

int main()
{
	ifstream infile("Test_quaternion.txt");
	int Number_of_Tests, i;
	int Operation_Number; // 1 - (+), 2 - (*), 3 - (/), 4 - (Conjugation), 5 - (DotProduct), 6 - (CrossProduct)
	infile >> Number_of_Tests;
	for (i = 1; i <= Number_of_Tests; i++)
	{
		infile >> Operation_Number;
		switch (Operation_Number)
		{
		case 1:
		{
			Quaternion TestOne, TestTwo, Rez;
			infile >> TestOne >> TestTwo >> Rez;
			if ((TestOne = TestOne + TestTwo) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}			

		case 2:
		{
			Quaternion TestOne, TestTwo, Rez;
			infile >> TestOne >> TestTwo >> Rez;
			if ((TestOne = TestOne * TestTwo) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}			

		case 3:
		{
			Quaternion TestOne, TestTwo, Rez;
			infile >> TestOne >> TestTwo >> Rez;
			if ((TestOne = TestOne / TestTwo) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}			

		case 4:
		{
			Quaternion TestOne, Rez;
			infile >> TestOne >> Rez;
			if ((TestOne = TestOne.Conjugation()) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}			

		case 5:
		{
			Quaternion TestOne, TestTwo;
			double Rez, Test;
			infile >> TestOne >> TestTwo >> Rez;
			if ((Test = TestOne.DotProduct(TestTwo)) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}			

		case 6:
		{
			Quaternion TestOne, TestTwo, Rez;
			infile >> TestOne >> TestTwo >> Rez;
			if ((TestOne = TestOne.CrossProduct(TestTwo)) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		default:
		{
			cout << "Error!!! Uncorrect Operation_Number!!! (Test " << i << ")" << endl;
			break;
		}			
		}
	}
	return 0;
}