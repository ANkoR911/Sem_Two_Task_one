#include <iostream>
#include <math.h>
#include <fstream>
#include "PointSegmentVector.h"

using namespace std;



int main()
{
	ifstream infile("Test_point_segment_vector.txt");
	int Number_of_tests, i;
	int Operation_Number; //1 - (VecOneWay), 2 - (Parallel), 3 - (PointAccessory), 4 - (FindIntersectionPointWith), 5 - (FindIntersectionSegmentWith)
	infile >> Number_of_tests;
	for (i = 1; i <= Number_of_tests; i++)
	{
		infile >> Operation_Number;
		switch (Operation_Number)
		{
		case 1:
		{
			Vector TestOne, TestTwo;
			infile >> TestOne >> TestTwo;
			bool Rez;
			infile >> Rez;
			if ((TestOne.VecOneWay(TestTwo)) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 2:
		{
			Vector TestOne, TestTwo;
			infile >> TestOne >> TestTwo;
			bool Rez;
			infile >> Rez;
			if ((TestOne.Parallel(TestTwo)) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 3:
		{
			Segment TestOne;
			infile >> TestOne;
			Point TestTwo;
			infile >> TestTwo;
			bool Rez;
			infile >> Rez;
			if ((TestOne.PointAccessory(TestTwo)) != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 4:
		{
			Segment TestOne, TestTwo;
			infile >> TestOne >> TestTwo;
			Point Rez, Ret;
			infile >> Rez;
			int Check;
			Check = TestOne.FindIntersectionPointWith(TestTwo, Ret);
			if ((Check != 1) || (Ret != Rez))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 5:
		{
			Segment TestOne, TestTwo;
			infile >> TestOne >> TestTwo;
			Segment Rez, Ret;
			infile >> Rez;
			int Check;
			Check = TestOne.FindIntersectionSegmentWith(TestTwo, Ret);
			if ((Check != 1) || (Ret != Rez))
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