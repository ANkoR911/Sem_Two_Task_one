#include <iostream>
#include "PointSegmentVector.h"
#include <vector>

using namespace std;

int main()
{
	int n, i, j, Parametr;
	Segment a;
	cin >> n;
	vector<Segment> Base;
	vector<Point> RezOne;
	vector<Segment> RezTwo;
	Point Necc;
	Segment Necc1;
	for (i = 0; i < n; i++)
		Base.push_back(a);
	for (i = 0; i < n; i++)
		cin >> Base[i];
	for (i = 0; i < n; i++)
	{
		if (i != n - 1)
		{
			for (j = i + 1; j < n; j++)
			{
				Parametr = Base[i].FindIntersectionPointWith(Base[j], &Necc);
				if (Parametr)
					RezOne.push_back(Necc);
			}
		}
	}

	for (i = 0; i < n; i++)
	{
		if (i != n - 1)
		{
			for (j = i + 1; j < n; j++)
			{
				Parametr = Base[i].FindIntersectionSegmentWith(Base[j], &Necc1);
				if (Parametr)
					RezTwo.push_back(Necc1);
			}
		}
	}

	for (i = 0; i < RezOne.size() - 1; i++)
	{
		RezOne[i].PrintPoint();
		cout << " ";
	}

	cout << endl;

	for (i = 0; i < RezTwo.size() - 1; i++)
	{
		RezTwo[i].PrintSegment();
		cout << " ";
	}
		
	return 0;
}