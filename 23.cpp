#include <iostream>
#include <queue>

using namespace std;

struct number
{
	long long n;
	int id, seq;
};

bool operator < (number a, number b)
{
	if (a.n != b.n)
		return a.n > b.n;
	return a.id > b.id;
}

priority_queue<number> pq, emp;

long long get_number(long long k, long long n)
{
	return n + (k-2) * ((n * (n-1)) / 2);
}

void push_next(number n)
{
	n.n = get_number(n.id, ++n.seq);
	pq.push(n);
}

void get_same(int k)
{
	number num, t;
	while (pq.top().n < k)
	{
		t = pq.top(); pq.pop();
		push_next(t);
	}
	num = pq.top(); pq.pop(); push_next(num);

	while (pq.top().n != num.n)
	{
		num = pq.top(); pq.pop();
		push_next(num);
	}
	t = pq.top(); pq.pop(); push_next(t);

	cout << num.n << ':' << num.id << ' ' << t.id;
	while (pq.top().n == num.n)
	{
		cout << ' ' << pq.top().id;
		t = pq.top(); pq.pop();
		push_next(t);
	}

	cout << endl;
}

int main()
{
	int n;
	while (cin >> n && n)
	{
		pq = emp;
		for (int i=0; i<n; i++)
		{
			int tn;
			cin >> tn;
			number t;
			t.id = tn;
			t.seq = 1;
			t.n = get_number(tn, 1);
			pq.push(t);
		}
		int minn; cin >> minn;
		static bool flag = true;
		if (!flag)
			cout << endl;
		flag = false;
		for (int i=0; i<5; i++)
			get_same(minn);
	}
	return 0;
}
