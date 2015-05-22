#include <iostream>
#include <string>
#include "Descrip.h"
#include <vector>
#include <fstream>

class Drug_and_price
{
private:
	Drug Product;
	double Price;

public:
	Drug_and_price() : Product(), Price(-1)
	{}

	Drug_and_price(const Drug &a) : Product(a), Price(-1)
	{}

	Drug_and_price(const Drug &a, const double _price) : Product(a)
	{
		if (_price >= 0)
			Price = _price;
	}

	void changePrice(const double a)
	{
		if (a >= 0)
			Price = a;
	}

	Drug ShowProduct() const
	{
		return Product;
	}

	double ShowPrice() const
	{
		return Price;
	}

	bool operator == (const Drug &a) const
	{
		return (Product == a);
	}

	bool operator == (const Drug_and_price &a) const
	{
		return ((Product == a.Product) && (Price == a.Price));
	}

	bool operator != (const Drug_and_price &a) const
	{
		return (!((*this) == a));
	}

	bool operator != (const Drug &a) const
	{
		return (Product != a);
	}

	friend istream& operator >> (istream& is, Drug_and_price &a);

	friend ostream& operator << (ostream& os, const Drug_and_price &a);
};

istream& operator >> (istream& is, Drug_and_price &a)
{
	is >> a.Product >> a.Price;
	return is;
}

ostream& operator << (ostream& os, const Drug_and_price &a)
{
	os << a.Product <<" " << a.Price;
	return os;
}

class Drugs_Shop
{
private:
	vector<Drug_and_price> Base;

public:
	Drugs_Shop()
	{}

	int ShowSize() const
	{
		return Base.size();
	}

	Drug_and_price retBack() const
	{
		return Base[Base.size() - 1];
	}

	bool operator == (const Drugs_Shop &a) const
	{
		bool Rez = 1;
		if ((a.ShowSize()) != (this->ShowSize()))
			return 0;
		else
		{
			for (int i = 0; i < a.ShowSize(); i++)
			{
				if (Base[i] != a.Base[i])
				{
					//cout << Base[i] <<" "<< a.Base[i] << endl;
					Rez = 0;
				}					
			}
			return Rez;
		}
	}

	bool operator != (const Drugs_Shop &a) const
	{
		return (!((*this) == a));
	}

	void addDrug(const Drug_and_price &a)
	{
		Base.push_back(a);
	}

	void addDrug(const Drug &a)
	{
		Base.push_back(a);
	}

	bool ChangePrice(const Drug &a, const double NewPrice)
	{
		int fNum = -1;
		for (int i = 0; i < Base.size(); i++)
		{
			if (Base[i] == a)
			{
				fNum = i;
				break;
			}
		}
		if ((fNum == -1) || (NewPrice < 0))
			return 0;
			//cout << "Not found this drug." << endl;
		else
		{
			Base[fNum].changePrice(NewPrice);
			return 1;
		}
	}

	bool findPrice(const Drug &a, double &Rez) const
	{
		int fNum = -1;
		for (int i = 0; i < Base.size(); i++)
		{
			if (Base[i] == a)
			{
				fNum = i;
				break;
			}
		}
					
		if (fNum == -1)
			return 0;
			//cout << "Not found this drug." << endl;
		else
		{
			Rez = Base[fNum].ShowPrice();
			if (Rez == -1)
				return 0;
				//cout << "Not found the price of this drug." << endl;
			if (Rez >= 0)
			{
				return 1;
				//cout << "The price of this drug is " << Base[fNum].ShowPrice() << "." << endl;
			}
				
		}
	}

	bool findFromChar(const string a, Drugs_Shop &Rez) const
	{
		string Help;
		int IfFound = 0;
		for (int i = 0; i < Base.size(); i++)
		{
			Help = Base[i].ShowProduct().ShowName().substr(0, a.size());
			if (Help == a)
			{
				Rez.addDrug(Base[i]);
				IfFound = 1;
			}				
		}
		return IfFound;
	}

	bool findFromMaker(const string a, Drugs_Shop &Rez) const
	{
		string Help;
		int IfFound = 0;
		for (int i = 0; i < Base.size(); i++)
		{
			Help = Base[i].ShowProduct().ShowMaker();
			if (Help == a)
			{
				Rez.addDrug(Base[i]);
				IfFound = 1;
			}
		}
		return IfFound;
	}

