#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class url
{
public:
	string s;
	int v;
	url(string ss, int vv);
};

url::url(string ss, int vv)
{
	s = ss;
	v = vv;
}

bool operator<(url a, url b)
{
	if (a.v != b.v)
		return a.v > b.v;
	return a.s < b.s;
}

int main()
{
	int cn; cin >> cn;
	while (cn--)
	{
		int n; cin >> n;
		vector<url> v;
		while (n--)
		{
			string a, s; cin >> a >> s;
			if (a == "Visit")
			{
				for (int i=0; i<v.size(); i++)
					if (s == v[i].s)
						v[i].v++, s[0] = '\0';
				if (s[0])
					v.push_back(url(s, 1));					
			}
			else
			{
				sort(v.begin(), v.end());
				for (int i=0; i<v.size(); i++)
					if (v[i].s.compare(0, s.length(), s) == 0)
						cout << v[i].s << endl;
				cout << endl;
			}
		}
	}

	return 0;
}
