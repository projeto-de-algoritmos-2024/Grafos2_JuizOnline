#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

vector<ii> adj[100001];

int prim(int u, int N)
{
    set<int> C;
    C.insert(u);

    priority_queue<ii, vector<ii>, greater<ii>> heap;

    for (auto [v, w] : adj[u])
        heap.push(ii(w, v));

    int mst = 0;

    while ((int)C.size() < N)
    {
        int v, w;

        do
        {
            w = heap.top().first, v = heap.top().second;
            heap.pop();
        } while (C.count(v));

        mst += w;
        C.insert(v);

        for (auto [s, p] : adj[v])
            heap.push(ii(p, s));
    }

    return mst;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, m;
        cin >> n >> m;

        for (int u = 1; u <= n; ++u)
            adj[u].clear();

        while (m--)
        {
            int a, b;
            long long c;
            cin >> a >> b >> c;

            auto k = static_cast<int>(log2(c));

            adj[a].emplace_back(b, k);
            adj[b].emplace_back(a, k);
        }

        cout << prim(1, n) + 1 << endl;
    }

    return 0;
}