	bool findFromActiveSub(const string a, Drugs_Shop &Rez) const
	{
		string Help;
		int IfFound = 0;
		for (int i = 0; i < Base.size(); i++)
		{
			Help = Base[i].ShowProduct().ShowActive_sub();
			if (Help == a)
			{
				Rez.addDrug(Base[i]);
				IfFound = 1;
			}
		}
		return IfFound;
	}

	bool findFromForm(const string a, Drugs_Shop &Rez) const
	{
		string Help;
		int IfFound = 0;
		for (int i = 0; i < Base.size(); i++)
		{
			Help = Base[i].ShowProduct().ShowForm();
			if (Help == a)
			{
				Rez.addDrug(Base[i]);
				IfFound = 1;
			}
		}
		return IfFound;
	}

	bool findFromMakerAndActiveSub(const string a, const string b, Drugs_Shop &Rez) const
	{
		int Par1 = (this->findFromMaker(a, Rez));
		if (Par1 == 0) return 0;
		else
		{
			Drugs_Shop Rez2;
			int Par2 = Rez.findFromActiveSub(b, Rez2);
			if (Par2 == 0)
			{
				Rez.Base.clear();
				return 0;
			}
			else
			{
				Rez = Rez2;
				return 1;
			}
		}
	}

	bool findFrom(const string a, const string Parametr, Drugs_Shop &Rez) const
	{
		string Help;
		Help = "_NULL_";
		int IfFound = 0;
		for (int i = 0; i < Base.size(); i++)
		{
			if (Parametr == "Maker")
				Help = Base[i].ShowProduct().ShowActive_sub();
			if (Parametr == "Active_Sub")
				Help = Base[i].ShowProduct().ShowActive_sub();
			if (Parametr == "First_char")
				Help = Base[i].ShowProduct().ShowName().substr(0, a.size());
			if (Parametr == "Form")
				Help = Base[i].ShowProduct().ShowForm();
			if (Help == a)
			{
				Rez.addDrug(Base[i]);
				IfFound = 1;
			}
		}
		return IfFound;
	}

	bool FindMinPrice(Drug_and_price &Rez) const
	{
		if ((this->ShowSize()) == 0)
		{
			return 0;
		}
		int Parametr = 0;
		int MinSum = -1;
		for (int i = 0; i < (this->ShowSize()); i++)
		{
			if ((MinSum > Base[i].ShowPrice() || (MinSum == -1)) && (Base[i].ShowPrice() >= 0))
			{
				MinSum = Base[i].ShowPrice();
				Parametr = i;
			}
		}
		if (MinSum == -1) return 0;
		else
		{
			Rez = Base[Parametr];
			return 0;
		}
	}

	double SumPrice() const
	{
		double Sum = 0;
		for (int i = 0; i < (this->ShowSize()); i++)
		{
			Sum += ((Base[i].ShowPrice() == -1) ? 0 : Base[i].ShowPrice());
		}
		return Sum;
	}

	void PrintAllBase() const
	{
		for (int i = 0; i < (this->ShowSize()); i++)
			cout << Base[i] << endl;
	}

	void deleteDrug(const int i)
	{
		int end = this->ShowSize() - 1;
		if (i-1 <= end)
		{
			Base[i-1] = Base[end];
			Base.pop_back();
		}		
	}

	void duplicateDrug(const int i)
	{
		if (i-1 < (this->ShowSize()))
			Base.push_back(Base[i-1]);
	}

	void deleteDuplicate()
	{
		vector<Drug_and_price> BaseV2;
		int carry;
		if (!Base.empty())
			BaseV2.push_back(Base[0]);


		for (int i = 1; i < Base.size(); i++)
		{
			carry = 1;
			for (int j = 0; j < BaseV2.size(); j++)
			{
				if (Base[i] == BaseV2[j])
					carry = 0;
			}
			if (carry)
				BaseV2.push_back(Base[i]);
		}

		Base.clear();
		Base.swap(BaseV2);
	}

};

