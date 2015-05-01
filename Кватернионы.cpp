#include <iostream>
#include <math.h>

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

	Quaternion(double a, double b, double c, double d) : Im(a), Re_i(b), Re_j(c), Re_k(d)
	{}



	/*void operator >> (Quaternion a)
	{
		cin >> a.Im >> a.Re_i >> a.Re_j >> a.Re_k;
	}*/

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

	Quaternion operator + (const Quaternion &a)
	{
		Quaternion Rez;
		Rez.Im = Im + a.Im;
		Rez.Re_i = Re_i + a.Re_i;
		Rez.Re_j = Re_j + a.Re_j;
		Rez.Re_k = Re_k + a.Re_k;
		return Rez;
	}

	Quaternion operator - (const Quaternion &a)
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

	Quaternion operator * (const Quaternion &a)
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

	Quaternion operator / (double n)
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

	Quaternion Conjugation()
	{
		Re_i = -Re_i;
		Re_j = -Re_j;
		Re_k = -Re_k;
		return *this;
	}

	double Norm()
	{
		double a = sqrt((Im*Im) + (Re_i*Re_i) + (Re_j*Re_j) + (Re_k*Re_k));
		return a;
	}

	Quaternion Reciprocal()
	{
		double n;
		Quaternion A = *this;
		n = A.Norm();
		A.Conjugation();
		A /= n*n;
		return A;
	}

	Quaternion operator / (const Quaternion &a)
	{
		Quaternion Rez, Help;
		Help = a;
		Help = Help.Reciprocal();
		Rez = *this * Help;
		return Rez;
	}

	Quaternion operator /= (const Quaternion &a)
	{
		Quaternion Rez, Help;
		Help = a;
		Help = Help.Reciprocal();
		Rez = *this * Help;
		*this = Rez;
		return *this;
	}

	bool operator == (const Quaternion &a)
	{
		if ((Im == a.Im) && (Re_i == a.Re_i) && (Re_j == a.Re_j) && (Re_k == a.Re_k)) return 1;
		else return 0;
	}

	double DotProduct(const Quaternion &a)
	{
		double Rez = (Im*a.Im) + (Re_i*a.Re_i) + (Re_j*a.Re_j) + (Re_k*a.Re_k);
	}

	Quaternion CrossProduct(Quaternion &a)
	{
		Quaternion Help = *this;
		Quaternion Rez = ((Help * a) - (a * Help)) / 2;
		return Rez;
	}
};

int main()
{
	double a, b, c, d;
	cin >> a >> b >> c >> d;
	Quaternion A;
	Quaternion B(a, b, c, d);
	Quaternion C;
	
	C = B;
	A = B / C;
	A.printQ();
	B.printQ();
	C.printQ();
	//cout << a << endl;
	return 0;
}