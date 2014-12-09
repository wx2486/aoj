#include <iostream>
#include <string>

using namespace std;

const int MAX = 100;

int main()
{
	int cn; cin >> cn;
	while (cn--)
	{
		int p;
		string s;
		cin >> p >> s;

		int n = s.length();

		int mtr[MAX][MAX];
		for (int i=0; i<n; i++)
		{
			mtr[i][0] = 1;
			for (int j=1; j<n; j++)
				mtr[i][j] = mtr[i][j-1] * (i+1) % p;
			mtr[i][n] = (s[i] == '*') ? 0 : s[i] - 'a' + 1;
		}

		for (int i=0; i<n; i++)
			for (int j=i+1; j<n; j++)
				for (int k=i+1; k<n+1; k++)
					mtr[j][k] =	(mtr[j][k] * mtr[i][i] % p - mtr[i][k] * mtr[j][i] % p + p) % p;

		for (int i=n-1; i>=0; i--)
			for (int j=i-1; j>=0; j--)
			{
				for (int k=j; k<i; k++)
					mtr[j][k] =	mtr[j][k] * mtr[i][i] % p;
				mtr[j][n] = (mtr[j][n] * mtr[i][i] % p - mtr[i][n] * mtr[j][i] % p + p) % p;
			}

/*
		for (int i=0; i<n; i++)
			cout << '(' << mtr[i][i] << ", " << mtr[i][n] << ')';
		cout << endl;
*/

		for (int i=0; i<n; i++)
		{
			for (int j=0; j<p; j++)
				if (j*mtr[i][i]%p == mtr[i][n])
				{
					cout << j;
					break;
				}
			if (i<n-1)
				cout << ' ';
			else
				cout << endl;
		}
	}

	return 0;
}
