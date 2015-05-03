#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class NewString
{
private:
	vector <char> Str;

public:
	NewString(char* a, int S)
	{
		for (int i = 0; i < S; i++)
			Str.push_back(a[i]);
	}

	NewString(string a)
	{
		for (int i = 0; i < a.size(); i++)
			Str.push_back(a[i]);
	}

	NewString()
	{}

	NewString(int S)
	{
		for (int i = 0; i < S; i++)
			Str.push_back('0');
	}

	NewString operator = (NewString &a)
	{
		Str = a.Str;
		return *this;
	}

	bool operator == (NewString &a)
	{
		if (Str == a.Str) return true;
		else return false;
	}

	/*NewString operator + (const NewString &a)
	{
		NewString Rez;
		Rez = *this;
		Rez.Str.insert(Rez.Str.end(), a.Str.front(), a.Str.back());
		return Rez;
	}*/

	NewString operator + (const NewString &a)
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
		for (int i = siz; i > (siz / 2); i--)
			Str[i + a.Str.size()-1] = Str[i-1];
		for (int i = 0; i < a.Str.size(); i++)
			Str[i + (siz / 2)] = a.Str[i];
	}

	void push_middle(const char a)
	{
		int siz = Str.size();
		Str.push_back(0);
		for (int i = siz; i > (siz / 2); i--)
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

	friend ostream& operator << (ostream& os, NewString &a);
	friend istream& operator >> (istream& is, NewString &a);
};

ostream& operator << (ostream& os, NewString &a)
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
	int n1, n2, i;
	cin >> n1 >> n2;
	
	
	/*char* A = new char[n];
	for (i = 0; i < n; i++)
		cin >> A[i];
	NewString Test(A, n);*/


	/*NewString Test(n);
	cout << Test << endl;
	cin >> Test;
	cout << Test << endl;*/


	/*string a = "Hellp";
	NewString Test(a);
	cout << Test << endl;*/

	
	/*NewString TestOne(n);
	cin >> TestOne;
	NewString TestTwo;
	TestTwo = TestOne;
	cout << TestTwo << endl;*/


	NewString TestOne(n1);
	cin >> TestOne;

	//NewString TestTwo(n2);
	//cin >> TestTwo;
	//NewString Rez;
	//TestOne.push_str_in_middle(TestTwo);

	char a = 'g';
	TestOne.pop_middle();
	cout << TestOne << endl;


	return 0;
}