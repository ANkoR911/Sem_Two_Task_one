#include <iostream>
#include <vector>
#include "All_Geometry.h"
#include <fstream>

using namespace std;

int main()
{
	ifstream infile("Test_geometry.txt");
	int Number_of_tests, i;
	int Operation_Number;//1 - (Cicrle_1), 2 - (Circle_2)
	infile >> Number_of_tests;
	for (i = 1; i <= Number_of_tests; i++)
	{
		infile >> Operation_Number;
		switch (Operation_Number)
		{
		case 1:
		{
			Circle Test;
			infile >> Test;
			Point a, b, c;			
			bool Rez_a_1, Rez_b_1, Rez_c_1, Rez_a_2, Rez_b_2, Rez_c_2;
			int Rez = 0;
			infile >> a >> b >> c;
			infile >> Rez_a_1 >> Rez_b_1 >> Rez_c_1;
			infile >> Rez_a_2 >> Rez_b_2 >> Rez_c_2;
			if (Test.PointOnBorder(a) == Rez_a_1) Rez++;
			if (Test.PointOnBorder(b) == Rez_b_1) Rez++;
			if (Test.PointOnBorder(c) == Rez_c_1) Rez++;
			if (Test.PointAccessory(a) == Rez_a_2) Rez++;
			if (Test.PointAccessory(b) == Rez_b_2) Rez++;
			if (Test.PointAccessory(c) == Rez_c_2) Rez++;

			if (Rez != 6)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 2:
		{
			int j, n, n_1;
			Circle Test;
			Segment SegTest;
			infile >> Test;
			infile >> SegTest;
			infile >> n_1;
			vector<Point> Rez;
			vector<Point> Rez_1(n_1);
			for (j = 0; j < n_1; j++)
				infile >> Rez_1[j];
			n = Test.FindIntersectionPointWith(SegTest, Rez);
			if ((n != n_1) || (Rez != Rez_1))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 3:
		{
			int n, j;
			double S, S_Test;
			infile >> n;
			Polygon Test(n);
			infile >> Test;
			infile >> S_Test;
			Point a, b, c;
			bool Rez_a_1, Rez_b_1, Rez_c_1, Rez_a_2, Rez_b_2, Rez_c_2;
			int Rez = 0;
			infile >> a >> b >> c;
			infile >> Rez_a_1 >> Rez_b_1 >> Rez_c_1;
			infile >> Rez_a_2 >> Rez_b_2 >> Rez_c_2;
			if (Test.PointOnBorder(a) == Rez_a_1) Rez++;
			if (Test.PointOnBorder(b) == Rez_b_1) Rez++;
			if (Test.PointOnBorder(c) == Rez_c_1) Rez++;
			if (Test.PointAccessory(a) == Rez_a_2) Rez++;
			if (Test.PointAccessory(b) == Rez_b_2) Rez++;
			if (Test.PointAccessory(c) == Rez_c_2) Rez++;
			S = Test.Area();

			if ((Rez != 6) || (S != S_Test))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 4:
		{
			int n, j, n_1;
			infile >> n;
			Polygon Test(n);
			infile >> Test;
			Segment SegTest;
			infile >> SegTest;
			infile >> n_1;
			vector<Point> Rez;
			vector<Point> Rez_1(n_1);
			for (j = 0; j < n_1; j++)
				infile >> Rez_1[j];
			n = Test.FindIntersectionPointWith(SegTest, Rez);
			if ((n != n_1) || (Rez != Rez_1))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 5:
		{
			int n, j;
			double S, S_Test;
			Rectangle Test;
			infile >> Test;
			infile >> S_Test;
			Point a, b, c;
			bool Rez_a_1, Rez_b_1, Rez_c_1, Rez_a_2, Rez_b_2, Rez_c_2;
			int Rez = 0;
			infile >> a >> b >> c;
			infile >> Rez_a_1 >> Rez_b_1 >> Rez_c_1;
			infile >> Rez_a_2 >> Rez_b_2 >> Rez_c_2;
			if (Test.PointOnBorder(a) == Rez_a_1) Rez++;
			if (Test.PointOnBorder(b) == Rez_b_1) Rez++;
			if (Test.PointOnBorder(c) == Rez_c_1) Rez++;
			if (Test.PointAccessory(a) == Rez_a_2) Rez++;
			if (Test.PointAccessory(b) == Rez_b_2) Rez++;
			if (Test.PointAccessory(c) == Rez_c_2) Rez++;
			S = Test.Area();

			if ((Rez != 6) || (S != S_Test))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 6:
		{
			int n, j, n_1;
			Rectangle Test;
			infile >> Test;
			Segment SegTest;
			infile >> SegTest;
			infile >> n_1;
			vector<Point> Rez;
			vector<Point> Rez_1(n_1);
			for (j = 0; j < n_1; j++)
				infile >> Rez_1[j];
			n = Test.FindIntersectionPointWith(SegTest, Rez);
			if ((n != n_1) || (Rez != Rez_1))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 7:
		{
			int n, j;
			double S, S_Test;
			Square Test;
			infile >> Test;
			infile >> S_Test;
			Point a, b, c;
			bool Rez_a_1, Rez_b_1, Rez_c_1, Rez_a_2, Rez_b_2, Rez_c_2;
			int Rez = 0;
			infile >> a >> b >> c;
			infile >> Rez_a_1 >> Rez_b_1 >> Rez_c_1;
			infile >> Rez_a_2 >> Rez_b_2 >> Rez_c_2;
			if (Test.PointOnBorder(a) == Rez_a_1) Rez++;
			if (Test.PointOnBorder(b) == Rez_b_1) Rez++;
			if (Test.PointOnBorder(c) == Rez_c_1) Rez++;
			if (Test.PointAccessory(a) == Rez_a_2) Rez++;
			if (Test.PointAccessory(b) == Rez_b_2) Rez++;
			if (Test.PointAccessory(c) == Rez_c_2) Rez++;
			S = Test.Area();

			if ((Rez != 6) || (S != S_Test))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 8:
		{
			int n, j, n_1;
			Square Test;
			infile >> Test;
			Segment SegTest;
			infile >> SegTest;
			infile >> n_1;
			vector<Point> Rez;
			vector<Point> Rez_1(n_1);
			for (j = 0; j < n_1; j++)
				infile >> Rez_1[j];
			n = Test.FindIntersectionPointWith(SegTest, Rez);
			if ((n != n_1) || (Rez != Rez_1))
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 9:
		{
			int n, j, n_1;
			infile >> n;
			Polygon Test(n);
			infile >> Test;
			infile >> n_1;
			vector<Point> Rez;
			vector<Point> Rez_1(n_1);
			for (j = 0; j < n_1; j++)
				infile >> Rez_1[j];
			Rez = Test.createCH();
			cout << endl;
			if ((Rez.size() != n_1) || (Rez != Rez_1))
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