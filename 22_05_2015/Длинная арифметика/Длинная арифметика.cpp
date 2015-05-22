#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;


const int base = 1000000000;

class LongNum
{
private:
	vector<int> ilum;
	int sign;
public:
	LongNum() : sign(0)
	{}

	LongNum(const string s)
	{
		for (int i = (int)s.length(); i>0; i -= 9)
			if (i < 9)
				ilum.push_back(atoi(s.substr(0, i).c_str()));
			else
				ilum.push_back(atoi(s.substr(i - 9, 9).c_str()));

		while (ilum.size() > 1 && ilum.back() == 0)
			ilum.pop_back();
	}

	void changeSign()
	{
		sign = 1;
	}

	void printLN() const
	{
		printf("%d", ilum.empty() ? 0 : ilum.back());
		for (int i = (int)ilum.size() - 2; i >= 0; --i)
			printf("%09d", ilum[i]);
		printf("\n");
	}

	void swap(LongNum &b)
	{
		ilum.swap(b.ilum);
		int c = sign;
		sign = b.sign;
		b.sign = c;
	}

	bool operator > (const LongNum &b) const
	{
		int carry = 1;
		if (ilum.size() > b.ilum.size())
			return true;
		if (ilum.size() < b.ilum.size())
			return false;
		if (ilum.size() == b.ilum.size())
		{
			for (int i = ilum.size() - 1; i >= 0; i--)
			{
				//cout << ilum[i] << " " << b.ilum[i] << endl;
				if (ilum[i] > b.ilum[i])
					break;
				if (ilum[i] < b.ilum[i])
				{
					carry = 0;
					break;
				}
					
			}				
			if (ilum == b.ilum) carry = 0;
			return carry;
		}
	}

	LongNum operator + (const LongNum &b) const
	{
		LongNum a = *this;
		int carry = 0;
		for (size_t i = 0; i<max(a.ilum.size(), b.ilum.size()) || carry; ++i)
		{
			if (i == a.ilum.size())
				a.ilum.push_back(0);
			a.ilum[i] += carry + (i < b.ilum.size() ? b.ilum[i] : 0);
			carry = a.ilum[i] >= base;
			if (carry)  a.ilum[i] -= base;
		}
		return a;
	}

	LongNum operator - (const LongNum &c) const
	{
		LongNum a = *this;
		LongNum b = c;
		if (b > a)
		{
			//a.ilum.swap(b.ilum);
			a.swap(b);
			a.changeSign();
		}
		int carry = 0;
		for (size_t i = 0; i<b.ilum.size() || carry; ++i)
		{
			a.ilum[i] -= carry + (i < b.ilum.size() ? b.ilum[i] : 0);
			carry = a.ilum[i] < 0;
			if (carry)  a.ilum[i] += base;
		}
		while (a.ilum.size() > 1 && a.ilum.back() == 0)
			a.ilum.pop_back();
		return a;
	}

	LongNum operator * (const LongNum &b) const
	{
		LongNum a = *this;
		LongNum c;
		for (int i = 0; i < (a.ilum.size() + b.ilum.size()); i++)
			c.ilum.push_back(0);
		for (size_t i = 0; i<a.ilum.size(); ++i)
			for (int j = 0, carry = 0; j<(int)b.ilum.size() || carry; ++j) 
			{
				long long cur = c.ilum[i + j] + a.ilum[i] * 1ll * (j < (int)b.ilum.size() ? b.ilum[j] : 0) + carry;
				c.ilum[i + j] = int(cur % base);
				carry = int(cur / base);
			}
		while (c.ilum.size() > 1 && c.ilum.back() == 0)
			c.ilum.pop_back();
		return c;
	}

	LongNum operator / (const int &b)  const
	{
		LongNum a = *this;
		int carry = 0;
		for (int i = (int)a.ilum.size() - 1; i >= 0; --i) {
			long long cur = a.ilum[i] + carry * 1ll * base;
			a.ilum[i] = int(cur / b);
			carry = int(cur % b);
		}
		while (a.ilum.size() > 1 && a.ilum.back() == 0)
			a.ilum.pop_back();
		return a;
	}

	int operator % (const int &b) const
	{
		LongNum a = *this;
		int carry = 0;
		for (int i = (int)a.ilum.size() - 1; i >= 0; --i) {
			long long cur = a.ilum[i] + carry * 1ll * base;
			a.ilum[i] = int(cur / b);
			carry = int(cur % b);
		}
		while (a.ilum.size() > 1 && a.ilum.back() == 0)
			a.ilum.pop_back();
		return carry;
	}

	friend ostream& operator<<(ostream& os, const LongNum& dt);
};

ostream& operator<<(ostream& os, const LongNum& dt)
{
	if ((!(dt.ilum.empty())) && (dt.sign == 1))
		os << '-';
	os << (dt.ilum.empty() ? 0 : dt.ilum.back());
	for (int i = (int)dt.ilum.size() - 2; i >= 0; --i)
	{
		os.width(9);
		os.fill('0');
		os << dt.ilum[i];
	}
	return os;
}

int main()
{
	ifstream infile("INPUT.txt");
	ofstream outfile("OUTPUT.txt");

	/*string a, b;
	infile >> a;
	infile >> b;
	LongNum TestOne(a);
	LongNum TestTwo(b);
	TestOne = TestOne + TestTwo;
	outfile << TestOne;*/

	string a, b;
	infile >> a;
	infile >> b;
	LongNum TestOne(a);
	LongNum TestTwo(b);
	TestOne = TestOne - TestTwo;
	outfile << TestOne;


	/*string a, b;
	infile >> a;
	infile >> b;
	LongNum TestOne(a);
	LongNum TestTwo(b);
	TestOne = TestOne * TestTwo;
	outfile << TestOne;*/

	/*string a;
	int b;
	infile >> a;
	LongNum TestOne(a);
	infile >> b;
	TestOne = TestOne / b;
	outfile << TestOne;*/

	/*string a;
	int b, Rez;
	infile >> a;
	LongNum TestOne(a);
	infile >> b;
	Rez = TestOne % b;
	outfile << Rez;*/

	//getline(infile, a);
	//getline(infile, b);
	
	//outfile << 'word' << ' ';
	return 0;
}