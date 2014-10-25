#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAX = 500;
struct order
{
	int time, x1, y1, x2, y2;
};
int n;
bool ls[MAX][MAX];
bool used[MAX];
int tgt[MAX];

bool can_match(int id)
{
	for (int i=0; i<n; i++)
		if (ls[id][i] && !used[i])
		{
			used[i] = true;
			if (tgt[i] < 0 || can_match(tgt[i]))
			{
				tgt[i] = id;
				return true;
			}
		}
	return false;
}

int main()
{
	int cn; cin >> cn;
	while (cn--)
	{
		vector<order> ov;
		cin >> n;
		for (int i=0; i<n; i++)
		{
			order t;
			char tmp;
			cin >> t.time >> tmp >> t.x1;
			t.time = t.time * 60 + t.x1;
			cin >> t.x1 >> t.y1 >> t.x2 >> t.y2;
			ov.push_back(t);
		}
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				ls[i][j] = ov[j].time > 
					ov[i].time +
					abs(ov[i].x2-ov[j].x1) + abs(ov[i].y2-ov[j].y1) +
					abs(ov[i].x1-ov[i].x2) + abs(ov[i].y1-ov[i].y2);
		
		int match = 0;
		fill_n(tgt, MAX, -1);
		for (int i=0; i<n; i++)
		{
			fill_n(used, MAX, false);
			match += can_match(i);
		}
		cout << n - match << endl;
	}

	return 0;
}
