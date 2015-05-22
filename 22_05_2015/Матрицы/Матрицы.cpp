#include <iostream>
#include <stdio.h>
#include <fstream>
#include <algorithm>

using namespace std;

template< class T >

class Matrix
{
private:
	T** M;
	int m, n;


public:	

	Matrix(const int M1, const int N1)
	{
		if ((m <= 0) && (n <= 0))
		{
			m = M1;
			n = N1;
			M = new T*[m];
			for (int i = 0; i < m; i++)
			{
				M[i] = new T[n];
				for (int j = 0; j < n; j++)
				{
					M[i][j] = 0;
				}
			}
		}
		else
		{
			cout << "Error! Incorrect imput data in Matrix Constructor." << endl;
			exit(1);
		}
			
		
	}

	Matrix(const Matrix &a)
	{
		m = a.m;
		n = a.n;
		M = new T*[m];
		for (int i = 0; i < m; i++)
		{
			M[i] = new T[n];
			for (int j = 0; j < n; j++)
			{
				M[i][j] = a.M[i][j];
				//cout << M[i][j] << " ";
			}
			//cout << endl;
		}
	}

	~Matrix()
	{
		for (int i = 0; i < m; i++)
			delete M[i];
		delete M;
	}

public:
	void printMatrix() const
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
				cout << M[i][j] << " ";
			//printf("%d ", M[i][j]);
			//printf("\n");
			cout << endl;
		}
	} 

	void scanfMatrix()
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
				cin >> M[i][j];
		}
	}

	/*void fscanfMatrix()
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
				infile >> M[i][j];
		}
	}*/

	Matrix operator = (const Matrix &a)
	{
		if ((m == a.m) && (n == a.n))
		{
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
					M[i][j] = a.M[i][j];

			}
			return *this;
		}
		else
		{
			cout << "ERROR!  Uncorrect size for operator(=)." << endl;
			exit(1);
		}
	}

	Matrix operator + (const Matrix &a) const
	{
		if ((m == a.m) && (n == a.n))
		{
			Matrix Rez(m, n);
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
					Rez[i][j] = M[i][j] + a.M[i][j];

			}
			return Rez;
		}
		else
		{
			cout << "ERROR!  Uncorrect size for operator(+)." << endl;
			exit(1);
		}
	}

	Matrix operator - (const Matrix &a) const
	{
		if ((m == a.m) && (n == a.n))
		{
			Matrix Rez(m, n);
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
					Rez[i][j] = M[i][j] - a.M[i][j];

			}
			return Rez;
		}
		else
		{
			cout << "ERROR!  Uncorrect size for operator(-)." << endl;
			exit(1);
		}
	}

	Matrix operator * (const Matrix &b) const
	{
		if (b.m == n)
		{
			Matrix Rez(m, b.n);
			double Sum;
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < b.n; j++)
				{
					Sum = 0;
					for (int k = 0; k < n; k++)
						Sum += M[i][k] * b.M[k][j];
					Rez.M[i][j] = Sum;
				}
			}
			return Rez;
		}
		else
		{
			cout << "ERROR! Uncorrect size for operator(*)." << endl;
			exit(1);
		}
	}

	bool operator == (const Matrix &a) const
	{
		bool k = 1;
		if ((m == a.m) && (n == a.n))
		{
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (M[i][j] != a.M[i][j])
						k = 0;
				}
			}
		}
		else k = 0;
		return k;
	}

	bool operator != (const Matrix &a) const
	{
		return (!((*this) == a));
	}

	T* operator [] (const int a)
	{
		return M[a];
	}

	void operator ()(const int a, const int b, const int Rez)
	{
		if ((a - 1 < m) && (b - 1 < n) && (a>0) && (b>0))
			M[a - 1][b - 1] = Rez;
		else cout << "ERROR! The element with this indices does not exist." << endl;
	}

	T traceMatrix() const
	{
		if (m == n)
		{
			T Sum = 0;
			for (int i = 0; i < m; i++)
				Sum += M[i][i];
			return Sum;
		}
		else
		{
			cout << "ERROR! Uncorrect size in traceMatrix()." << endl;
			exit(1);
		}
	}

	Matrix buildSubMatrix(const int a, const int b) const
	{
		if ((m == 1) || (n == 1) || (m <= a) || (n <= b))
		{
			cout << "Uncorrect using  buildSubMatrix() for this size." << endl;
			exit(1);
		}			
		else
		{
			Matrix Rez(m - 1, n - 1);
			int m1, n1;

			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (i < a)
						m1 = i;
					if (i > a)
						m1 = i - 1;
					if (j < b)
						n1 = j;
					if (j > b)
						n1 = j - 1;
					if ((i != a) && (j != b))
						Rez.M[m1][n1] = M[i][j];
				}
			}
			return Rez;
		}
		
	}

	T detMatrix() const
	{
		if (m == n)
		{
			if (m == 1)
				return M[0][0];
			else
			{
				T Rez = 0;
				int sign = -1;
				for (int i = 0; i < m; i++)
				{
					sign *= -1;
					Matrix Help(m - 1, m - 1);
					Help = (this -> buildSubMatrix(0, i));
					Rez += sign*M[0][i]*(Help.detMatrix());
				}
				return Rez;
			}
		}
		else
		{
			cout << "ERROR! Uncorrect size in detMatrix()." << endl;
			exit(1);
		}
	}

	/*T detMatrix() const
	{
		if (m == n)
		{
			Matrix a(m, n);
			int l;
			T Crack;
			T Rez = 1;
			int N = m;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
					a.M[i][j] = M[i][j];
			}

			for (int i = 0; i < N; i++)
			{
				l = i;
				while ((a.M[l][l] == 0) && (l < N))
				{
					if (l == N - 1)
					{
						Rez = 0;
						break;
					}
					l++;
				}



				if ((l != i) && (l < N))
				{
					for (int j = 0; j < N; j++)
						swap(a.M[i][j], a.M[l][j]);
					if (((l - i) % 2) == 1)
						Rez = Rez*(-1);
				}

				if ((l != i) && (l >= N))
				{
					Rez = 0;
					break;
				}

				if (Rez == 0) break;


				Rez = Rez * a.M[i][i];
				Crack = a.M[i][i];
				for (int j = 0; j < N; j++)
					a.M[i][j] = a.M[i][j] / Crack;


				for (int j = i + 1; j < N; j++)
				{
					Crack = a.M[j][i];
					for (int k = 0; k < N; k++)
					{
						a.M[j][k] -= a.M[i][k] * Crack;
					}
				}
				//a.printMatrix();
				//printf("\n");
			}
			return Rez;
		}
		else
		{
			cout << "ERROR! Uncorrect size in detMatrix()." << endl;
			exit(1);
		}
	}*/

	T rangMatrix() const
	{
		Matrix a(*this);
		int i, j, shift, i_counter, l;
		T Crack, Rez, Sum;
		Rez = min(m, n);
		shift = 0;
		for (i = 0; i < a.m; i++)
		{
			i_counter = i;
			while (a.M[i_counter][i + shift] == 0)
			{
				if (i_counter == a.m - 1)
				{
					if ((a.M[i_counter][i + shift] == 0) && (i + shift < a.n))
					{
						shift++;
						i_counter = i;
						if (i + shift == a.n)
							break;
						continue;
					}					
				}
				i_counter++;
			}

			if (i_counter != i)
			{
				for (int j = 0; j < a.n; j++)
					swap(a.M[i][j], a.M[i_counter][j]);
			}

			Crack = a.M[i][i+shift];
			if (Crack != 0)
			{
				for (int j = 0; j < a.n; j++)
					a.M[i][j] = a.M[i][j] / Crack;
			}

			for (int j = 0; j < a.m; j++)
			{
				if (j != i)
				{
					Crack = a.M[j][i + shift];
					for (int k = 0; k < n; k++)
					{
						a.M[j][k] -= a.M[i][k] * Crack;
					}
				}
			}
		}
		for (int i = 0; i < min(m, n); i++)
		{
			Sum = 0;
			l = 0;
			while (l < min(m, n))
			{
				Sum = a.M[i][l] * a.M[i][l];
				if (Sum > 0) break;
				l++;
			}
			if (Sum == 0) Rez -= 1;
		}
		return Rez;

	}

	Matrix TMatrix() const
	{
		Matrix Rez(n, m);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
				Rez.M[j][i] = M[i][j];
		}
		return Rez;
	}

	Matrix reverseMatrix() const
	{
		if (m == n)
		{
			int N = m;
			Matrix Help(N, 2 * N);
			Matrix Rez(N, N);
			int l, err;
			T Crack, Sum;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
					Help.M[i][j] = M[i][j];
			}

			for (int i = 0; i < N; i++)
			{
				for (int j = N; j < 2 * N; j++)
				{
					if (i == (j - N)) Help.M[i][j] = 1;
					else Help.M[i][j] = 0;
				}
			}

			for (int i = 0; i < N; i++)
			{
				l = i;
				while ((Help.M[l][l] == 0) && (l < N))
				{
					if (l == N - 1)
					{
						break;
					}
					l++;
				}



				if ((l != i) && (l < N))
				{
					for (int j = 0; j < 2 * N; j++)
						swap(Help.M[i][j], Help.M[l][j]);
				}



				Crack = Help.M[i][i];
				if (Crack != 0)
				{
					for (int j = 0; j < 2 * N; j++)
						Help.M[i][j] = Help.M[i][j] / Crack;
				}



				for (int j = 0; j < N; j++)
				{
					if (j != i)
					{
						Crack = Help.M[j][i];
						for (int k = 0; k < 2 * N; k++)
						{
							Help.M[j][k] -= Help.M[i][k] * Crack;
						}
					}
				}
			}

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (((i == j) && (Help.M[i][j] == 1)) || ((i != j) && (Help.M[i][j] == 0)))
						err = 0;
					else
					{
						err = 1;
						break;
					}
				}
				if (err == 1) break;
			}

			if (err == 0)
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < N; j++)
						Rez.M[i][j] = Help.M[i][j + N];
				}
			}
			if (err == 1)
			{
				cout << "Not exist" << endl;
			}
			return Rez;
		}
		else
		{
			cout << "ERROR! Uncorrect size in reverseMatrix()." << endl;
			exit(1);
		}
	}
	
	friend istream& operator >> (istream& is, Matrix &a);

	friend ostream& operator << (ostream& os, const Matrix &a);
};