int main()
{
	ifstream infile("Anteka_base.txt");
	ifstream infile2("Anteka_test.txt");
	int Base_size, Number_of_tests, i, Parametr, ParametrTest, j;
	int Operation_Number;//1 - (change price), 2 - (add Drug), 3 - (find price), 4 - (find from char)
	//5 - (find from Maker), 6 - (find from Active_sub), 7 - (find from Maker and Active_sub), 8 - (AllSum), 9 - (minSum)
	//10 - (delete and duplicate), 11 - (deleteCopy)
	Drug_and_price Help;
	Drugs_Shop TestBase;
	infile >> Base_size;
	for (int i = 0; i < Base_size; i++)
	{
		infile >> Help;
		//cout << Help << endl;
		TestBase.addDrug(Help);
	}

	infile2 >> Number_of_tests;
	for (i = 1; i <= Number_of_tests; i++)
	{
		infile2 >> Operation_Number;
		switch (Operation_Number)
		{
		case 1:
		{
			Drug TestOne;
			double NewPrice;
			infile2 >> TestOne;
			infile2 >> ParametrTest >> NewPrice;
			Parametr = TestBase.ChangePrice(TestOne, NewPrice);
			if (ParametrTest != Parametr)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 2:
		{
			Drug TestOne;
			Drug_and_price TestTwo;
			infile2 >> TestOne;
			TestBase.addDrug(TestOne);
			TestTwo = TestBase.retBack();
			if (TestTwo != TestOne)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 3:
		{
			Drug TestOne;
			double TestPrice, Price;
			infile2 >> TestOne;
			infile2 >> TestPrice >> ParametrTest;
			Price = 0;
			Parametr = TestBase.findPrice(TestOne, Price);
			if ((TestPrice != Price) || (ParametrTest != Parametr))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 4:
		{
			Drugs_Shop TestOne, Rez;
			int RezSize;
			string a;
			infile2 >> a >> ParametrTest >> RezSize;
			Drug_and_price Help;
			for (j = 0; j < RezSize; j++)
			{
				infile2 >> Help;
				Rez.addDrug(Help);
			}
			Parametr = TestBase.findFromChar(a, TestOne);
			if ((Parametr != ParametrTest) || (TestOne != Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 5:
		{
			Drugs_Shop TestOne, Rez;
			int RezSize;
			string a;
			infile2 >> a >> ParametrTest >> RezSize;
			Drug_and_price Help;
			for (j = 0; j < RezSize; j++)
			{
				infile2 >> Help;
				Rez.addDrug(Help);
			}
			Parametr = TestBase.findFromMaker(a, TestOne);
			if ((Parametr != ParametrTest) || (TestOne != Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 6:
		{
			Drugs_Shop TestOne, Rez;
			int RezSize;
			string a;
			infile2 >> a >> ParametrTest >> RezSize;
			Drug_and_price Help;
			for (j = 0; j < RezSize; j++)
			{
				infile2 >> Help;
				Rez.addDrug(Help);
			}
			Parametr = TestBase.findFromActiveSub(a, TestOne);
			if ((Parametr != ParametrTest) || (TestOne != Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 7:
		{
			Drugs_Shop TestOne, Rez;
			int RezSize;
			string a, b;
			infile2 >> a >> b >> ParametrTest >> RezSize;
			Drug_and_price Help;
			for (j = 0; j < RezSize; j++)
			{
				infile2 >> Help;
				Rez.addDrug(Help);
			}
			Parametr = TestBase.findFromMakerAndActiveSub(a, b, TestOne);
			if ((Parametr != ParametrTest) || (TestOne != Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 8:
		{
			Drugs_Shop TestOne, Rez;
			int RezSize;
			double TestSum, Sum;
			string a;
			infile2 >> a >> ParametrTest >> TestSum;
			Parametr = TestBase.findFromChar(a, TestOne);
			Sum = TestOne.SumPrice();
			if ((Parametr != ParametrTest) || (TestSum != Sum))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 9:
		{
			Drug_and_price TestOne, Rez;
			infile2 >> Rez;
			Parametr = TestBase.FindMinPrice(TestOne);
			if (TestOne != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 10:
		{
			Drugs_Shop Rez;
			int RezSize, i1, j1;
			infile2 >> i1 >> j1 >> RezSize;
			Drug_and_price Help;
			for (j = 0; j < RezSize; j++)
			{
				infile2 >> Help;
				Rez.addDrug(Help);
			}
			TestBase.deleteDrug(i1);
			TestBase.duplicateDrug(j1);
			if (TestBase != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 11:
		{
			Drugs_Shop Rez;
			int RezSize;
			infile2 >> RezSize;
			Drug_and_price Help;
			for (j = 0; j < RezSize; j++)
			{
				infile2 >> Help;
				Rez.addDrug(Help);
			}
			TestBase.deleteDuplicate();
			if (TestBase != Rez)
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