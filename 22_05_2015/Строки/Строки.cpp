#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class NewString
{
private:
	vector <char> Str;

public:
	NewString(const char* a, const int S)
	{
		for (int i = 0; i < S; i++)
			Str.push_back(a[i]);
	}

	NewString(const string a)
	{
		for (int i = 0; i < a.size(); i++)
			Str.push_back(a[i]);
	}

	NewString()
	{}

	NewString(const int S)
	{
		for (int i = 0; i < S; i++)
			Str.push_back('0');
	}

	NewString operator = (const NewString &a)
	{
		Str = a.Str;
		return *this;
	}

	NewString operator = (const string &a)
	{
		for (int i = 0; i < Str.size(); i++)
			Str.pop_back();
		for (int i = 0; i < a.size(); i++)
			Str.push_back(a[i]);
		return *this;
	}

	bool operator == (const NewString &a) const
	{
		return (Str == a.Str);
	}

	bool operator < (const NewString &a) const
	{
		int k = 1;
		for (int i = 0; i < min(Str.size(), a.Str.size()); i++)
		{
			if ((Str[i] > a.Str[i]) || (Str == a.Str))
			{
				k = 0;
				break;
			}
			if (Str[i] < a.Str[i])
			{
				k = 2;
				break;
			}
		}
		if ((k == 1) && (Str.size() > a.Str.size())) k = 0;
		return (k > 0);
	}

	NewString operator + (const NewString &a) const
	{
		NewString Rez;
		Rez = *this;
		for (int i = 0; i < a.Str.size(); i++)
		{
			Rez.Str.push_back(a.Str[i]);
		}
		return Rez;
	}

	void push_str_in_middle(const NewString &a)
	{
		int siz = Str.size();
		for (int i = 0; i < a.Str.size(); i++)
			Str.push_back(0);
		for (int i = siz; i >(siz / 2); i--)
			Str[i + a.Str.size() - 1] = Str[i - 1];
		for (int i = 0; i < a.Str.size(); i++)
			Str[i + (siz / 2)] = a.Str[i];
	}

	void push_middle(const char a)
	{
		int siz = Str.size();
		Str.push_back(0);
		for (int i = siz; i >(siz / 2); i--)
			Str[i] = Str[i - 1];
		Str[siz / 2] = a;
	}

	void pop_middle()
	{
		int siz = Str.size() - 1;
		for (int i = (siz / 2); i < siz; i++)
			Str[i] = Str[i + 1];
		Str.pop_back();
	}

	void push_in_back(const char a)
	{
		Str.push_back(a);
	}

	void pop_in_back()
	{
		Str.pop_back();
	}

	friend ostream& operator << (ostream& os, const NewString &a);
	friend istream& operator >> (istream& is, NewString &a);
};

ostream& operator << (ostream& os, const NewString &a)
{
	for (int i = 0; i < a.Str.size(); i++)
		os << a.Str[i];
	return os;
}

istream& operator >> (istream& is, NewString &a)
{
	for (int i = 0; i < a.Str.size(); i++)
		is >> a.Str[i];
	return is;
}



int main()
{
	ifstream infile("Test_string.txt");
	int Number_of_Tests, i, j, Num_of_string, n1, n2, n3;
	int Operation_Number; //1 - (==), 2 - (<), 3 - (+), 4 - (push_str_in_middle), 5 - (push_middle), 6 - (pop_middle), 7 - (push_in_back), 8 - (pop_in_back)
	infile >> Number_of_Tests;
	for (i = 1; i <= Number_of_Tests; i++)
	{	
		infile >> Operation_Number;
		switch (Operation_Number)
		{
		case 1:
		{
			infile >> n1;
			NewString TestOne(n1);
			infile >> TestOne;
			infile >> n2;
			NewString TestTwo(n2);
			infile >> TestTwo;
			bool Rez;
			infile >> Rez;
			if ((TestOne == TestTwo) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;				
		}

		case 2:
		{
			infile >> n1;
			NewString TestOne(n1);
			infile >> TestOne;
			infile >> n2;
			NewString TestTwo(n2);
			infile >> TestTwo;
			bool Rez;
			infile >> Rez;
			if ((TestOne < TestTwo) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 3:
		{
			infile >> n1;
			NewString TestOne(n1);
			infile >> TestOne;
			infile >> n2;
			NewString TestTwo(n2);
			infile >> TestTwo;
			NewString TestThree;
			TestThree = TestOne + TestTwo;
			NewString Rez(n1+n2);
			infile >> Rez;
			if (!(TestThree == Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 4:
		{
			infile >> n1;
			NewString TestOne(n1);
			infile >> TestOne;
			infile >> n2;
			NewString TestTwo(n2);
			infile >> TestTwo;
			TestOne.push_str_in_middle(TestTwo);
			NewString Rez(n1 + n2);
			infile >> Rez;
			if (!(TestOne == Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 5:
		{
			infile >> n1;
			NewString TestOne(n1);
			infile >> TestOne;
			char XZ_Wat;
			infile >> XZ_Wat;
			NewString Rez(n1 + 1);
			infile >> Rez;
			TestOne.push_middle(XZ_Wat);
			if (!(TestOne == Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 6:
		{
			infile >> n1;
			NewString TestOne(n1);
			infile >> TestOne;			
			NewString Rez(n1 - 1);
			infile >> Rez;
			TestOne.pop_middle();
			if (!(TestOne == Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 7:
		{
			infile >> n1;
			NewString TestOne(n1);
			infile >> TestOne;
			char XZ_Wat;
			infile >> XZ_Wat;
			NewString Rez(n1 + 1);
			infile >> Rez;
			TestOne.push_in_back(XZ_Wat);
			if (!(TestOne == Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 8:
		{
			infile >> n1;
			NewString TestOne(n1);
			infile >> TestOne;
			NewString Rez(n1 - 1);
			infile >> Rez;
			TestOne.pop_in_back();
			if (!(TestOne == Rez))
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