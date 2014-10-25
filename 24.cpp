#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class frac{
public:
	int a, b; // b > 0
	frac();
	frac(int x);
};

frac::frac()
{
	a = 0;
	b = 1;
}

frac::frac(int x)
{
	a = x;
	b = 1;
}

int gcd(int a, int b) // a != 0 && b != 0
{
	if (a<0) a = -a;
	if (b<0) b = -b;

	while (a && b)
		if (a>b) a %= b;
		else     b %= a;
	return a+b;
}

frac operator*(frac a, frac b)
{
	a.a *= b.a;
	a.b *= b.b;
	if (a.a)
	{
		b.a = gcd(a.a, a.b);
		a.a /= b.a;
		a.b /= b.a;
	}
	else
		a.b = 1;
	return a;
}

frac operator/(frac a, frac b) // b.a != 0
{
	a.a *= b.b;
	a.b *= b.a;
	if (a.a)
	{
		b.a = gcd(a.a, a.b);
		a.a /= b.a;
		a.b /= b.a;
		if (a.b<0)
		{
			a.a = -a.a;
			a.b = -a.b;
		}
	}
	else
		a.b = 1;
	return a;
}

frac operator+(frac a, frac b)
{
	int g = gcd(a.b, b.b);
	a.b /= g;
	b.b /= g;
	a.a = a.a * b.b + b.a * a.b;
	a.b = a.b * b.b * g;
	if (a.a)
	{
		g = gcd(a.a, a.b);
		a.a /= g;
		a.b /= g;
	}
	else
		a.b = 1;
	return a;
}

frac operator-(frac a, frac b)
{
	b.a = -b.a;
	return a+b;
}

int main()
{
LOOP:
	int m, n;
	int f[10];

	cin >> m >> n;
	if (!m || !n)
		return 0;
	for (int i=0; i<m+n; i++)
		cin >> f[i];
	
	vector<frac> vv(m+n+1);
	vector<vector<frac> > v(m+n);
	fill(v.begin(), v.end(), vv);

	for (int i=0; i<m+n; i++)
	{
		if (i<m)
			v[i][i] = -1;
		for (int j=0; j<=i && j<n; j++)
			v[i][m+j] = f[i-j];
	}
	v[m+n-1][m+n] = 1;

	for (int i=m; i<m+n; i++)
	{
		for (int j=i; j<m+n; j++)
			if (v[j][i].a)
			{
				swap(v[i], v[j]);
				break;
			}

		for (int j=i+1; j<m+n; j++)
			if (v[j][i].a)
			{
				frac r = v[j][i] / v[i][i];
				for (int k=i; k<m+n; k++)
					v[j][k] = v[j][k] - r * v[i][k];
			}
	}

	for (int i=m+n-1; i>=0; i--)
	{
		v[i][i] = v[i][m+n] / v[i][i];
		for (int j=0; j<i; j++)
			v[j][m+n] = v[j][m+n] - v[i][i] * v[j][i];
	}

	static bool flag = true;
	if (!flag)
		cout << endl;
	flag = false;

	bool havep = false, haveq = false;
	bool flagp = true, flagq = true;

	for (int i=0; i<m+n; i++)
	{
		frac t = v[i][i];
		if (t.a)
		{
			if (i<m)
			{
				havep = true;
				if (!flagp)
					cout << ' ';
				flagp = false;
			}
			else
			{
				haveq = true;
				if (!flagq)
					cout << ' ';
				flagq = false;
			}
			cout << '(' << t.a;
			if (t.b != 1)
				cout << '/' << t.b;
			cout << ',' << (i<m ? i : i-m) << ')';
		}

		if (i == m-1 && !havep || i == m+n-1 && !haveq)
			cout << "(0,0)";

		if (i == m-1 || i == m+n-1)
			cout << endl;
	}
	goto LOOP;

	return 0;
}
