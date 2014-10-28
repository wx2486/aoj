#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 102;
int n;
int rd[MAX][MAX], flow[MAX][MAX];
bool used[MAX];

bool add_flow(int id, int limit)
{
	used[id] = true;
	if (id == n+1)
		return limit;
	for (int i=0; i<n+2; i++)
		if (!used[i] && rd[id][i] >= flow[id][i] + limit)
		{
			if (add_flow(i, limit))
			{
//				printf("add flow: %d %d %d\n", id, i, f);
				flow[id][i] += limit;
				return true;
			}
		}
	
	for (int i=0; i<n+2; i++)
		if (!used[i] && flow[i][id] >= limit)
		{
			if (add_flow(i, limit))
			{
				flow[i][id] -= limit;
				return true;
			}
		}

	return false;
}

int main()
{
LOOP:
	int np, nc, m;
	if (scanf("%d%d%d%d", &n, &np, &nc, &m) == EOF)
		return 0; 

	fill(rd[0], rd[0]+MAX*MAX, 0);
	fill(flow[0], flow[0]+MAX*MAX, 0);
	for (int i=0; i<m; i++)
	{
		int a, b, c;
		while (getchar() != '(');
		scanf("%d%*c%d%*c%d", &a, &b, &c);
		rd[a][b] = c;
	}
	for (int i=0; i<np; i++)
	{
		int a, b;
		while (getchar() != '(');
		scanf("%d%*c%d", &a, &b);
		rd[n][a] = b;
	}
	for (int i=0; i<nc; i++)
	{
		int a, b;
		while (getchar() != '(');
		scanf("%d%*c%d", &a, &b);
		rd[a][n+1] = b;
	}

#define LOOP_LIMIT(limit) \
	do\
		fill(used, used+MAX, false);\
	while (add_flow(n, (limit)));

	for (int i=12; i>=0; i--)
		LOOP_LIMIT(1<<i);

	int sum = 0;
	for (int i=0; i<n; i++)
		sum += flow[n][i];
	printf("%d\n", sum);

	goto LOOP;

	return 0;
}