istream& operator >> (istream& is, Matrix<double> &a)
{
	for (int i = 0; i < a.m; i++)
	{
		for (int j = 0; j < a.n; j++)
			is >> a.M[i][j];
	}
	return is;
}

ostream& operator << (ostream& os, const Matrix<double> &a)
{
	for (int i = 0; i < a.m; i++)
	{
		for (int j = 0; j < a.n; j++)
			os << a.M[i][j] << " ";
		//printf("%d ", M[i][j]);
		//printf("\n");
		os << endl;
	}
	return os;
}

int main()
{
	ifstream infile("Test_matrix.txt");
	int Number_of_tests, i, m1, n1, m2, n2, m3, n3;
	int Operation_Number; //1 - (=), 2 - (+), 3 - (-), 4 - (*), 5 - ([]), 6 - (traceMatrix), 7 - (detMatrix), 8 - (rangMatrix), 9 - (TMatrix), 10 - (reverseMatrix)
	infile >> Number_of_tests;
	for (i = 1; i <= Number_of_tests; i++)
	{
		infile >> Operation_Number;
		switch (Operation_Number)
		{
		case 1:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			infile >> m2 >> n2;
			Matrix<double> b(m2, n2);
			Matrix<double> Rez(m2, n2);
			infile >> Rez;
			b = a;
			if (b != Rez) 
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 2:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			infile >> m2 >> n2;
			Matrix<double> b(m2, n2);
			infile >> b;
			Matrix<double> c(m1, n1);
			infile >> m3 >> n3;
			Matrix<double> Rez(m3, n3);
			infile >> Rez;
			c = a + b;
			if (c != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 3:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			infile >> m2 >> n2;
			Matrix<double> b(m2, n2);
			infile >> b;
			Matrix<double> c(m1, n1);
			infile >> m3 >> n3;
			Matrix<double> Rez(m3, n3);
			infile >> Rez;
			c = a - b;
			if (c != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 4:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			infile >> m2 >> n2;
			Matrix<double> b(m2, n2);
			infile >> b;
			Matrix<double> c(m1, n2);
			infile >> m3 >> n3;
			Matrix<double> Rez(m3, n3);
			infile >> Rez;
			c = a * b;
			if (c != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 5:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			double b;
			infile >> m2 >> n2;
			infile >> b;
			a[m2- 1][n2 - 1] = b;
			infile >> m3 >> n3;
			Matrix<double> Rez(m3, n3);
			infile >> Rez;
			if (a != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 6:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			double b, Rez;
			infile >> Rez;
			b = a.traceMatrix();
			if (b != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 7:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			double b, Rez;
			infile >> Rez;
			b = a.detMatrix();
			if (b != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 8:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			double b, Rez;
			infile >> Rez;
			b = a.rangMatrix();
			if (b != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 9:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			Matrix<double> b(n1, m1);
			b = a.TMatrix();
			infile >> m3 >> n3;
			Matrix<double> Rez(m3, n3);
			infile >> Rez;
			if (b != Rez)
				cout << "Test " << i << " is not success!!!" << endl;
			break;
		}

		case 10:
		{
			infile >> m1 >> n1;
			Matrix<double> a(m1, n1);
			infile >> a;
			Matrix<double> b(m1, n1);
			b = a.reverseMatrix();
			infile >> m3 >> n3;
			Matrix<double> Rez(m3, n3);
			infile >> Rez;
			if (b != Rez)
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