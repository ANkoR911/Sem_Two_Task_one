#include <iostream>
#include <string.h>

using namespace std;

class Drug
{
private:
	string Name;
	string Maker;
	string Active_sub;
	double Dosage;
	string Form;

public:
	Drug() : Name("Unknown"), Maker("Unknown"), Active_sub("Unknown"), Dosage(0), Form("Unknown")
	{}

	Drug(string _name, string _maker, string _active_sub, double _dose, string _form) : Name(_name), Maker(_maker), Active_sub(_active_sub), Dosage(_dose), Form(_form)
	{}

	string printName()
	{
		return Name;
	}

	void getName(string newName)
	{
		Name = newName;
	}

	string printMaker()
	{
		return Maker;
	}

	void getMaker(string newMaker)
	{
		Maker = newMaker;
	}

	string printActive_sub()
	{
		return Active_sub;
	}

	void getActive_sub(string newActive_sub)
	{
		Active_sub = newActive_sub;
	}

	double printDosage()
	{
		return Dosage;
	}

	void getDosage(double newDosage)
	{
		Dosage = newDosage;
	}

	string printForm()
	{
		return Form;
	}

	void getForm(string newForm)
	{
		Form = newForm;
	}

	void operator << (const string &a)
	{
		for (int i = 0; i < a.size(); i++)
			cout << a[i];
	}

	void printInfo()
	{
		cout << printName() << " " << printMaker() << " " << printActive_sub() << " " << printDosage() << " " << printForm() << endl;
	}
};

int main()
{
	Drug A;
	Drug B("Iod", "Japan", "Iod", 10, "Maz");
	A.printInfo();
	B.printInfo();
	return 0;
}