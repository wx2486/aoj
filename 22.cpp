#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 21;
struct medge
{
	int a, b, dis;
	medge(){ a = b = dis = 0; }
};
int n, lmt;
map<string, int> mp;
int dis[MAX][MAX];
int con[MAX][MAX];
bool used[MAX];
int total_dis;
medge medg[MAX];
bool dfsf[MAX];

int get_id()
{
	string s; cin >> s;
	if (mp.find(s) != mp.end())
		return mp[s];
	return mp[s] = n++;
}

int gene_tree(int id)
{// gene tree
	int mdis[MAX],tcon[MAX], mrid;
	copy(dis[id], dis[id]+MAX, mdis);
	fill(tcon, tcon+MAX, id);
	mrid = dis[0][id] ? id : 0;
	used[id] = true;
	while (true)
	{
		int minid = 0;
		for (int i=1; i<n; i++)
			if (!used[i] && mdis[i] && (!minid || mdis[i] < mdis[minid]))
				minid = i;

		if (!minid) break;
		if (dis[0][minid] && (!mrid || dis[0][minid] < dis[0][mrid]))
			mrid = minid;
		con[tcon[minid]][minid] = con[minid][tcon[minid]] = 1;
		used[minid] = true;
		id = minid;
		
		for (int i=1; i<n; i++)
			if (!used[i] && dis[id][i] && (!mdis[i] || dis[id][i] < mdis[i]))
				mdis[i] = dis[id][i], tcon[i] = id;
	}
	return mrid;
}

void dfs(int id)
{// add to total_dis, update medge
	dfsf[id] = true;
	for (int i=1; i<n; i++)
		if (!dfsf[i] && con[id][i])
		{
			total_dis += dis[id][i];
			medg[i].a = id, medg[i].b = i, medg[i].dis = dis[id][i];
			if (medg[id].dis > medg[i].dis)
				medg[i] = medg[id];
			dfs(i);
		}
	dfsf[id] = false;
}

int main()
{
	int en; cin >> en;
	mp["Park"] = n++;
	for (int i=0; i<en; i++)
	{
		int a, b, t;
		a = get_id(); b = get_id();
		cin >> t;
		if (!dis[a][b] || t < dis[a][b])
			dis[b][a] = dis[a][b] = t;
	}
	cin >> lmt;

	int subg = 0;
	for (int i=1; i<n; i++)
		if (!used[i])
		{
			int mrid = gene_tree(i);
			con[0][mrid] = con[mrid][0] = 1;
			medg[mrid].dis = 0;
			dfs(mrid);
			subg++;
		}

	for (int i=0; i<lmt-subg; i++)
	{
		int minid = 0;
		for (int j=1; j<n; j++)
			if (dis[0][j] && !con[0][j] && dis[0][j] < medg[j].dis &&
				(!minid || dis[0][j] - medg[j].dis < dis[0][minid] - medg[minid].dis))
				minid = j;

		if (!minid) break;
		con[0][minid] = con[minid][0] = 1;
		int a = medg[minid].a, b = medg[minid].b;
		con[a][b] = con[b][a] = 0;
		medg[minid].dis = 0;
		dfs(minid);
	}

	total_dis = 0;
	dfs(0);

	cout << "Total miles driven: " << total_dis << endl;

	return 0;
}
