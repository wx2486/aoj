#include <cstdio>
#include <iostream>
#include <cctype>
#include <string>
#include <climits>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

const int MAX = 10;
int min_cost;
int m, n;
int rc[MAX][MAX], dc[MAX][MAX];

int get_digit();
void finish();
void step(int r, int c, long long status, int cost, map<long long, int> &dpn);
void update(long long status, int cost, map<long long, int> &dpn);

int main()
{
	int cn; cin >> cn;

	while (cn--)
	{
		cin >> m >> n;
		for (int i=0; i<m; i++)
		{
			for (int j=0; j<n-1; j++)
				rc[i][j] = get_digit();
			if (i<m-1)
				for (int j=0; j<n; j++)
					dc[i][j] = get_digit();
		}

		finish();

		map<long long, int> dp;
		dp[0] = 0;
		min_cost = INT_MAX;

		for (int i=0; i<m; i++)
			for (int j=0; j<n; j++)
			{
				map<long long, int> dpn;
				for (map<long long, int>::iterator it=dp.begin(); it != dp.end(); it++)
					step(i, j, it->first, it->second, dpn);
				swap(dp, dpn);
			}

		cout << min_cost << endl;
	}

	return 0;
}

void update(long long status, int cost, map<long long, int> &dpn)
{
	map<long long, int>::iterator it = dpn.find(status);
	if (it == dpn.end())
		dpn[status] = cost;
	else
		it->second = min(it->second, cost);
	// printf("update: %llx %d\n", status, cost);
}

void step(int r, int c, long long status, int cost, map<long long, int> &dpn)
{
	if (c == 0)
		status <<= 2;
	// printf("%d %d %llx %d\n", r, c, status, cost);
	int bpos = 2 * c;
	long long mask = (status >> bpos) & 0xf;

	if (mask == 0x9) // 1 2
	{
		if (r == m-1 && c == n-1)
			min_cost = min(min_cost, cost);
	}
	else if (mask == 0x0) // 0 0
	{
		if (r == m-1 || c == n-1)
			return;
		status ^= mask << bpos;
		status |= (long long)(0x9) << bpos;
		cost += rc[r][c] + dc[r][c];
		update(status, cost, dpn);
	}
	else if (mask == 0x6) // 2 1
	{
		status ^= mask << bpos;
		update(status, cost, dpn);
	}
	else if (mask == 0x4 || mask == 0x1) // 0 1 or 1 0
	{
		status ^= mask << bpos;
		// -> 1 0
		if (r != m-1)
			update(status | ( (long long)(0x1) << bpos ), cost + dc[r][c], dpn);
		// -> 0 1
		if (c != n-1)
			update(status | ( (long long)(0x4) << bpos ), cost + rc[r][c], dpn);
	}
	else if (mask == 0x8 || mask == 0x2) // 0 2 or 2 0
	{
		status ^= mask << bpos;
		// -> 2 0
		if (r != m-1)
			update(status | ( (long long)(0x2) << bpos ), cost + dc[r][c], dpn);
		// -> 0 2
		if (c != n-1)
			update(status | ( (long long)(0x8) << bpos ), cost + rc[r][c], dpn);
	}
	else if (mask == 0x5) // 1 1
	{
		int dpos = 4, cnt = 0;
		long long t = status >> (bpos+dpos);

		while ((t & 0x3) != 0x2 || cnt)
		{
			if ((t & 0x3) == 0x1)
				cnt++;
			else if ((t & 0x3) == 0x2)
				cnt--;

			dpos += 2;
			t >>= 2;
		}

		status ^= (long long)(0x3) << (bpos+dpos);
		status ^= mask << bpos;
		update(status, cost, dpn);
	}
	else if (mask == 0xa) // 2 2
	{
		int dpos = 2, cnt = 0;
		long long t = 0, tt = status;
		for (int i=0; i<bpos; i+=2, tt>>=2)
			t = (t << 2) | (tt & 0x3);

		while ((t & 0x3) != 0x1 || cnt)
		{
			if ((t & 0x3) == 0x2)
				cnt++;
			else if ((t & 0x3) == 0x1)
				cnt--;

			dpos += 2;
			t >>= 2;
		}

		// if (dpos < 0)
		//    	printf("dpos error:%d %llx %d %d\n", dpos, status, r, c);
		status ^= (long long)(0x3) << (bpos-dpos);
		status ^= mask << bpos;
		update(status, cost, dpn);
	}

	//if (status >> (2*n))
	//    	cout << "status: " << status << ' ' << r << ' ' << c << endl;
	// if (status < 0)
	//     cout << "Bad status:" << status << ' ' << mask << endl;
}

int get_digit()
{
	char c;
	while (cin >> c && !isdigit(c));
	return c - '0';
}

void finish()
{
	string s;
	getline(cin, s);
	getline(cin, s);
}
