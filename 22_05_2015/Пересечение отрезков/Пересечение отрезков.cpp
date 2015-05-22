#include <iostream>
#include "PointSegmentVector.h"
#include <vector>
#include <fstream>

using namespace std;

int main()
{
	ifstream infile("Test_Segments_intersection.txt");
	int n, i, j, Parametr;
	Segment a;
	infile >> n;
	vector<Segment> Base;
	vector<Point> RezOne;
	vector<Point> RezOneV2;
	vector<Segment> RezTwo;
	Point Necc;
	Segment Necc1;
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
				Parametr = Base[i].FindIntersectionPointWith(Base[j], Necc);
				if (Parametr)
					RezOne.push_back(Necc);
			}
		}
	}

	int carry;
	if (!RezOne.empty())
		RezOneV2.push_back(RezOne[0]);


	for (i = 1; i < RezOne.size(); i++)
	{
		carry = 1;
		for (j = 0; j < RezOneV2.size(); j++)
		{
			if (RezOne[i] == RezOneV2[j])
				carry = 0;
		}
		if (carry)
			RezOneV2.push_back(RezOne[i]);
	}

	for (i = 0; i < n; i++)
	{
		if (i != n - 1)
		{
			for (j = i + 1; j < n; j++)
			{
				Parametr = Base[i].FindIntersectionSegmentWith(Base[j], Necc1);
				if (Parametr)
					RezTwo.push_back(Necc1);
			}
		}
	}

	for (i = 0; i < RezOne.size(); i++)
	{
		RezOne[i].PrintPoint();
		cout << " ";
	}

	cout << endl;

	for (i = 0; i < RezOneV2.size(); i++)
	{
		RezOneV2[i].PrintPoint();
		cout << " ";
	}

	cout << endl;

	for (i = 0; i < RezTwo.size(); i++)
	{
		RezTwo[i].PrintSegment();
		cout << " ";
	}
		
	return 0;
}