#include <iostream>
#include <stdio.h>

int N = 3;

using namespace std;

int min(int a, int b)
{
	if (a < b) return a;
	else return b;
}

class Matrix
{
private:
	double** M;
	int m, n;


public:
	Matrix(int M1, int N1)
	{
		m = M1;
		n = N1;
		M = new double*[m];
		for (int i = 0; i < m; i++)
		{
			M[i] = new double[n];
			for (int j = 0; j < n; j++)
			{
				M[i][j] = 0;
				//cout << M[i][j] << " ";
			}
			//cout << endl;
		}
	}

public:
	void printMatrix()
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
		else cout << "ERROR!" << endl;
	}

	Matrix operator + (const Matrix &a)
	{
		if ((m == a.m) && (n == a.n))
		{
			Matrix Rez(m, n);
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
					Rez[i][j] = M[i][j] + a.M[i][j];

			}
			return *this;
		}
		else cout << "ERROR!" << endl;		
	}

	Matrix operator - (const Matrix &a)
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
		else cout << "ERROR!" << endl;
	}

	Matrix operator * (const Matrix &b)
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
		else cout << "ERROR!" << endl;		
	}

	double* operator [] (int a)
	{
			return M[a];
	}

	void operator ()(int a, int b, int Rez)
	{
		if ((a - 1 < m) && (b - 1 < n) && (a>0) && (b>0))
			M[a-1][b-1] = Rez;
		else cout << "ERROR!" << endl;
	}


	double traceMatrix()
	{
		if (m == n)
		{
			double Sum = 0;
			for (int i = 0; i < N; i++)
				Sum += M[i][i];
			return Sum;
		}
		else cout << "ERROR!" << endl;
	}

	double detMatrix()
	{
		if (m == n)
		{
			Matrix a(m, n);
			int l;
			double Crack;
			double Rez = 1;
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
		else cout << "ERROR!" << endl;
	}

	double rangMatrix()
	{
		N = min(m, n);
		double Rez = N;
		Matrix a(m, n);
		int l;
		double Crack, Sum;
		for (int i = 0; i < m; i++)
			{
			for (int j = 0; j < n; j++)
				a.M[i][j] = M[i][j];
		}


		for (int i = 0; i < m; i++)
		{
			l = i;
			while ((a.M[l][l] == 0) && (l < N))
			{
				if (l == N - 1)
				{
					break;
				}
				l++;
			}



			if ((l != i) && (l < N))
			{
				for (int j = 0; j < n; j++)
					swap(a.M[i][j], a.M[l][j]);
			}



			Crack = a.M[i][i];
			if (Crack != 0)
			{
				for (int j = 0; j < n; j++)
					a.M[i][j] = a.M[i][j] / Crack;
			}



			for (int j = 0; j < m; j++)
			{
				if (j != i)
				{
					Crack = a.M[j][i];
					for (int k = 0; k < n; k++)
					{
						a.M[j][k] -= a.M[i][k] * Crack;
					}
				}					
			}
			//a.printMatrix();
			//printf("\n");
		}

		for (int i = 0; i < N; i++)
		{
			Sum = 0;
			l = 0;
				while (l < N)
			{
				Sum = a.M[i][l] * a.M[i][l];
				if (Sum > 0) break;
				l++;
			}
			if (Sum == 0) Rez -= 1;
		}
		return Rez;	
		
	}

	Matrix TMatrix()
	{
		Matrix Rez(n, m);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
				Rez.M[j][i] = M[i][j];
		}
		return Rez;
	}

	Matrix reverseMatrix()
	{
		if (m == n)
		{
			int N = m;
			Matrix Help(N, 2 * N);
			Matrix Rez(N, N);
			int l, err;
			double Crack, Sum;
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
					for (int j = 0; j < 2*N; j++)
						swap(Help.M[i][j], Help.M[l][j]);
				}



				Crack = Help.M[i][i];
				if (Crack != 0)
				{
					for (int j = 0; j < 2*N; j++)
						Help.M[i][j] = Help.M[i][j] / Crack;
				}



				for (int j = 0; j < N; j++)
				{
					if (j != i)
					{
						Crack = Help.M[j][i];
						for (int k = 0; k < 2*N; k++)
						{
							Help.M[j][k] -= Help.M[i][k] * Crack;
						}
					}
				}
				Help.printMatrix();
				printf("\n");
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
				return Rez;
			}
			if (err == 1) cout << "Not exist" << endl;

		}
		else cout << "ERROR!" << endl;
	}

	/*~Matrix()
	{
		for (int i = 0; i < m; i++)
			delete M[i];
		delete M;
	}*/
};


int main()
{
	int m, n;
	cin >> m >> n;
	Matrix a(m, n);
	double Rez;
	Matrix b(m, n);
	//Matrix c(m, m);
	a.scanfMatrix();
	printf("\n");
	//b.scanfMatrix();
	//printf("\n");
	//c = a * b;
	//b = a.reverseMatrix();
	//cout << Rez << endl;
	a(2, 3, 5);
	a.printMatrix();
	return 0;
}