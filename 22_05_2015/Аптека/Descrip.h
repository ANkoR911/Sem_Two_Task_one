#ifndef _DESCRIPTION_OF_THE_DRUG_
#define _DESCRIPTION_OF_THE_DRUG_
#include <iostream>
#include <string>

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

	Drug(const string _name, const string _maker, const string _active_sub, const double _dose, const string _form) : Name(_name), Maker(_maker), Active_sub(_active_sub), Dosage(_dose), Form(_form)
	{}

	string ShowName() const
	{
		return Name;
	}

	void getName(const string newName)
	{
		Name = newName;
	}

	string ShowMaker() const
	{
		return Maker;
	}

	void getMaker(const string newMaker)
	{
		Maker = newMaker;
	}

	string ShowActive_sub() const
	{
		return Active_sub;
	}

	void getActive_sub(const string newActive_sub)
	{
		Active_sub = newActive_sub;
	}

	double ShowDosage() const
	{
		return Dosage;
	}

	void getDosage(const double newDosage)
	{
		Dosage = newDosage;
	}

	string ShowForm() const
	{
		return Form;
	}

	void getForm(const string newForm)
	{
		Form = newForm;
	}

	bool operator == (const Drug &a) const
	{
		return ((Name == a.Name) && (Maker == a.Maker) && (Active_sub == a.Active_sub) && (Dosage == a.Dosage) && (Form == a.Form));
	}

	bool operator != (const Drug &a) const
	{
		return (!((*this) == a));
	}

	friend istream& operator >> (istream& is,  Drug &a);

	friend ostream& operator << (ostream& os, const Drug &a);
};

istream& operator >> (istream& is, Drug &a)
{
	is >> a.Name >> a.Maker >> a.Active_sub >> a.Dosage >> a.Form;
	return is;
}

ostream& operator << (ostream& os, const Drug &a)
{
	os <<  a.Name << " " << a.Maker << " " << a.Active_sub << " " <<  a.Dosage << " " << a.Form;
	return os;
}
#endif