#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int base, tgt;
int last[100001];

bool calc(vector<int> &a, vector<int> &b)
{
	for (int i=0, d=0; i<b.size(); i++)
	{
		int ta = (b[i]+base-a[i-d]) % base, tb = b[i] < a[i-d];
		a.push_back(ta);
		if (!tb)
			continue;
		if (i+1 >= b.size())
			b.push_back(1);
		else if (b[i+1] != 1)
			return false;
		i++, d++;
	}

	return true;
}

bool put(int num, int pos)
{
	while (true)
	{
		if (pos == tgt)
		{
			last[pos] = num;
			return true;
		}

		if (last[pos] < 0)
		{
			last[pos] = num;
			return false;
		}

		swap(last[pos], num);
		num += last[pos++];
		if (num >= base)
		{
			if (put(num%base, pos))
				return true;
			if (put(1, pos))
				return true;
			return false;
		}
	}
}

int main()
{
	int cn; scanf("%d", &cn);
	while (cn--)
	{
		int n; scanf("%d%d", &base, &n);
		vector<int> onev(1);
		vector<vector<int> > v(n, onev);
		for (int i=0; i<n; i++)
			scanf("%d", &v[i][0]);
		scanf("%d", &tgt);
		vector<int> &fv = v[0];

		for (int i=n-1; i; i--)
			if (!calc(v[i-1], v[i]))
				goto IMPOSSIBLE;

		fill(last, last+tgt+1, -1);
		for (int i=0; i<fv.size(); i++)
			if (put(fv[i], 1))
				goto NEXT;

	UNPREDICTABLE:
		puts("unpredictable");
		continue;
	NEXT:
		printf("%d\n", last[tgt]);
		continue;
	IMPOSSIBLE:
		puts("impossible");
		continue;
	}

	return 0;
}
